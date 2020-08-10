talk.pdf: talk.rst $(wildcard solutions/*.c solutions/*.cpp)
	pandoc talk.rst -o talk.pdf

.PHONY: reference/cat
reference/cat:
	g++ -O2 reference/ref.cpp reference/cat.cpp -o reference/cat
	./reference/cat 99-bottles.txt

.PHONY: warmup/sizeof warmup/methods warmup/methods.c
warmup/sizeof:
	g++ -O2 warmup/1-sizeof.cpp -o warmup/sizeof
	warmup/sizeof

warmup/methods:
	g++ -O2 warmup/2-methods.cpp -o warmup/methods
	warmup/methods

warmup/methods.c:
	gcc -std=c99 -O2 warmup/3-methods.c -o warmup/methods-c
	warmup/methods

.PHONY: interface
interface:
	gcc -std=c99 -O2 interface.c file.c -o interface-cat
	./interface-cat 99-bottles.txt

.PHONY: vtable
vtable:
	gcc -std=c99 -O2 vtable.c -o vtable-cat
	./vtable-cat 99-bottles.txt

.PHONY: dynamic-cast
dynamic-cast:
	gcc -std=c99 -O2 dynamic-cast.c -o dynamic-cat
	./dynamic-cat 99-bottles.txt

.PHONY: clean
clean:
	rm -f interface.c cat warmup/methods warmup/sizeof reference/cat
	rm -rf dynamic-cat vtable-cat interface-cat

.PHONY: viz/inheritance
viz/inheritance:
	dot -Gsize=9,15\! -Tpng viz-inheritance.dot | feh -
