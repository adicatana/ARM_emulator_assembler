#include "input.h"
#include "types.h"
#include "pipeline_cycle.h"

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

uint32_t convert_endians(uint32_t word) {

	uint32_t converted_word = 0;

	converted_word += (0xFF000000 & word) >> 24;
	converted_word += (0x00FF0000 & word) >> 8;
	converted_word += (0x0000FF00 & word) << 8;
	converted_word += (0x000000FF & word) << 24;

	return converted_word;
}

void print_state(memory_t *mem, uint32_t *regs) {

	printf("%s", "Registers:\n");

	for (uint32_t i = 0; i < NO_OF_GENERAL_REGISTERS; i++) {
		printf("$%-2d : %10d (0x%08x)\n", i, regs[i], regs[i]);
	} 

	printf("PC  : %10d (0x%08x)\n", regs[PC_REG], regs[PC_REG]);
	printf("CPSR: %10d (0x%08x)\n", regs[FLAG_REG], regs[FLAG_REG]);
	
	printf("%s", "Non-zero memory:\n");

	for (uint32_t i = 0; i < MEMORY_SIZE; i++) {
		uint32_t word = *(uint32_t *)&mem->addr[i];
		if (word) {
			printf("0x%08x: 0x%08x\n", i, convert_endians(word));
		}
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
