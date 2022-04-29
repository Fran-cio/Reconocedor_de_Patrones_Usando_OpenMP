CC=gcc
GDB=-g
CFLAGS=-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11
OPT=-O0
PROF=-pg
PATHbin=./bin/
PATHrec=./src/
PATHout=./out/
PATHlog=./log/
PATHtest=./test/

lab4: $(PATHbin)main

$(PATHbin)main: main.c 
	mkdir -p $(PATHbin) 
	$(CC) $(CFLAGS) $(OPT) $(GDB) -o $(PATHbin)main main.c

clean:
	rm -f -d $(PATHbin)* $(PATHbin) $(PATHlog)* $(PATHlog) $(PATHout)* $(PATHout) ./profiling/ejecucion.txt $(PATHtest)*.txt
