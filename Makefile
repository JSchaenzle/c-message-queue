CC = gcc
VPATH = test/

test: unit_tests.c
	gcc unit_tests.c -o test/unit_tests.out && ./test/unit_tests.out
