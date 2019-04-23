CC = gcc
VPATH = test/

test: unit_tests.c
	cc test/unit_tests.c -o test/unit_tests.out && ./test/unit_tests.out
