#include "multiply.h"

typedef struct {
	bit rm : 4;
	bit unused_1 : 4;
	bit rs : 4;
	bit rn : 4;
	bit rd : 4;
	bit s : 1;
	bit a : 1;
	bit unused_2 : 6;
	bit cond : 4;
} multiply_instr;

void exec_multiply(uint32_t code, memory_t *memory, uint32_t *regs) {
	
	printf("%s\n", "Execution of MULTIPLY done.");

	multiply_instr reg = *((multiply_instr *) &code);

	if (!cond_check(reg.cond, *(uint32_t *)(regs + FLAG_REG))) {
		return;
	}

	int accumulator = (reg.s & 1) ? reg.rn : 0;

	uint32_t rm = *(uint32_t *)(regs + reg.rm);
	uint32_t rs = *(uint32_t *)(regs + reg.rs);

	uint32_t rd = rm * rs + accumulator;

	*(uint32_t *)(regs + reg.rd) = rd;

	if (reg.s) {
		// set N, Z
		if (rd >> 31) {
			set_negative(regs + FLAG_REG);
		} else {
			clear_negative(regs + FLAG_REG);
		}

		if (rd == 0) {
			set_zero(regs + FLAG_REG);
		}

	}

}