CC=gcc
GDB=-g
CFLAGS=-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11
PARALELA= -fopenmp
OPT=-O2
PROF=-pg
PATHbin=./bin/
PATHrec=./src/
PATHout=./out/
PATHlog=./log/
PATHtest=./test/

lab4: $(PATHbin)main

$(PATHbin)main: main.c $(PATHrec)PGM_in_c.c 
	mkdir -p $(PATHbin) 
	$(CC) $(CFLAGS) $(OPT) $(PARALELA) -o $(PATHbin)main main.c

clean:
	rm -f -d $(PATHbin)* $(PATHbin) $(PATHlog)* $(PATHlog) $(PATHout)* $(PATHout) ./profiling/ejecucion.txt $(PATHtest)*.txt
