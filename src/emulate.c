#include "input.h"
#include "types.h"

uint32_t fetch(memory_t* mem, uint32_t PC) {
	if (PC < 0) {
		return -1;
	}
	return mem->addr[PC];
}

uint32_t decode(uint32_t instruction) {
	return instruction;
}

void execute(uint32_t instruction) {
	// nothing do to yet
}

int main(int argc, char** argv) {

    if (argc > 1) {

		memory_t *memory = read_from_binary(argv[1]);

		memset(registers, 0, NO_OF_REGISTERS);

		if (memory == NULL) {
			perror("Erorr reading from binary\n");
			exit(EXIT_FAILURE);
		}

		int count = 0;
		
		uint32_t previous_instruction = -1;
		uint32_t prev_instruction = -1;
		    
		do {
			
			printf("%s\n", "Starting the cycle...");
			
			
			printf("%s\n", "Fetching...");			
			uint32_t instruction = fetch(memory, registers[PC_REG]);
			printf("%x fetched\n", instruction);

			printf("%s\n", "Decoding...");
			uint32_t decoded = decode(previous_instruction);
			printf("%x decoded\n", decoded);			

			printf("%s %x\n", "Executing...", prev_instruction);			
			execute(prev_instruction);
			
			prev_instruction = previous_instruction;
			previous_instruction = decoded;

			registers[PC_REG] += 4;
			
			printf("%s\n\n", "Cycle ended");
			
			count++;		
		} while (memory->addr[count]);

		free(memory);

        return 0;
    
    } else {
    
        return -1;
    
    }

}
