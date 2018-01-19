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

void exec_multiply(uint32_t code, const memory_t * const memory, uint32_t * const regs) {
	
	log(("%s\n", "Execution of a MULTIPLY instruction is starting."));

	multiply_instr instr = *((multiply_instr *) &code);

	if (!cond_check(instr.cond, *(regs + FLAG_REG))) {
		return;
	}

	int accumulator = (instr.a & 1) ? *(regs + instr.rn) : 0;

	uint32_t rm = *(regs + instr.rm);
	uint32_t rs = *(regs + instr.rs);

	uint32_t rd = rm * rs + accumulator;

	*(regs + instr.rd) = rd;

	if (instr.s) {
		// set N, Z

		set_negative(regs + FLAG_REG, (rd & MSB_MASK) != 0);

		if (rd == 0) {
			set_zero(regs + FLAG_REG, 1);
		}

	}

	log(("%s\n", "Execution of a MULTIPLY instruction is ending."));

}