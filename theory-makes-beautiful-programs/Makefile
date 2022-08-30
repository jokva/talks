DOCNAME=techtown-2022
.DEFAULT_GOAL := $(DOCNAME).pdf

PDFLATEX="pdflatex -interaction=nonstopmode -synctex=1"

.PHONY: $(DOCNAME).pdf all clean

graph/%.pdf: %.dot
	@mkdir -p graph
	dot $< -Tpdf -o $@

graphs += graph/fig1.pdf
graphs += graph/fig2.pdf
graphs += graph/fig3.pdf
graphs += graph/fig4.pdf

graphs += graph/fig5-1.pdf
graphs += graph/fig5-2.pdf
graphs += graph/fig5-3.pdf
graphs += graph/fig5-4.pdf
graphs += graph/fig5-5.pdf
graphs += graph/fig5-6.pdf
graphs += graph/fig5-7.pdf
graphs += graph/fig5-8.pdf
graphs += graph/fig5-9.pdf
graphs += graph/fig5-10.pdf
graphs += graph/fig5-11.pdf

graphs += graph/fig6-1.pdf
graphs += graph/fig6-2.pdf
graphs += graph/fig6-3.pdf
graphs += graph/fig6-4.pdf
graphs += graph/fig6-5.pdf

graphs += graph/fig7.pdf
graphs += graph/fig8.pdf

graphs += graph/fig9-1.pdf
graphs += graph/fig9-2.pdf
graphs += graph/fig9-3.pdf
graphs += graph/fig9-4.pdf
graphs += graph/fig9-5.pdf

graphs += graph/fig10-1.pdf
graphs += graph/fig10-2.pdf

graphs += graph/fig11-1.pdf
graphs += graph/fig11-2.pdf
graphs += graph/fig11-3.pdf

graphs += graph/fig12-1.pdf
graphs += graph/fig12-2.pdf
graphs += graph/fig12-3.pdf

graphs += graph/fig13-1.pdf
graphs += graph/fig13-2.pdf
graphs += graph/fig13-3.pdf
graphs += graph/fig13-4.pdf
graphs += graph/fig13-5.pdf
graphs += graph/fig13-6.pdf
graphs += graph/fig13-7.pdf
graphs += graph/fig13-8.pdf

$(DOCNAME).pdf: $(DOCNAME).tex $(graphs)
	latexmk -shell-escape -pdf -pdflatex=$(PDFLATEX) -recorder -use-make $(DOCNAME).tex

watch: $(DOCNAME).tex
	latexmk -pvc -pdf -pdflatex=$(PDFLATEX) -use-make $(DOCNAME).tex

clean:
	rm -rf graph
	latexmk -CA
