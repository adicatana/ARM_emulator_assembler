#include "branch.h"

typedef struct __attribute__((__packed__)) {
	int offset : 24;
	bit unused_1 : 4;
	bit cond : 4;
} branch_instr;

// code   - the branch instruction
// regs   - simulated registers for the ARM machine
void exec_branch(uint32_t code, uint32_t * const regs) {
	log(("%s\n", "Execution of a BRANCH instruction starting."));

	branch_instr instr = *((branch_instr *) &code);

	if (!cond_check(instr.cond, *(regs + FLAG_REG))) {
		return;
	}

	int offset = instr.offset << 2;

	log(("%s%d\n", "Offset for the PC is ", offset));

	offset += *(regs + PC_REG);

	// modify the PC accordingly to the branch instruction
	*(regs + PC_REG) = offset;

	log(("%s%d\n", "PC after branch will be ", *(regs + PC_REG)));

}

uint32_t assemble_branch(char * const instruction) {
	log(("%s%s\n", "Assembling a BRANCH instruction: ", instruction));
	return 0;
}