# Test all compilation options

PROGS=bench_Os bench_O1 bench_O2 bench_O3
PROGS+=bench64_Os bench64_O1 bench64_O2 bench64_O3

SRC=benchmark.c benchmark_data.c
#CFLAGS=-std=c11 -g -Wall c11 doesn't have the !@# endian macros
CFLAGS=-std=gnu99 -g -Wall
H64=-DHAVE_64BIT_ARCH

all: $(PROGS)

bench_Os: $(SRC)
	$(CC) $(CFLAGS) -Os $(SRC) -o $@
bench_O1: $(SRC)
	$(CC) $(CFLAGS) -O1 $(SRC) -o $@
bench_O2: $(SRC)
	$(CC) $(CFLAGS) -O2 $(SRC) -o $@
bench_O3: $(SRC)
	$(CC) $(CFLAGS) -O3 $(SRC) -o $@

bench64_Os: $(SRC)
	$(CC) $(CFLAGS) -Os $(H64) $(SRC) -o $@
bench64_O1: $(SRC)
	$(CC) $(CFLAGS) -O1 $(H64) $(SRC) -o $@
bench64_O2: $(SRC)
	$(CC) $(CFLAGS) -O2 $(H64) $(SRC) -o $@
bench64_O3: $(SRC)
	$(CC) $(CFLAGS) -O3 $(H64) $(SRC) -o $@

clean: 
	rm -f $(PROGS) gmon.out
