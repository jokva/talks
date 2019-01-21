JOBNAME=working-git

all: main.tex
	latexmk \
	-pdf \
	-jobname=$(JOBNAME) \
	-latexoption=-halt-on-error \
	main.tex

.PHONY: clean
clean:
	latexmk -C -jobname=$(JOBNAME)
	rm -f $(JOBNAME).nav $(JOBNAME).snm $(JOBNAME).vrb
