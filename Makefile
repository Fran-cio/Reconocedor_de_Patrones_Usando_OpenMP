CC=gcc
GDB=-g
CFLAGS=-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11
PARALELA= -fopenmp
OPT=-O2
PATHbin=./bin/
PATHrec=./src/
PATHout=./out/
PATHlib=./lib/

lab4: $(PATHbin)main

$(PATHbin)main: main.c $(PATHrec)PGM_in_c.c $(PATHlib)lib_rec.a
	mkdir -p $(PATHbin) 
	$(CC) $(CFLAGS) $(OPT) $(PARALELA) -o $(PATHbin)main main.c -L$(PATHlib) -l_rec

$(PATHlib)lib_rec.a: $(PATHout)recursos.o  
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)lib_rec.a $(PATHout)recursos.o 

$(PATHout)recursos.o: $(PATHrec)recursos.c $(PATHrec)PGM_in_c.c
	mkdir -p $(PATHout)
	$(CC) $(CFLAGS) $(OPT) $(PARALELA) -c $(PATHrec)recursos.c 
	mv ./recursos.o $(PATHout)/recursos.o



clean:
	rm -f -d $(PATHbin)* $(PATHbin) $(PATHout)* $(PATHout) $(PATHlib)* $(PATHlib) 
