---
title: Open source in the subsurface
author: Jørgen Kvalsvik
date: May 13, 2021
---

# Software and source code

---

- Runnable programs are built from _source code_
- Source code is translated to or interpreted as computer instructions

---

Source code is for humans

---

Source code - hello.c

    #include <stdio.h>
    int main() {
        puts("Hello, world!");
    }

---

Human-readable "machine instructions" - hello.s

    .LC0:
            .string "Hello, world!"
            .section        .text.startup,"ax",@progbits
            .p2align 4,,15
            .globl  main
            .type   main, @function
    main:
    .LFB11:
            .cfi_startproc
            subq    $8, %rsp
            .cfi_def_cfa_offset 16
            leaq    .LC0(%rip), %rdi
            call    puts@PLT
            xorl    %eax, %eax
            addq    $8, %rsp
            .cfi_def_cfa_offset 8
            ret
            .cfi_endproc

---

Machine readable instructions - hello.o

    7F 45 4C 46 02 01 01 00 00 00 00 00 00 00 00 00 01 00 3E
    00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 F8 02 00 00 00 00 00 00 00 00 00 00 40 00 00 00 00
    00 40 00 0E 00 0D 00 48 65 6C 6C 6F 2C 20 77 6F 72 6C 64
    21 00 00 00 48 83 EC 08 48 8D 3D 00 00 00 00 E8 00 00 00
    00 31 C0 48 83 C4 08 C3 00 47 43 43 3A 20 28 44 65 62 69
    61 6E 20 38 2E 33 2E 30 2D 36 29 20 38 2E 33 2E 30 00 00
    00 00 00 14 00 00 00 00 00 00 00 01 7A 52 00 01 78 10 01
    1B 0C 07 08 90 01 00 00 14 00 00 00 1C 00 00 00 00 00 00
    00 17 00 00 00 00 44 0E 10 52 0E 08 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
    00 00 00 04 00 F1 FF 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 03 00 01 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 03 00 02 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 03
    00 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 03 00 04 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 03 00 05 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 03 00 08 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    03 00 09 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 09 00 00 00 00 00 04 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 03 00 07 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 0E 00 00 00 12 00 05 00
    00 00 00 00 00 00 00 00 17 00 00 00 00 00 00 00 13 00 00
    00 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 29 00 00 00 10 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 68 65 6C 6C 6F 2E 63 00 2E 4C 43
    30 00 6D 61 69 6E 00 5F 47 4C 4F 42 41 4C 5F 4F 46 46 53
    45 54 5F 54 41 42 4C 45 5F 00 70 75 74 73 00 00 00 07 00
    00 00 00 00 00 00 02 00 00 00 09 00 00 00 FC FF FF FF FF
    FF FF FF 0C 00 00 00 00 00 00 00 04 00 00 00 0D 00 00 00
    FC FF FF FF FF FF FF FF 20 00 00 00 00 00 00 00 02 00 00
    00 06 00 00 00 00 00 00 00 00 00 00 00 00 2E 73 79 6D 74
    61 62 00 2E 73 74 72 74 61 62 00 2E 73 68 73 74 72 74 61
    62 00 2E 74 65 78 74 00 2E 64 61 74 61 00 2E 62 73 73 00
    2E 72 6F 64 61 74 61 2E 73 74 72 31 2E 31 00 2E 72 65 6C
    61 2E 74 65 78 74 2E 73 74 61 72 74 75 70 00 2E 63 6F 6D
    6D 65 6E 74 00 2E 6E 6F 74 65 2E 47 4E 55 2D 73 74 61 63
    6B 00 2E 72 65 6C 61 2E 65 68 5F 66 72 61 6D 65 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 1B 00 00 00 01 00 00 00 06 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 21 00 00 00 01
    00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    40 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 27 00 00 00 08 00 00 00 03 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 40 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 2C 00 00 00 01 00 00 00 32 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 00 00
    00 00 00 0E 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    01 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 40 00 00
    00 01 00 00 00 06 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 50 00 00 00 00 00 00 00 17 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 10 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 3B 00 00 00 04 00 00 00 40 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 38 02 00 00 00 00 00 00 30 00
    00 00 00 00 00 00 0B 00 00 00 05 00 00 00 08 00 00 00 00
    00 00 00 18 00 00 00 00 00 00 00 4E 00 00 00 01 00 00 00
    30 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 67 00 00
    00 00 00 00 00 1D 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 01 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 57
    00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 84 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 6C 00 00 00 01 00 00 00 02 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 88 00 00 00 00 00 00 00
    30 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 08 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 67 00 00 00 04 00
    00 00 40 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 68
    02 00 00 00 00 00 00 18 00 00 00 00 00 00 00 0B 00 00 00
    09 00 00 00 08 00 00 00 00 00 00 00 18 00 00 00 00 00 00
    00 01 00 00 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 B8 00 00 00 00 00 00 00 50 01 00 00 00
    00 00 00 0C 00 00 00 0B 00 00 00 08 00 00 00 00 00 00 00
    18 00 00 00 00 00 00 00 09 00 00 00 03 00 00 00 00 00 00
    00 00 00 00 00 00 00 00 00 00 00 00 00 08 02 00 00 00 00
    00 00 2E 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 11 00 00 00
    03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00 80 02 00 00 00 00 00 00 76 00 00 00 00 00 00 00 00 00
    00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00
    00 00 00

hexdump -v -e '/1 "%02X "' hello.o

---

Translation to computer instructions is a _one-way process_

---

Computer instructions effectively

- Cannot be _studied_
- Cannot be _modified_
- Cannot be _adapted_

---

Conclusion

> To change a program, you need the source

# Free and open source software

---

What does it even mean?

---

Open source is a _legal_ aspect, not a technical one

---

- Controls what you can and cannot do with source code
- Definition is owned by the Open Source Initiative (OSI)

https://opensource.org/

---

>  in brief, they allow software to be freely used, modified, and shared

https://opensource.org/licenses

---

Common licences

- GNU General Public License (GPL)
    + Lesser (LGPL)
    + Affero (AGPL)
- MIT
- BSD
- Apache

---

No open source license forbid commercial use

All come with a _cost_

---

All licenses rely on copyright

---

Observation:

> Open source is a legal-only, but changes *attitude*

# Open source in O&G

---

The O&G is traditionally **very** protective and "share-unfriendly"

---

- A very conservative industry
- Applies to more than software
- This is changing slowly

---

O&G attitude:

> Everything worth using costs (a lot of) money

---

The _cost_ of software was not a big issue; high cost, high-complexity,
high-revenune business

---

Proprietary software means:

- Small players cannot afford expensive licenses
- Often difficult to upgrade or change provider
    + e.g. petrel vs openworks
- High barrier of entry for "fresh blood"
- All development comes at a (high) vendor cost, little customer control

---

Software becomes _increasingly more important_ in the industry

. . .

... which changes the need for control and ownership

---

Opinion:

> O&G is not a zero-sum game

Your gain is not my loss

---

The O&G industry today is deeply reliant on OSS

(we'll see some examples)

---

Norwegian phrase:

> Let's make each other good

# Why?

---

The battlefield has moved in the computer space

---

## Example: wells

- Before
    + Analysis was restricted to a single or handful of wells
    + Fairly manual work, assisted tools like petrel and techlog
- Now
    + Analysis or search through tens of thousands of wells
    + Automated processing
    + Statistics, ML, and predictions
    + More bespoke

---

For large-scale processing you need programmable and boring tools

---

A form of commoditization, and a level playing field

---

### Example projects

---

### I/O

- segyio
- lasio
- dlisio

---

### Maths and stats

- numpy, scipy
- Pandas
- TensorFlow, PyTorch

---

### Modelling and misc

- GemPy
- welleng, wellpathpy, welly
- devito
- madagascar, seismic unix
- opendtect

---

### For completeness

- linux
- git
- gcc and other compilers
- databases (influx, postgres, sqlite, maria etc)

---

The fight is _how well_ you can:

- Leverage your toolkit
- Experiment and understand
- Build new and novel applications

---

This requires the ability to _study_ and _modify_

---

In effect, OSS is 

- Faster
    + To adapt and modify
- Cheaper
    + Build on pre-existing work, not emulate or re-implement from scratch
    + To maintain, don't need to painfully hide source
- More available
    + Most OSS software is free (in money)
    + No trial period, no expensive licence

---

Opinion:

> The O&G industry cares neither for open source nor proprietary software

. . .

The industry cares about _value_

---

Opinion:

> (Bespoke) Software is an investment, and an open license gives higher returns

---

The ability to _modify_ and _operate_ is more valuable than the code itself

---

A community gives more value than "forcing" competitors to implement the same
features

---

If _value_ in O&G comes from how software is combined with **domain knowledge**
and **data**, not from the source code ...


. . .


... then open source will generally be more valuable

---

> Why not piggy back on your competitor?

. . .

You can, but will always be one step behind

# Projects and community

---

Common issues and questions

---

> ... but I have nothing to contribute

. . .

Sure you do!

- Questions & clarifications
- Documentation
- Bug reports
- Feature suggetions
- Translations
- Testing

---

> ... who would care about this?

. . .

You would be surprised

---

> ... it's not good enough

. . .

You would be surprised

# Post script

---

![](img/swung_round_no_text.png)

https://softwareunderground.org/

---

<figure>
    ![](img/fireplace.jpg){ style="width: 100%; margin: auto;" }
</figure>

---

References:

The Fireplace by Robbie Sproule CC-BY-2 https://www.flickr.com/photos/85278812@N00
