# Set the flags for the C compiler
CFLAGS= -Wall -pedantic -std=c99

# Build rule for the final executable
emulate: emulate.o input.o pipeline_cycle.o multiply.o cond_flags.o

# Rule to clean generated files	
clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate