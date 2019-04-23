CC = gcc
VPATH = example/:test/

.PHONY: test
test: unit_tests.out
	./test/unit_tests.out

.PHONY: example
example: example.out

example.out: queue.h example/*.c example/*.h
	$(CC) example/*.c -o example/example.out

unit_tests.out: queue.h unit_tests.c
	$(CC) test/unit_tests.c -o test/unit_tests.out 

.PHONY: clean
clean:
	rm -f example/example.out test/unit_tests.out
