CC = gcc -std=c99
CFLAGS = -I.
PROGRAM = banker

all: banker.c
	$(CC) -o $(PROGRAM) banker.c $(CFLAGS)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm $(PROGRAM)
