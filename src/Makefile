# Set the flags for the C compiler
CFLAGS= -Wall -pedantic -std=c99

all: emulate assemble

# Build rule for the final executable
emulate: emulate.o input.o pipeline_cycle.o multiply.o data_processing.o data_transfer.o branch.o cond_flags.o utils.o

assemble: assemble.o utils.o encode.o

# Rule to clean generated files	
clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
