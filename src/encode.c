#include "encode.h"

void execute(char * const instruction) {
	log(("%s\n", instruction));
	char *type = strtok(instruction, " ");
	log(("%s%s\n", "The command is ", type));
}