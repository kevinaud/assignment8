CFLAGS=-Wall
LIBS=-lcheck
STD=-std=c89

all: expand 

expand: expand.o functions.o
	gcc -o expand expand.o functions.o

expand.o: expand.c functions.o
	gcc $(CFLAGS) $(STD) -c expand.c

functions.o: functions.c functions.h
	gcc $(CFLAGS) $(STD) -c functions.c

test: functions-test
	./functions-test

functions-test: functions-test.o functions.o
	gcc $(STD) -o functions-test functions.o functions-test.o $(LIBS)

functions-test.o: functions-test.c functions.h
	gcc $(CFLAGS) $(STD) -c functions-test.c

functions-test.c: functions-test.check
	checkmk functions-test.check >functions-test.c
