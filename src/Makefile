# Set the flags for the C compiler
CFLAGS= -Wall -pedantic -std=c99

# Build rule for the final executable
emulate: emulate.o input.o types.h
	$(CC) emulate.o input.o -o emulate

# Build rules for the .o files
emulate.o: emulate.c input.h
	$(CC) $(CFLAGS) emulate.c -c -o emulate.o
input.o: input.c input.h
	$(CC) $(CFLAGS) input.c -c -o input.o

# Rule to clean generated files
clean:
	rm -f emulate emulate.o input.o

# Tell make that ‘clean’ is not a real file
.PHONY: clean
