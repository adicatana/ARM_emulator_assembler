#include "pipeline_cycle.h"

#define ALL_ZEROS 0
#define NO_OF_INSTRUCTIONS 5

void clear_cycle(uint32_t * const current_instruction, uint32_t * const to_decode, instruction * const to_execute) {
		*current_instruction = START_INSTRUCTION;		
		*to_decode = START_INSTRUCTION;		
		
		to_execute->type = START;
		to_execute->code = START_INSTRUCTION;
}

uint32_t fetch(const memory_t * const mem, uint32_t PC) {
	return *(uint32_t *)((char *)(mem->addr) + PC);
}

instruction decode(uint32_t instr) {

	instruction decoded;

	if (instr == ALL_ZEROS) {
		decoded.type = HALT;
		decoded.code = ALL_ZEROS;
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
	log(("%s\n", "A START instruction (no effect on the pipeline) has been executed..."));
}

void execute(instruction instr, memory_t * const memory, uint32_t * const regs) {

	if (instr.type < 0 && instr.type >= NO_OF_INSTRUCTIONS) {
		return;
	}

	// TODO: remove memory where redundant i.e data processing multiply branch
	switch (instr.type) {
		case DATA_PROCESSING: exec_data_processing(instr.code, regs); return;
		case MULTIPLY: exec_multiply(instr.code, regs); return;
		case DATA_TRANSFER: exec_data_transfer(instr.code, memory, regs); return;
		case BRANCH: exec_branch(instr.code, regs); return;
		case START: exec_start(); return;
		case HALT: return;
	}


}
