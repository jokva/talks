empty :=
space := $(empty) $(empty)

srcfmt += markdown_strict
srcfmt += footnotes
srcfmt += backtick_code_blocks
srcfmt += auto_identifiers
srcfmt += yaml_metadata_block


opts += --dpi=300
opts += --slide-level 2
opts += --shift-heading-level-by=0
opts += -V classoption:aspectratio=169
opts += -f $(subst $(space),+,$(srcfmt))

.PHONY: all
all: main.pdf notes.pdf

main.pdf: main.md Makefile $(imgs)
	nix-shell -p pandoc --run "pandoc -t beamer $(opts) -s $< -o $@"

notes.pdf: notes.md Makefile
	nix-shell -p pandoc --run "pandoc -s $< -o $@"

gcc-examples += 12b78b0b42d53019eb2c500d386094194e90ad16

.PHONY:
gcc-ex-%:
	cd ~/src/gcc && git log $(word $*, $(gcc-examples))
