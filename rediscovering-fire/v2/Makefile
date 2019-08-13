LATEXMK := latexmk

.PHONY: all clean deps

all: slides

slides:
	$(LATEXMK) -pdf rediscovering-fire

clean:
	$(LATEXMK) -C rediscovering-fire
	rm -f rediscovering-fire.nav rediscovering-fire.snm rediscovering-fire.vrb
	rm -f equinor-red-eps-converted-to.pdf

deps:
	apt-get install latexmk texlive-latex-extra texlive-science texlive-font-utils
