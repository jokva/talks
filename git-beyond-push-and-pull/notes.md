# 50/72 - motivation

Linus is pretty clear on this - the only time proper wrapping can happen is
write time, because some lines might need to be long, such as literal quotes,
urls, other special formatting. Breaking those with soft wrapping would be
awful, so hard wrapping it is. 72 is just a practical value.

# Writing messages - imperative subject
Good examples:

- src/gcc - `git log --oneline`

# Writing messages - don't repeat the patch
`make gcc-ex-1`

# git stage
Two-phase commit (stage; commit-with-message) is a _feature_.
Permits crafting commits from a _subset_ of changes on disk.

I have never understood the complaint about commit not doing anything without
add. The alternative (commit being "eager") would mean only being able to
support "add ." or "add -p && commit"

Example: Without printf, debug info, diagnostics

Example motivation: doing a change, spot a tiny improvement (typo, add const
etc.). Just fix-add-commit right away, or fix now and add/don't to the
in-flight commit later

# git rebase
segyio
```
git rebase --exec ./segyio-rebase.sh HEAD~N
```


# git bisect

Example from gcc. Key revisions are:

9dc18fca431626404b0692c689a2e103666e7adb
    - Last commit *before* the fix was applied
1eb90f46c16453f72dc119ba20b07053a15b452d
    - Commit with regression

```
git rev-list ndc/first-bad releases/gcc-12.2.0 --oneline --count
git bisect start
git bisect bad ndc/first-bad
git bisect good releases/gcc-12.2.0
./test.sh # run manually
git bisect run ./test.sh
```

# git format-patch
In some cases, format-patch may be the only way to move patches
back/forward across aggressive renames

# git send-email
Some projects are still developed mainly on mailing list. Notable examples are
linux, gcc, emacs.

The email workflow might sound primitive, but it is very nice. It comes with
some nice features: no sign-ups, does not require much shared infrastructure,
is and feels truly distributed. Even if you mainly synchronize with something
central (github, gitlab) sometimes it doesn't work well (no write permissions,
new team members etc.) and send-email means you can still work.

# Story time
Fix the Zelda: The Wind Waker heat effect glitch.

Let's talk a bit about this bug. 12nd oldest bug not fixed in Dolphin, it was a
lot of fun to debug and it kept me busy for a while :)

Shoutout to Nintendo for framework.map, without which this could have taken a
lot longer.

Basic debugging using apitrace shows that the heat effect is rendered in an
interesting way:
* An EFB copy texture is created, using the hardware scaler to divide the
  texture resolution by two and that way create the blur effect.
* This texture is then warped using indirect texturing: a deformation map is
  used to "move" the texture coordinates used to sample the framebuffer copy.

Pixel shader: http://pastie.org/private/25oe1pqn6s0h5yieks1jfw

Interestingly, when looking at apitrace, the deformation texture was only 4x4
pixels... weird. It also does not have any feature that you would expect from a
deformation map. Seeing how the heat effect glitches, this deformation texture
being wrong looks like a good candidate for the problem. Let's see how it's
loaded!

By NOPing random calls to GXSetTevIndirect, we find a call that when removed
breaks the effect completely. The parameters used for this call come from the
results of methods of JPAExTexShapeArc objects. 3 different objects go through
this code path, by breaking each one we can notice that the one "controlling"
the heat effect is the one at 0x81575b98.

Following the path of this object a bit more, we can see that it has a method
called "getIndTexId". When this is called, the returned texture ID is used to
index a map and get a JPATextureArc object stored at 0x81577bec.

Nice feature of JPATextureArc: they have a getName method. For this object, it
returns "AK_kagerouInd01". We can probably use that to see how this texture
should look like, by loading it "manually" from the Wind Waker DVD.
Unfortunately I don't know how to do that. Fortunately @Abahbob got me the
texture I wanted in less than 10min after I asked him on Twitter.
AK_kagerouInd01 is a 32x32 texture that really looks like a deformation map:
http://i.imgur.com/0TfZEVj.png . Fun fact: "kagerou" means "heat haze" in JP.

So apparently we're not using the right texture object when rendering! The
GXTexObj that maps to the JPATextureArc is at offset 0x81577bf0 and points to
data at 0x80ed0460, but we're loading texture data from 0x0039d860 instead.

I started to suspect the BP write that loads the texture parameters "did not
work" somehow. Logged that and yes: nothing gets loaded to texture stage 1! ...
but it turns out this is normal, the deformation map is loaded to texture stage
5 (hardcoded in the DOL). Wait, why is the TextureCache trying to load from
texture stage 1 then?!

Because someone sucked at hex.

Fixes issue 2338.


- source: https://dolphin-emu.org/blog/2014/01/06/old-problem-meets-its-timely-demise/
- git-ref: ed67d1ae2f9693ed42867a2e79b7cae4427574e3
