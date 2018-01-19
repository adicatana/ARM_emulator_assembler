#include "pipeline_cycle.h"

void clear_cycle(uint32_t *current_instruction, uint32_t *to_decode, instruction *to_execute) {
		*current_instruction = START_INSTRUCTION;		
		*to_decode = START_INSTRUCTION;		
		
		to_execute->type = START;
		to_execute->code = START_INSTRUCTION;
}

uint32_t fetch(memory_t* mem, uint32_t PC) {
	return *(uint32_t *)((char *)(mem->addr) + PC);
}

instruction decode(uint32_t instr) {

	instruction decoded;

	if (instr == 0) {
		decoded.type = HALT;
		decoded.code = 0;
	} else {

		decoded.code = instr;

		if ((instr & START_MASK) == START_MASK) {
			decoded.type = START;
		} else if (instr & BRANCH_MASK) {
			decoded.type = BRANCH;
		} else if (instr & DATA_TRANSFER_MASK) {
			decoded.type = DATA_TRANSFER;
		} else if ((instr & MULTIPLY_MASK) == MULTIPLY_MASK && (((instr >> 22) & 0x3F) == 0)) {
			decoded.type = MULTIPLY;
		} else {
			decoded.type = DATA_PROCESSING;
		}

	}

	return decoded;
}

void exec_start() {
	// printf ("%s\n", "Starting the cycle...");
}

void execute(instruction instr, memory_t *memory, uint32_t *regs) {

	if (instr.type < 0 && instr.type > 4) {
		return;
	}

	switch (instr.type) {
		case DATA_PROCESSING: exec_data_processing(instr.code, memory, regs); return;
		case MULTIPLY: exec_multiply(instr.code, memory, regs); return;
		case DATA_TRANSFER: exec_data_transfer(instr.code, memory, regs); return;
		case BRANCH: exec_branch(instr.code, memory, regs); return;
		case START: exec_start(); return;
		case HALT: return;
	}


}
