#include "data_transfer.h"

#define RM_MASK 0xF
#define SHIFT_TYPE_MASK 3

typedef struct __attribute__((__packed__)) {
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

void exec_data_transfer(uint32_t code, const memory_t * const memory, uint32_t * const regs) {
	log(("%s\n", "Execution of a DATA TRANSFER instruction starting."));

	transfer_instr instr = *((transfer_instr *) &code);

	if (!cond_check(instr.cond, *(regs + FLAG_REG))) {
		return;
	}	

	uint32_t z_flag, n_flag, c_flag;

	get_flags(regs + FLAG_REG, &z_flag, &n_flag, &c_flag);	

	if (instr.i) {
		
		uint32_t operand = compute_operand(instr.offset, regs, &c_flag);

		uint32_t base_reg = *(regs + instr.rn);

		if (instr.u) {
			base_reg += operand;
		} else {
			base_reg -= operand;
		}

		if (!instr.p) {
			uint32_t aux = base_reg;
			base_reg = *(regs + instr.rn);
			*(regs + instr.rn) = aux;
		}

	} else {
		// offset is an unsigned 12 bit immediate offset
	}

	log(("%s\n", "Execution of DT ending."));

}