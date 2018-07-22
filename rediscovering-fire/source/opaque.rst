Opaque types
============
.. _opaque: https://en.wikipedia.org/wiki/Opaque_data_type
.. _FILE: http://man7.org/linux/man-pages/man3/fopen.3.html
.. _ABI: https://en.wikipedia.org/wiki/Application_binary_interface
.. _unique_ptr: https://en.cppreference.com/w/cpp/memory/unique_ptr
.. _Julia: https://julialang.org/
.. _GArray: https://developer.gnome.org/glib/2.56/glib-Arrays.html

This section discusses the opaque_ type, an object without its data structure
externally defined in an interface. It is **the** data hiding technique in C,
and has been used extensively throughout history. In fact, it's an integral
part of C and unix' defining feature: the FILE_.

While this technique is very useful for protecting implementation details and
hiding some possibly moving parts, the opaque type has some jarring problems
when writing core libraries.

Lifetime model
--------------
The main drawback is that an opaque type *forces* you to write matching
``alloc`` and ``destroy`` functions, because only one C source file can see the
definition. It necessitates a heap allocation *in C*.

This means every opaque type needs to have a wrapping object in the host
language dedicated to managing a pointer, forcing the C model onto the host
language. While this is usually ok in C++ (except its tiresome to write wrapper
objects), there is a less clear notion of lifetimes in most garbage collected
languages. Additionally, now extra code needs to be run during clean-up,
instead of a pure deallocation.

Consider this example in C++:

.. code-block:: c++

    class A {
    public:
        A()        : opq(opq_default_alloc()) {}
        A(int arg) : opq(opq_int_alloc(arg))  {}

        int readval() { opq_readval(this->opq); }

        ~A() { opq_destroy(this->opq); }

    private:
        opaque* opq;
    };


If ``opq`` *wasn't* opaque, but rather a collection of automatic variables, the
destructor ``~A()`` and the default constructor ``A()`` can be defaulted. But
the bigger problem is the (defaulted) copy constructor and ``=`` operator.

.. code-block:: c++

    A a;
    if( true ) {
        A b = a; // opq shared between a and b
    } // b destroyed, opq_destroy called

    a.readval(); // oops, opq_destroy already called on b.opq


Not only is the extra indirection costly, it requires more boilerplate to make
C++ behave like C++. The story is similar for many languages, such as Julia_:

.. code-block:: Julia

    mutable struct data_trace
    end

    function segyio_readtrace(fp::segy_file, n::Integer)
        output_ptr = ccall(
            (:segy_readtrace, :segyio), # C function and library
            Ptr{data_trace},            # output type
            (Ptr{segy_file},Cint),      # input types
            fp, n                       # input vars
        )
        if output_ptr == C_NULL # Could not open file
            throw(FileOpenError())
        end
        
        # register cleanup with runtime,
        # but the actual call may be delayed
        finalizer(output_ptr, segy_trace_free)
        return output_ptr
    end

    function segy_trace_free(p::Ref{data_trace})
        ccall(
            (:segy_trace_free, :segyio),
            Void,
            (Ref{data_trace},),
            p
        )
    end


Adapted from the `Julia documentation
<https://docs.julialang.org/en/stable/manual/calling-c-and-fortran-code/index.html#Some-Examples-of-C-Wrappers-1>`_

Exactly when the trace is free'd is up to the Julia runtime. If the handle
wasn't opaque, but just a regular array, a *block of (aligned) memory*, then:

- The finalizer is not necessary
- No extra action is needed for cleanup
- A Julia object is already available
- No large set of alloc/free functions
- Traces behave like Julia arrays

Storage and representation
--------------------------
The only way to use an opaque type is to store and pass around a pointer to the
object. While it is true it provides ABI_ stability it impossible to use native
data types for the components, and that makes it harder to write custom
behaviours from host languages as well.

Consider this example from segyio: if a file describes a 3-dimensional
*volume*, a cube, it has a set of assosicated inline and crossline labels that
describe the resolution or *ticks* in the horizontal directions. In Python,
this is stored as two Numpy arrays, which means:

- They can be printed and formatted by Python
- They can be inspected with any python syntax or feature (like debuggers)
- They can be replaced by any other type implementing an array
- They support the full range of Numpy features
- They carry Python semantics and behave nicely and as expected
- They are constructed, managed, and cleaned up automatically

The segyio core library does not know (or care) that Numpy is responsible for
storing the line labels. If the labels had been hidden behind an opaque type,
say, ``geometry``, none of this would've *just worked*, and possibly never been
exposed to users of the Python library.

Not having this hidden behind a pointer means that it can also be *generated*
as-need. As long as the correct representation is available when the function
is called, the core library does not care that it is encoded in different
structures and assembled just-in-time. This gives library developers
flexibility to write the *right* library for their users.

Remember, the clients are other *library developers*, and it's ok to assume
they're reasonably responsible. In Python, being able to facilitate core
features like slicing is paramount, and maybe Python expects some error
recovery that's just not that interesting in Julia. By exposing more data with
a disclaimer, developers can write better libraries without requiring explicit
support from the core library.

Boilerplate and flexibility
---------------------------
The only way to get *anything* out of an opaque handle is a function, and if
you need to do something that the core author didn't think of you're lost.
This happens to be the strength of the opaque type design, the library author
can guarantee integrity, so you take the good with the bad.

The opaque type *hides data*. It does so at two levels:

- From the compiler
- From the developer

The first case is very appealing for stability, as previously mentioned, as it
enables changing the data layout without recompiling or modifiying existing
code, at the cost of maybe disallowing some optimisations, and introducing some
extra indirection.

But hiding data from the *developer* means stripping power, which when used
responsibly greatly improves the quality of the end-user facing library. By
deferring the choice of storage of primitive, raw data, developers can choose
what makes most sense for their library. In Python, most data that could be hid
inside the ``segy_file`` handle, is currently [#]_ stored this way:

.. code-block:: c

    struct segyiofd {
        PyObject_HEAD
        autofd fd;
        long trace0;
        int trace_bsize;
        int tracecount;
        int samplecount;
        int format;
        int elemsize;
    };

This is how arbitrary data is embedded inside Python objects, when the objects
are defined inside a Python extension, and this data is *buried* inside the
object. The ``autofd`` class is a simple unique_ptr_ like class that automates
some common operations. In use, it's reminiscent of C++:

.. code-block:: c

    PyObject* metrics( segyiofd* self ) {
        static const int text = SEGY_TEXT_HEADER_SIZE;
        static const int bin  = SEGY_BINARY_HEADER_SIZE;
        const int ext = (self->trace0 - (text + bin)) / text;
        return Py_BuildValue( "{s:i, s:l, s:i, s:i, s:i, s:i}",
                              "tracecount",  self->tracecount,
                              "trace0",      self->trace0,
                              "trace_bsize", self->trace_bsize,
                              "samplecount", self->samplecount,
                              "format",      self->format,
                              "ext_headers", ext );
    }

This function builds a dictionary of certain structural properties of the file.
There's no need to call functions like ``segy_get_tracecount(fp)``, but segyio
provides functions to *compute* all these values - it just doesn't make a
decision on how to store them. For completeness, the functions to compute all
the data needed for this dictionary (same order as the dict):

.. _automation-sans-opaque:
.. code-block:: c

    int  segy_traces( segy_file*, int*, long trace0, int trace_bsize );
    long segy_trace0( const char* binheader );
    int  segy_trsize( int format, int samples );
    int  segy_samples( const char* binheader );
    int  segy_format( const char* binheader );

In short, by exposing more data as *data* instead of hiding it behind functions
on an opaque handle, it's simpler for the developer to choose low-boilerplate
highly efficient native idioms for the target environment, instead of having to
deal with the data hiding idioms of the *core* language.

Opacity is not abstraction
--------------------------
Often, the opaque type is justified as an abstraction, something like *users
don't have to worry about exact representation*. While true, opacity implies
*indirection*, but indirection itself is not abstraction. There are many
libraries and programs that use opaque types liberally, and then end up writing
tons of functions to control every aspect of it.

An example is the glib GArray_. This is not a criticism of glib; glib targets C
application developers, and segyio targets library developers. This is GArray's
interface:

.. code-block:: c

    GArray* g_array_new()
    GArray* g_array_sized_new()
    GArray* g_array_ref()
    void    g_array_unref()
    guint   g_array_get_element_size()
    #define g_array_append_val()
    GArray* g_array_append_vals()
    #define g_array_prepend_val()
    GArray* g_array_prepend_vals()
    #define g_array_insert_val()
    GArray* g_array_insert_vals()
    GArray* g_array_remove_index()
    GArray* g_array_remove_index_fast()
    GArray* g_array_remove_range()
    void    g_array_sort()
    void    g_array_sort_with_data()
    #define g_array_index()
    GArray* g_array_set_size()
    void    g_array_set_clear_func()
    gchar*  g_array_free()


The GArray is not comletely opaque, it exposes its data as a ``gchar*``
pointer. For the sake of the argument, let's assume there also is a
``g_array_raw`` function that returns this pointer from the opaque ``GArray``.

This module does very little to abstract over the C array [#]_, a chunk of
consecutive elements, because abstraction is about *removing details*. All the
details are still there:

- Appending is faster than insertion
- Elements are stored contiguously
- It has a finite size
- It has no extra structure or invariants (like the stack, for instance)

What it does is *automate* some common operations over C arrays. This is
useful, but it's not an abstraction. In a library like segyio, introducing our
own type that did not abstract over anything, would only make interoperating
with Python more cumbersome. The automation is appealing, but is doable
:ref:`without opacity <automation-sans-opaque>`.

Alternatives
------------
Opaque types aren't bad, and I'm not advising against the use of opaque data
types. They're great, but when writing a library for other libraries to
consume, I think they do more harm than good for most data types. The only
real exceptions are file handles and other *remote* resources.

Instead of reaching for the opaque type, consider:

- Narrow the scope of the module
- Passing what would be embedded as explicit function arguments
- Add reserved fields for later use in structs and functions

Finally, having interfaces without opaque types means its often easier to test.
Since an arbitrary state can be constructed without going through the machinery
of the opaque handle, or even bypassing security mechanisms, tests can be more
to the point and accurate.

Summary
-------
This section disucssed the problems of designing too much around the opaque
data type. While a very useful technique, it often ends up counter-productive
when designing for libraries, because the final say in anything, and every
conceivable feature, has to be implemented in the core C library.

It demonstrates why having stuff often hidden behind pointers is *useful* when
represented as scattered, free variables. This all relies on users being
library developers, that have to map between a core library's view of the
world, and the assumptions of their target environment.

.. [#] 2018-07-10
.. [#] The C array is already a pretty good abstraction over a segment of bytes
