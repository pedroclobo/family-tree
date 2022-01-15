CC = g++
CFLAGS = -std=c++11 -O3 -Wall -lm
MFLAGS += --no-print-directory
EXE=../src/proj

all:: run

randGeneoTree: randGeneoTree.cpp
	$(CC) $(CFLAGS) randGeneoTree.cpp -o randGeneoTree

run:: randGeneoTree
	rm output.txt
	bash benchmark.sh

clean::
	rm randGeneoTree output.txt tree
