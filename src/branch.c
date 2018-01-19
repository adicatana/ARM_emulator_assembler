#include "branch.h"

typedef struct {
	bit offset : 24;
	bit unused_1 : 4;
	bit cond : 4;
} branch_instr;

void exec_branch(uint32_t code, memory_t *memory, uint32_t *regs) {
	// printf("%s\n", "Execution of BRANCH starting.");

	branch_instr instr = *((branch_instr *) &code);

	if (!cond_check(instr.cond, *(uint32_t *)(regs + FLAG_REG))) {
	// printf("Offset \n");
		return;
	}

	int offset = instr.offset << 2;

	// printf("Offset %d\n", offset);

	*(regs + PC_REG) = *(regs + PC_REG) + offset;
}