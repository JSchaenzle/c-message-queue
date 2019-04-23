CC = gcc
VPATH = test/

.PHONY: test
test: unit_tests.out
	./test/unit_tests.out

unit_tests.out: queue.h unit_tests.c
	$(CC) test/unit_tests.c -o test/unit_tests.out 

