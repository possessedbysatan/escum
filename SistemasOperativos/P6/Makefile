CC=gcc
CFLAGS=-lm -Wpedantic -Wshadow -Wall -O3 -pthread
all: principal 
principal:
	$(CC) $(CFLAGS) memcomp.c -o memcomp
	$(CC) $(CFLAGS) Tuberias.c -o tuberias
clean:
	rm memcomp tuberias Inversa*.txt

