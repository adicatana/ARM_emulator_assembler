#include "data_transfer.h"

typedef struct {
	bit offset : 12;
	bit rd : 4;
	bit rn : 4;
	bit l : 1;
	bit unused_1 : 2;
	bit u : 1;
	bit p : 1;
	bit i : 1;
	bit unused_2 : 2;
	bit cond : 4;
} transfer_instr;

void exec_data_transfer(uint32_t code, memory_t *memory, uint32_t *regs) {
	printf("%s\n", "Execution of DT done.");

	transfer_instr instr = *((transfer_instr *) &code);

	if (!cond_check(instr.cond, *(uint32_t *)(regs + FLAG_REG))) {
		return;
	}	

	if (instr.i) {
		// offset is a shifted register
	} else {
		// offset is an unsigned 12 bit immediate value
	}

}