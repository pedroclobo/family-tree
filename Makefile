CC = g++
CFLAGS = -std=c++11 -O3 -Wall -lm
MFLAGS += --no-print-directory

all:: proj

proj: src/proj.cpp
	$(CC) $(CFLAGS) src/proj.cpp -o src/proj

relatorio: docs/relatorio.tex
	(cd docs && pdflatex relatorio.tex)

run:: proj
	./src/proj

clean::
	rm src/proj

tests:: proj
	@$(MAKE) $(MFLAGS) -C tests

benchmarks:: proj
	@$(MAKE) $(MFLAGS) -C benchmarks
