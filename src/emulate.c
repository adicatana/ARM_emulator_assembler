#include "input.h"
#include "types.h"
#include "pipeline_cycle.h"
#include "utils.h"

char *get_type(instruction_t e) {
	switch (e) {
		case 0: return "DATA_PROCESSING";
		case 1: return "MULTIPLY";
		case 2: return "DATA_TRANSFER";
		case 3: return "BRANCH";
		case 4: return "HALT";
		default: return "NOTHING";
	}
}


int main(int argc, char** argv) {

    if (argc > 1) {

		memory_t *memory = read_from_binary(argv[1]);

		memset(registers, 0, NO_OF_REGISTERS);

		if (memory == NULL) {
			perror("Erorr reading from binary\n");
			exit(EXIT_FAILURE);
		}
		
		uint32_t to_decode = -1;
		uint32_t current_instruction = -1;		
		instruction to_execute;

		do {
			
			printf("%s%x\n", "Starting the cycle... at PC: ", registers[PC_REG]);		
			
			printf("%s\n", "Fetching...");			
			current_instruction = fetch(memory, registers[PC_REG]);
			printf("%x fetched\n", current_instruction);

			printf("%s\n", "Decoding...");
			instruction decoded = decode(to_decode);
			printf("%x decoded as a %s instruction\n", decoded.code, get_type(decoded.type));			

			printf("%s %x\n", "Executing...", to_execute.code);			
			execute(to_execute, memory, registers);
			
			to_execute = decoded;
			to_decode = current_instruction;

			registers[PC_REG] += 4;
			
			printf("%s\n\n", "Cycle ended.");
			
		} while (to_execute.type != HALT);

		print_state(memory, registers);

		free(memory);

        return 0;
    
    } else {
    
        return -1;
    
    }

}
