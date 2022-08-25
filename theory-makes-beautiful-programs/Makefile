DOCNAME=techtown-2022

PDFLATEX="pdflatex -interaction=nonstopmode -synctex=1"

.PHONY: $(DOCNAME).pdf all clean

$(DOCNAME).pdf: $(DOCNAME).tex
	latexmk -pdf -pdflatex=$(PDFLATEX) -recorder -use-make $(DOCNAME).tex

watch: $(DOCNAME).tex
	latexmk -pvc -pdf -pdflatex=$(PDFLATEX) -use-make $(DOCNAME).tex

clean:
	latexmk -CA
