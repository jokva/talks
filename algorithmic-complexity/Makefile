JOBNAME=complexity

all: main.tex growth1.png growth2.png
	latexmk \
	-pdf \
	-jobname=$(JOBNAME) \
	-latexoption=-halt-on-error \
	main.tex

growth1.png: growth.gnuplot
	gnuplot -c growth.gnuplot 2000 > growth1.png

growth2.png: growth.gnuplot
	gnuplot -c growth.gnuplot 220000 > growth2.png

.PHONY: clean
clean:
	latexmk -C -jobname=$(JOBNAME)
	rm -f $(JOBNAME).nav $(JOBNAME).snm $(JOBNAME).vrb
	rm -f growth1.png growth2.png
