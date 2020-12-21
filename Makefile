all: processor.c controller.c
	gcc -o processor processor.c
	gcc -o controller controller.c

.PHONY: run

run: 
	./processor &
	./controller
