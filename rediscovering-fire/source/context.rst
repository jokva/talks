Context and motivation
======================
This section discusses context, requirements, and motivations for segyio. If
either of these had been different, segyio would have been very different
today.

Context and requirements
------------------------
`SEG-Y <https://en.wikipedia.org/wiki/SEG-Y>`_ is a fairly old standard, built
around in an age of magnetic tape and IBM-centric hardware. It has a lot of
quirks, and there are lot of standard-violating files out there. We saw several
implementations being developed and maintained by lone geoscientists scattered
around the company, with varying quality and completeness. It's also a very
duplicated effort, and a huge time sink.

So we wanted a high-quality solution that would just take the pain away. But
this raises the issue of language and operating system.

At the time, Python was seeing a *huge* surge in popularity in the Equinor
geoscience community, so doing the implementation in pure Python was
considered. It was decided against, because:

1. We have tons of applications in C++, C, Java, .NET, matlab, and other
   languages, that could leverage reading SEG-Y files, meaning essentially a
   port from Python
2. Python's fairly slow, and may not be suitable for computationally-intensive
   problems
3. Shuffling bytes isn't Python's strong suit

In fact, an original requirement was also a matlab library (which has since
largely been abandoned). Replicating SEG-Y weirdness across languages was not
very appealing, so a C core library was chosen, because virtually all languages
have `FFIs <https://en.wikipedia.org/wiki/Foreign_function_interface>`_ to C.

That way, in order to read SEG-Ys in a new language, say Julia, it's "only"
necessary to implement the Julia -> segyio bit, and the Julia implementation
shouldn't need to worry too much about SEG-Y details. Geoscientists don't have
to write C code, but will have more suited libraries at their disposal.

Multiple high-level language implementations sharing a common core was always a
part of the segyio vision.

Goals
-----
The requirements arise from the business case, and from the need of our end
users, but segyio also has some technical goals:

**Natural**
    User-facing libraries should *feel* like they were written in that language
**Fast**
    Speed matters, and faster libraries means faster programs
**Portable**
    Useable on different architectures, and different operating systems
**Stable**
    Functioning code should remain functioning, and upgrading should always be
    safe

Natural
~~~~~~~
A lot of libraries that wrap modules written in a different language have a
distinct *feel* about them. In the Python world, an excellent example of this
is the curses_ module, which directly maps onto the underlying C library. While
this makes the module immediately familiar to anyone that has written *curses*
code in C, it pretty much feels like writing C with Python syntax.

.. _curses: https://docs.python.org/3/library/curses.html#module-curses

.. code-block:: python

    import curses
    from curses.textpad import Textbox, rectangle

    def main(stdscr):
        stdscr.addstr(0, 0, "Enter IM message: (hit Ctrl-G to send)")

        editwin = curses.newwin(5,30, 2,1)
        rectangle(stdscr, 1,0, 1+5+1, 1+30+1)
        stdscr.refresh()

        box = Textbox(editwin)

        # Let the user edit until Ctrl-G is struck.
        box.edit()

        # Get resulting contents
        message = box.gather()


Code example from `curses docs <https://docs.python.org/3/howto/curses.html>`_.

To be fair, Curses is pretty old, and has held up rather well for the video
terminals it targets. Let's look at a few examples that I believe *feel* right,
and appreciate what they do right.

.. code-block:: python

    >>> r = requests.get('https://api.github.com/user',
                         auth=('user', 'pass'))
    >>> r.status_code
    200
    >>> r.headers['content-type']
    'application/json; charset=utf8'
    >>> r.encoding
    'utf-8'
    >>> r.text
    u'{"type":"User"...'
    >>> r.json()
    {u'disk_usage': 368627, u'private_gists': 484, ...}

Code example from `request docs <https://pypi.org/project/requests/>`_

.. code-block:: python

    >>> A = np.array( [[1,1],
    ...                [0,1]] )
    >>> B = np.array( [[2,0],
    ...                [3,4]] )
    >>> A.shape
    (2, 2)
    >>> A*B             # elementwise product
    array([[2, 0],
           [0, 4]])
    >>> A.dot(B)        # matrix product
    array([[5, 4],
           [3, 4]])
    >>> np.dot(A, B)    # another matrix product
    array([[5, 4],
           [3, 4]])

Code example from `numpy quickstart
<https://docs.scipy.org/doc/numpy/user/quickstart.html>`_

For requests, it's has a reasonable defaults, and the most simple use case,
just fetching a remote web site, is as simple as ``requests.get(url)``. All
other configuration is keyword arguments. Results of queries have a fairly
limited set of interesting things to afterwards (determined by the HTTP
protocol), so they're all *properties* on the returned object, no awkward get
methods. Callers can inspect what they care about as they see fit (status,
encoding etc.). The dynamic parts of a result, contents of the header, are read
with the ubiquitous ``dict``.

Numpy share the same attributes, but for maths and not HTTP. Granted, numpy
code can quickly get rather wieldy, but that's often a result of its
(wonderful) composability and the sometimes involved nature of the
transformations users want to express, and is not something *inherent* to numpy
code. Largely, however, things do work as you would expect, and there certainly
isn't a feeling that it simply wraps a Fortran or C library.

For segyio, the goal was to make the library feel *natural*. Things should work
as you'd expect in Python - arguments and types should be robust and work, the
right errors should be raised, and combining features should result in what
you'd expect. Conversly, it was deemed important not to have things work in a
specific way just because the core library worked that way - Python could make
its own decision and design choices.

This has, to me, some surprising implications when designing a C library. A lot
of interesting issues, things we often take for granted, come up - what if you
*can no longer* assume `stderr` is available for warnings? What if you *can no
longer ask for more memory*? What if your host *wants to run you in 1000
threads*?

Simply put, just exposing the underlying C functions to Python doesn't work
very well, and a Python-like C library is very awkward to use in a language
with a different set of assumptions (C++, Haskell, Rust and the MLs, and lisp
comes to mind). A well designed Python library feels as if it's Pythons all the
way down.

Fast
~~~~
Speed is important. A well-written library will likely see much use, so there's
a substantial return-of-investement. More importantly, it allows for even more
data processed faster, which means money.

As a library writer, you never really get to assume how fast is *fast enough*
for your clients, because you never know what requirements they have. You also
don't really know what infrastructure and runtimes are around (save your host
language), so a lean core is very useful. That also means sometimes choosing between potential
safety for potential speed.

That, in practice, means only a handful of languages are really an option. For
segyio, we ended up on plain C99 for the core itself, but if that choice came
up again it would be C++.

Portable
~~~~~~~~
We know that most of our machines today are amd64 linux, but seismic processing
might occasionally be done on different architectures and operating systems.
For us, this portability was important enough to warrant C (or C++), which
granted were top choices anyway, but now left out languages like D and Rust.
Available skillsets and experience helped that choice.

For reference, since its inclusion in debian, segyio runs on different
`architectures <https://packages.debian.org/sid/libsegyio1>`_:

- alpha
- amd64
- arm64
- armel
- armhf
- hppa
- i386
- kfreebsd-amd64
- kfreebsd-i386
- m68k
- mips
- mips64el
- mipsel
- powerpcspe
- ppc64
- ppc64el
- s390x
- sh4
- sparc64
- x32

Stable and future proof
~~~~~~~~~~~~~~~~~~~~~~~
A stable API and ABI helps keeping users happy, as it makes upgrades safe,
efficient, and easy. It is *very* annoying when code that used to work and was
correct stops working, and we never want our users to be careful with upgrades.

Of course, this introduce a new set of problems, because now you need to write
core functionality in such a way that the *need* for breakage is minimal. It's
especially problematic when it turns out a function didn't *quite* get it
right, and just adding one parameter, or changing its type, would fix it. Which
it would, but it would also break downstream programs.

In Python, it's usually fairly easy to make backwards compatible changes, in C
it's a bit harder. This aspect in particular will be discussed in length in
later sections.

Multiple host languages
~~~~~~~~~~~~~~~~~~~~~~~
Finally, one of the original requirements of segyio was to make it useable for
Matlab. It still is, although it's rough, riddled with legacy, and not really
used by us at (a comedy troupe ate its lunch). But being able to use multiple
languages was crucial to us, which heavily influenced the design.

At the time of writing, a C++ front for segyio is in development. It's shaping
up to look very different from the C core library, and intended for downstream
consumption. We've worked it into a few in-house projects, but it's a living
example of the reusability of the core library's design.

About SEG-Y
-----------
The SEG-Y format was standardised in 1975, in an age where IBM dominated the
computer industry, and magnetic tape was the primary mean of data exchange.
Because of this, the standard details a lot of aspects that consumers don't
really care that much about. What they do care about is the ability to access
the data stored in this format, in a way that's quick and easy and robust.

Summary
-------
This section fleshes out the context and requirements that underpins the desgin
of segyio, and provides a rationale for decisions made, that will be discussed
in later sections. In short, segyio should be:

- Useful for creating new libraries (in different languages)
- Fast
- Portable
- Stable
