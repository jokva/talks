##################
Rediscovering fire
##################

This article is written as preparation material to the *Rediscovering fire - on
designing portable multi-language libraries* talk at `NDC Techtown
<https://ndctechtown.com/talk/rediscovering-fire-on-designing-portable-multi-language-libraries/>`_,
and will largely describe the lessons learned designing and maintaining the
segyio library. The topics disussed will have wider applicability, but will
point to what, how, and why things were done as they were in segyio. In
essence, this document will attempt to articulate some insights in designing
libraries for libraries.

As the name implies, these lessions aren't new. Segyio draws inspiration from
several libraries, and relies on the experience of thousands of developers of
the past and the present.

Sections
========

.. toctree::
   :maxdepth: 2

   context
   allocation

About segyio
============
segyio_ is a fairly small library for reading and writing seismic data in the
SEG-Y_ format. It consists of a fairly low-level *core* library, targeting
library developers and written in C99, and multiple end-user facing libraries,
most notably Python.

.. _segyio: https://github.com/statoil/segyio/
.. _SEG-Y: https://en.wikipedia.org/wiki/SEG-Y

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
