LATEXMK := latexmk

.PHONY: all clean deps

all: slides

slides:
	$(LATEXMK) -pdf almost-free-lunch

clean:
	$(LATEXMK) -C almost-free-lunch
	rm -f almost-free-lunch.nav almost-free-lunch.snm almost-free-lunch.vrb

deps:
	apt-get install latexmk texlive-latex-extra texlive-science texlive-font-utils
