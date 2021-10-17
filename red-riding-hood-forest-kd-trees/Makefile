talk.pdf: talk.md Makefile
	pandoc \
		-s talk.md \
		-t beamer \
		-o talk.pdf \
		--listings \
		--template=eisvogel.tex \
		--dpi 300 \
		--pdf-engine=xelatex


@PHONY: clean
clean:
	rm -f talk.pdf
