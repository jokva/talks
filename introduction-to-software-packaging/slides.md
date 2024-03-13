---
title: Introduction to software packaging
---

Who are you?

---

Why are you here?

---

Phases

- Fetch
- Unpack
- Patch
- Configure
- Build
- Test
- Post-build
- Archive

---

```bash
wget https://ftp.gnu.org/gnu/hello/hello-2.12.1.tar.gz
tar xf hello-2.12.1.tar.gz
```
---

```bash
./configure
    --prefix=/opt/booster/usr
    --without-libiconv-prefix
    --without-libintl-prefix
make
```

---

What is in the box?

---

- Assets
    + Binaries, libraries
    + Manuals, documentation
    + Translations, etc.
    + Configuration files
- Metadata
    + File listing
    + Dependency information
    + Version, description, etc.
    + Scripts, pre/post-install

---

Where do we go from here?

---

```bash
wget http://deb.debian.org/debian/pool/main/h/hello/hello_2.10-2_amd64.deb
ar p hello_2.10-2_amd64.deb
```

---

Fetch phase

- http(s), ftp tarballs
- git clone, svn co, hg, cvs
- Misc (NFS/file system, others?)

Pros/cons?

---

Patch phase

---

Configure phase

---

Build phase

---

Post-build phase

---

Archive phase

---

Leveling up

---

GNU Guix

---

Nix
