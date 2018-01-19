#include "pipeline_cycle.h"

uint32_t fetch(memory_t* mem, uint32_t PC) {
	if (PC < 0) {
		return -1;
	}
	return *(uint32_t *)((char *)(mem->addr) + PC);
}

instruction decode(uint32_t instr) {

	instruction decoded;

	if (instr == 0) {
		decoded.type = HALT;
		decoded.code = 0;
	} else {

		uint32_t BRANCH_MASK = 1 << 27;
		uint32_t DATA_TRANSFER_MASK = 1 << 26;
		uint32_t MULTIPLY_MASK = 9 << 4;

		decoded.code = instr;

		if (instr & BRANCH_MASK) {
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

void execute(instruction instr, memory_t *memory, uint32_t *regs) {

	if (instr.type < 0 && instr.type > 3) {
		return;
	}

	switch (instr.type) {
		case DATA_PROCESSING: exec_data_processing(instr.code, memory, regs); return;
		case MULTIPLY: exec_multiply(instr.code, memory, regs); return;
		case DATA_TRANSFER: exec_data_transfer(instr.code, memory, regs); return;
		case BRANCH: exec_branch(instr.code, memory, regs); return;
		case HALT: return;
	}


}
