PREFIX = /home/lycantrophe/src/gcc/root/

GCOV = $(PREFIX)bin/gcov -bc
CC   = $(PREFIX)bin/gcc -fprofile-conditions
CXX  = $(PREFIX)bin/g++ -fprofile-conditions

.PHONY:
dots:
	mkdir -p unprocessed-dots
	cd unprocessed-dots && $(CC) --coverage ../gcov-19.c | \
		csplit \
			--elide-empty-files \
			--prefix=cfg- \
			--suffix-format="%03d.dot" \
			--digits 3 \
			- "/.* {/" "{*}"
