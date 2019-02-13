OUTPUT := segyio-description

all:
	$(PDFLATEX) -output-format=pdf $(OUTPUT)
	$(BIBTEX) bibtex $(OUTPUT)
	$(PDFLATEX) -output-format=pdf $(OUTPUT)
	$(PDFLATEX) -output-format=pdf $(OUTPUT)

clean:
	rm -rf *.aux *.bbl $(OUTPUT).pdf $(OUTPUT).log $(OUTPUT).out $(OUTPUT).blg
