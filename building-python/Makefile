LATEXMK := latexmk

.PHONY: all clean deps

all: slides

slides:
	$(LATEXMK) -e '$$pdflatex=q/pdflatex %O -shell-escape %S/' -pdf building-python

clean:
	$(LATEXMK) -C building-python
	rm -f building-python.nav building-python.snm building-python.vrb
	rm -f equinor-red-eps-converted-to.pdf

deps:
	apt-get install latexmk texlive-latex-extra texlive-science texlive-font-utils
