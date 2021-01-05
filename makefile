all: frequency

frequency: frequency.c
	gcc -Wall -g -o frequency frequency.c 

clean: frequency

.PHONY: all clean



