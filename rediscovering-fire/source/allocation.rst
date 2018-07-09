Allocation and memory management
================================
This section discusses allocation, resource management, and the resulting
effect on overall library design.

.. _PETSc: https://www.mcs.anl.gov/petsc/
.. _REPL: https://en.wikipedia.org/wiki/Read-eval-print_loop
.. _buffer object: https://docs.python.org/3/c-api/buffer.html

Half of Common Lisp
-------------------
C and its standard library (I'm deliberately not considering common unix
libraries here) is pretty tiny, so for a very long time, large C libraries have
assumed that virtually nothing pre-written was available, and consequently
written it for their project.  This is so common it's known as `Greenspun's
tenth rule <https://en.wikipedia.org/wiki/Greenspun%27s_tenth_rule>`_:

    Any sufficiently complicated C or Fortran program contains an ad-hoc,
    informally-specified, bug-ridden, slow implementation of half of Common
    Lisp

I think that a good example of this is the PETSc_ library, a popular package in
C for scientific computing. Here's a snippet initialising a vector ``x``, and
copying into ``u`` and ``b``.

.. code-block:: c

    VecCreate(PETSC_COMM_WORLD,&x);
    PetscObjectSetName((PetscObject) x, "Solution");
    VecSetSizes(x,PETSC_DECIDE,n);
    VecSetFromOptions(x);
    VecDuplicate(x,&b);
    VecDuplicate(x,&u);

Code example from `PETSc tutoral ex1
<http://www.mcs.anl.gov/petsc/petsc-current/src/ksp/ksp/examples/tutorials/ex1.c.html>`_

Granted, it's fairly straight forward if you're writing your application in C,
but let's assume we want to use this vector in a Python program. Python has no
concept of PETSc's custom (and opaque) vector type, so to make use of it, the
extension must implement a new Python class that either:

1. Implements methods that map onto the Vector functions in PETSc
2. Implements Python's Container protocol (``__getitem__``, ``__len__`` etc),
   massage the arguments and forward to PETSc, and allows information to flow
   back into Python

While 1. is simple, and familiar to a seasoned PETSc dev programming in Python,
it lends itself to a clumsy *Python* library. The REPL_ won't print data
nicely, it won't be usable in ``for _ in _`` contexts, and ``len(x)`` fails.
Numpy is the de facto standard package for scientific computing in Python, and
one of its major benefits is behaving very similar to how Python's own list
(``[]``) the ``numpy.ndarray`` really is. Programs using this library will
technically be Python, but largely feel like C with Python syntax.

Option 2. is a lot of work, but the resulting library ends up looking like
Python code. Since PETSc protects types behind a pointers, no third party
library can be leveraged to help this work, or automate it, and it won't nicely
integrate with Numpy or other libraries.

None of these solutions solve the issue of resource management, and a
considerable amount of code will have to be commited to bridge the gap between
the lifetime models of PETSc and Python. That work can be delegated to user
(Python) code, but if you have to carefully manage memory, you might as well
write C.

There's another problem neither of these approaches solve: what if I want to
return a Numpy array from a function? Granted, the arrays can be copied inside
python (assuming option 2), but that might introduce a significant overhead, or
place a potential extra burden on clients.

Both of these solutions means that a *substantial* amount of code has to be
written to leverage the C core, and the resulting in a less ergonomic Python
library.

Allocate-and-return
-------------------
segyio reads chunks seismic data, *traces*, from a file. The very first
prototype of segyio (that part never made it to the published repository)
looked something like this:

.. code-block:: c

    float* read_trace( segy_file*, int trace_number );

Which, granted, is pretty simple, but has some glaring issues:

- How do I release? ``free``? ``delete``? Is it managed internally?
- Buffers can no longer be reused, so every read *must* pay the price of
  allocation
- Multiple traces can no longer be stored in the same allocation.
- How is this float-array exposed as a Python object?

It has some additional problems, but they will be discussed in other sections.

This was one of the first issues that *radically* changed the design of segyio,
because SEG-Y files often describe geometric *volumes*, cubes, of the
subsurface. This introduces the concept of intersecting *lines*, which in the
file is a set of consecutive traces (which go in depth).

Simplified, reading a line would result in a function like this:

.. code-block:: c

    float* read_line(segy_file* fp, int line_number) {
        int trace_length = fp->trace_length * sizeof(float);
        int start = start_of_line(fp, line_number);
        int end = start + fp->line_length;

        float* line = malloc(trace_length * fp->line_length);
        int pos = 0;

        for( int i = start; i < end; ++i ) {
            float* trace = read_trace(fp, i);
            memcpy(line + pos, trace, trace_length);
            free(trace);
            pos += trace_length;
        }

        return line;
    }

Because read_trace allocates, which is convenient in calling C code as the
caller doesn't need to know upfront how much memory is needed, it is now
impossible to use this function in *any* other context than reading single
traces, without taxing the allocator heavily, or copying all the data twice.

While sometimes *convenient* to not worry about size, and just get nicely laid
out memory back, remember that the consumers are *other library writers*, and
it's safe to assume they can figure out much is needed - in fact, they often
*want* to lay out memory in a certain way, or merge several C operations into a
single, larger user-facing function.

Thou shalt not assume how memory is managed
-------------------------------------------
The previous bit touches is the first rediscovery made in segyio, a detail I
have sinced noticed is prevalent in a lot of the older libraries - almost all
functions take their memory buffer as an argument, and few functions (visibly)
allocates. Some examples from the C standard library:

.. code-block:: c

    size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
    int sprintf(char* buffer, const char* format, ...);
    char* strcat(char* dest, const char* src);
    void* memcpy(void* dest, const void* src, size_t n);

When designing libraries for libraries, you **do not get to assume how your
client manages resources**. Maybe they want a memory pool, maybe stuff is ref
counted, maybe there's a tracing gc somewhere, maybe they prefer a large,
up-front allocation, or have some other, exotic allocator. If your target group
is application writers, some assumptions on their behalf is often welcome.

Memory is still necessary for a lot of functions to operate. In segyio, only
one function (publically [#]_) allocates, the ``segy_open`` function. All other
functions assume memory is allocated and meet expectations, and are managed
externally. One common criticism of C and its standard library is its unsafety,
which is very real, and this lession does nothing do alleviate that.

This places a larger burden on host language library developers, but give a lot
of flexibility. In segyio's Python extension, all memory is allocated by
creating empty Numpy array *in Python*, so even the Python-C layer no
allocation is done, and memory is properly registered with the Python runtime.
In fact, the extension code does not know at all that it is Numpy that provides
the memory - all it sees is a `buffer object`_, and the Python code is free to
replace Numpy with something else. This has proven to scale very for segyio,
where resource allocation has been rewritten at least three times (invisibly to
the user).

For a motivating example, consider the following Python program, which prints
the mean value of every individual trace:

.. code-block:: python

    for trace in f.trace[:]:
        print(trace.mean())

This allocates one, 1, buffer under the hood, and reuses that, since it knows
it's in an iterable context, and that no modifications o the ``trace`` variable
will carry on to the next iteration. I measured this by running it ten million
times on a simple file, and found that re-using the buffer *doubled* the speed
of the program.

This would not have been possible if the core did not work with caller-provided
buffers.

Since memory is now assumed to always be there, and correct, the tedious manual
memory management of C goes away, which does make a lot of code a lot simpler,
at the cost of documenting expectations and requirements.

Summary
-------
This section discussed the drawbacks of *hiding allocations*, and returning
freshly allocated memory from functions with the expectation that callers
release it later, and demonstrates why libraries for libraries should always
assume its memory is externally managed, and take it by argument.

Briefly, assuming memory is allocated, managed, and correct makes the library
simpler, and leaves the author of the module using the library the flexbility
needed to make the right choices *for that environment*. Choices that are
drastically different in Python, C++, Common Lisp, and Julia.

.. [#] ``segy_readsubtr`` and ``segy_writesubtr`` will allocate and free upon
       when reading non-contiguous ranges, unless the ``rangebuf`` parameter is
       specified, in which case it will assume it is large enough, and use
       that.
