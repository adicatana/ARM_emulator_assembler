# Set the flags for the C compiler
CFLAGS= -Wall -pedantic -std=c99

# Build rule for the final executable
emulate: emulate.o input.o pipeline_cycle.o
	$(CC) emulate.o input.o pipeline_cycle.o -o emulate

# Build rules for the .o files
emulate.o: emulate.c 
	$(CC) $(CFLAGS) emulate.c -c -o emulate.o
input.o: input.c
	$(CC) $(CFLAGS) input.c -c -o input.o
pipeline_cycle.o: pipeline_cycle.c 
	$(CC) $(CFLAGS) pipeline_cycle.c -c -o pipeline_cycle.o 

# Rule to clean generated files
clean:
	rm -f emulate emulate.o input.o pipeline_cycle.o

# Tell make that ‘clean’ is not a real file
.PHONY: clean
