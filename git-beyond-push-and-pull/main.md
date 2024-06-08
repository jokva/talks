---
title: "git beyond push & pull"
author: "Jørgen Kvalsvik <<j@lambda.is>>"
date: "2023-09-21"
...


### What is this talk?

+ Show-and-tell: a few slightly advanced operations
+ Focus on _what_ you can achieve
+ Guide on crafting commits

---

### What is this talk not?

+ A deep dive into git internals
+ A tour of dark corners and exotic features
+ Introduction to VCS
+ Battle of the VCSs

---

I do _all_ of these things

---

Even in single-person projects

---

`model_2_edits3_james_fixed_final_v3.c`

Good habits
===========
---

###
A well-cared for log is a beautiful and useful thing. git blame, revert,
rebase, log, shortlog and other subcommands come to life.

###
<https://cbea.ms/git-commit/>

---

50/72

---

0.6944444444444444

---

### 50/72
* Subject length max 50
* Line length max 72

---

```
This patch implements another of Uros' suggestions, to investigate a
insvti_lowpart_1 pattern to improve TImode parameter passing on x86_64.


This patch implements another of Uros' suggestions, to investigate a insvti_lowpart_1 pattern to improve TImode
parameter passing on x86_64.
```

---

### 50/72 - motivation
+ `git log --oneline`
+ Subject may be added after verbs, e.g. 'Revert [...]'
+ git does not hard wrap

---

### 50/72 - not arbitrary
- git log does not wrap
    + `80 - (indent + symmetry) = 72`, `indent = 4`
- good for email formatting, room for `> reply` before overflowing 80
- git log/graph often given a small window in IDEs
- subject: used in merge, rebase, shortlog

###
Tim Pope: <https://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html>

---

### Writing messages - imperative subject
- Add ...
- Remove ...
- Prune ...
- Handle ...
- Fix ... (careful)

---

### Answer the question: if applied ...
- this commit will _refactor subsystem X for readability_
- this commit will _update getting started documentation_
- this commit will _remove deprecated methods_
- this commit will _release version 1.0.0_
- this commit will _merge pull request #123 from user/branch_

###
<https://cbea.ms/git-commit/>

---

### Writing messages - don't repeat the patch
- Focus on **why** and **how**
- Summarise research, decisions
- Add references

---

### Writing messages - cool things
- Add tables, links
- Add lists, code listings
- Reference tickets
- Include parts of other commit messages

---

### Focused commits - do one thing (well)
Easier to understand, cherry-pick, merge, review

---

**All** commits should compile and pass tests

---

Public history is immutable

The git stage
=============
---

Changes are _staged_, added to the index, in preparation of the next _commit_

---

`git add --patch`

---

`git reset --patch`

---

`git reset --patch HEAD~1`

---

`git checkout HEAD -p -- PATH`

---

```
$ git log --oneline -n 1 b85d150
b85d150 Remove bootstrap/
$ git checkout b85d150~1 -- bootstrap/defs.py
```

Building histories
==================
---

`git cherry-pick`

---

`git merge refs...`

---

`git rebase`

---

`git rebase --interactive`

---

`git commit --fixup`

---

`git rebase --interactive --autosquash`

Using histories
===============
---

`git shortlog`

---

`git rebase --exec`

---

`git bisect`

To patch or not to patch
========================
---

`git format-patch`

---

`git send-email`

---

`git am`

Misc
====
---

`git log -S<string>`

---

`git grep`

---

`git instaweb`

---

`git archive`

---

`git clean`


Please reach out
================

### 
Jørgen Kvalsvik <<j@lambda.is>>
