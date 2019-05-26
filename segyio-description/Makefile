PDFLATEX := pdflatex
LATEXMK := latexmk
BIBTEX := bibtex
OUTPUT := segyio-description

.PHONY: all clean deps

all:
	$(PDFLATEX) -output-format=pdf $(OUTPUT)
	$(BIBTEX) $(OUTPUT)
	$(PDFLATEX) -output-format=pdf $(OUTPUT)
	$(PDFLATEX) -output-format=pdf $(OUTPUT)

poster: *.py read-trace.eps py_logo.pdf c++.pdf equinor-red.eps
	$(LATEXMK) --shell-escape -pdf segyio-poster

clean:
	rm -f *.aux *.bbl $(OUTPUT).pdf $(OUTPUT).log $(OUTPUT).out $(OUTPUT).blg
	$(LATEXMK) -C segyio-poster
	rm -f read-trace.png read-trace.eps
	rm -f c++.pdf py_logo.pdf

read-trace.eps: read-trace.dot
	dot read-trace.dot -Tps2 -o read-trace.eps -Gbgcolor="transparent"

py_logo.pdf: py_logo.svg
	inkscape py_logo.svg --export-pdf=py_logo.pdf

c++.pdf: c++.svg
	inkscape c++.svg --export-pdf=c++.pdf

deps:
	apt-get install latexmk texlive-latex-extra graphviz inkscape
