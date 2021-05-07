talk.html: talk.md Makefile
	pandoc \
		-s talk.md \
		-o talk.html \
		-t revealjs \
		-V revealjs-url=https://cdn.jsdelivr.net/reveal.js/3.0.0

@PHONY: clean
clean:
	rm -f talk.html
