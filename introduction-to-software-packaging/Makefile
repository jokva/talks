.PHONY: all
all: slides.html

PREFIX = out

# This build works fine outside of pandoc, but the rendering on older pandocs
# relies on a relative-path copy of reveal.js. Newer pandocs (post
# https://github.com/jgm/pandoc/commit/7c6dbd37eb3e785f875e0030d723e422db72d453)
# defaults to an online copy.
slides.html: slides.md slides.css Makefile
	pandoc --to revealjs --standalone \
		-V revealjs-url=reveal.js \
		-V hash=true \
		--css git.css \
		$(opts) $< -o $@

# TODO: "install" reveal.js here?
install: slides.html slides.css
	mkdir -p $(PREFIX)
	cp slides.html slides.css $(PREFIX)/

.PHONY: pack
pack: slides.md slides.css default.guix Makefile $(wildcard img/*)
	rm -f pack
	guix time-machine --commit=v1.4.0 -- build -f default.guix --quiet --root=$@
	@echo firefox $@/slides.html to start the slideshow
