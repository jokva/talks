Virtual functions in C
======================

Hi & welcome.

- Inspiration from real-world project
- Wanted fairly simple interfaces that could be ad-hoc extended (for multiple
  back ends)
- C interface
- Realised half-way through initial design I was really just implementing the
  virtual keyword, without the safety net

Warmup - Let's talk about objects
---------------------------------
In C, we have two ways of constructing objects: "vertical" stacking (the
struct) and horizontal stacking (the array).

- Not quite the object in object-oriented programming - Objects here also means
  ints, floats, small arrays.
- "A thing with an address"
- Anything constructed this way is in turn a new object

sizeof exercise
~~~~~~~~~~~~~~~

.. include:: warmup/1-sizeof.cpp
   :code: cpp

::

   make warmup/sizeof

   warmup/1-sizeof.cpp, update in-place

   sizeof(int)
   sizeof(struct {int})
   sizeof(struct {int int})
   sizeof(struct {int c})

   sizeof(int[3])
   sizeof(struct {int int}[3])

methods exercise
~~~~~~~~~~~~~~~~

This is pretty straight-forward C++ 

warmup/2-methods.cpp

.. include:: warmup/2-methods.cpp
   :code: cpp

:code:`make warmup/methods`

Let's port it to C

- :code:`make warmup/methods.c`
- compare side-by-side to C++
- Solution in warmup/3-methods-1.c warmup/3-methods-2.c

First try:

.. code-block:: c

   // 3-methods-1-basic.c

   typedef struct C {
      int x;
      void (*increment)(struct C*);
      int (*get)(const struct C*);
   } C;

Super inefficient, grows with number of methods, clumsy calling

Second try:

.. code-block:: c

   // 3-methods-2.c

   void C_increment(C* self) {
      self->x++;
   }

Uses "C namespacing", cannot replace methods at runtime, probably faster.

Conclusion
~~~~~~~~~~
Methods are fairly simple to emulate, albeit more clumsy and with C style
namespacing

Short break
===========
Time to write questsions, get some drinks

Reference program
=================
:code:`make reference/cat`

reference/, this program has:

- Inheritance
- Non-virtual functions
- (Pure) Virtual mutable functions
- (Pure) Virtual const functions
- Dynamic cast

Skim through reference/ref.cpp

inheritance.c
=============
(C1x §6.7.2.1.13: "A pointer to a structure object, suitably converted,
points to its initial member ... and vice versa. There may be unnamed
padding within as structure object, but not at its beginning.")

.. include:: solutions/inheritance.c
   :code: c

C++ gives us:

- Automatic name resolution of parent's members in children (no self->parent)
- Methods defined on parent implicitly available on instances of children
- Parents unaware of their children
- References to children implicitly convertible to parent, e.g. for function calls

Visualize what's happening with :code:`make viz/inheritance`

Questions?

Break
=====

Port cfile to C
===============

Files: file.h, file.c

Implement side-by-side with reference/file.hpp

.. include:: solutions/file.h
   :code: c


.. include:: solutions/file.c
   :code: c


interface.c
===========
So far, everything has been static. Time to runtime dispatch a function.

:code:`make interface`

.. include:: solutions/interface.c
   :code: c

Demo override by replacing function in interface (noisy)

Some notes:

- Interface is a separate parameter passed just-in-time
- Individual functions can be replaced, as long as signatures match
- This is run-time dispatch via function pointers

Some problems:

- Unergonomic; two pointers (interface and data) that must always go together
- Error prone; for the same reason

How do we improve this?

Break
=====

vtable.c
========

:code:`make vtable`

.. include:: solutions/file-vtable.h
   :code: c

.. include:: solutions/vtable.c
   :code: c

EXTRA: make cfile functions take :code:`cfile*` instead of casting. vtable take
void ptr


Dynamic cast
============

.. code:: c

   #define DYNAMIC_CAST(type, ptr) \
      *(uintptr_t**) &(*f) == (uintptr_t*) &(type ## _vtable) \
      ? (type*)ptr : NULL


.. include:: solutions/dynamic-cast.c
   :code: c
