#include "input.h"
#include "types.h"
#include "pipeline_cycle.h"

int main(int argc, char** argv) {

    if (argc > 1) {

		memory_t *memory = read_from_binary(argv[1]);

		memset(registers, 0, NO_OF_REGISTERS);

		if (memory == NULL) {
			perror("Erorr reading from binary\n");
			exit(EXIT_FAILURE);
		}
		
		uint32_t previous_instruction = -1;
		uint32_t prev_instruction = -1;
		uint32_t instruction = 4;

		do {
			
			printf("%s%x\n", "Starting the cycle... at PC: ", registers[PC_REG]);		
			
			printf("%s\n", "Fetching...");			
			instruction = fetch(memory, registers[PC_REG]);
			printf("%x fetched\n", instruction);

			printf("%s\n", "Decoding...");
			uint32_t decoded = decode(previous_instruction);
			printf("%x decoded\n", decoded);			

			printf("%s %x\n", "Executing...", prev_instruction);			
			execute(prev_instruction);
			
			prev_instruction = decoded;
			previous_instruction = instruction;

			registers[PC_REG] += 4;
			
			printf("%s\n\n", "Cycle ended.");
			
		} while (prev_instruction != 0);

		free(memory);

        return 0;
    
    } else {
    
        return -1;
    
    }

}
