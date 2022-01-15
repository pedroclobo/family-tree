.SUFFIXES: .in .out .diff
MAKEFLAGS += --no-print-directory
GREEN=$(shell tput setaf 2)
RED=$(shell tput setaf 1)
RESET=$(shell tput op)
OK="$(GREEN)test $< PASSED$(RESET)"
KO="$(RED)test $< FAILED$(RESET)"
EXE=../src/proj

all:: clean
	@$(MAKE) $(MFLAGS) `ls *.in | sed -e "s/in/diff/"`

.in.diff:
	@-$(EXE) < $< | diff - $*.out > $@
	@if [ `wc -l < $@` -eq 0 ]; then echo $(OK); else echo $(KO); fi;

clean::
	@rm -f *.diff
