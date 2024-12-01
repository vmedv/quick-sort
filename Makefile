TGDIR	 := target
SRCDIR	 := src
TESTDIR	 := test
BENCHDIR := bench

CILKINSTALLATION := /opt/opencilk
CC	 := $(CILKINSTALLATION)/bin/clang++
CCFLAGS	:= -O3 -fopencilk -std=c++20 -I$(CILKINSTALLATION)/lib/clang/16/include -Isrc -Itest

all:
	@make build-test
	@make build-bench

build-test:
	mkdir -p $(TGDIR)
	$(CC) $(CCFLAGS) $(TESTDIR)/test.cpp -o $(TGDIR)/test

run-test:
	@make build-test
	./target/test

build-bench:
	mkdir -p $(TGDIR)
	$(CC) $(CCFLAGS) $(BENCHDIR)/bench.cpp -o $(TGDIR)/bench

run-bench:
	@make build-bench
	CILK_NWORKERS=4 ./target/bench

clean:
	rm target/test target/bench
