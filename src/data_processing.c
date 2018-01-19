#include "data_processing.h"

typedef struct {
	bit operand : 12;
	bit rd : 4;
	bit rn : 4;
	bit s : 1;
	bit opcode : 4;
	bit i : 1;
	bit unused : 2;
	bit cond : 4;
} processing_instr;

typedef uint32_t (*get_operation_code)(uint32_t rn, uint32_t operand);

uint32_t and(uint32_t rn, uint32_t operand) {
	// printf("AND\n");
	return rn & operand;
}

uint32_t eor(uint32_t rn, uint32_t operand) {
	return rn ^ operand;
}

uint32_t sub(uint32_t rn, uint32_t operand) {
	return rn - operand;
}

uint32_t rsb(uint32_t rn, uint32_t operand) {
	return operand - rn;
}

uint32_t add(uint32_t rn, uint32_t operand) {
	return rn + operand;
}

uint32_t tst(uint32_t rn, uint32_t operand) {
	return 1;
}

uint32_t teq(uint32_t rn, uint32_t operand) {
	return 1;
}

uint32_t cmp(uint32_t rn, uint32_t operand) {
	return 1;
}

uint32_t orr(uint32_t rn, uint32_t operand) {
	return rn | operand;
}

uint32_t mov(uint32_t rn, uint32_t operand) {
	// printf("MOV %d\n", operand);	
	return operand;
}

uint32_t not_defined(uint32_t rn, uint32_t operand) {
	return 0;
}

get_operation_code operation_table[16] = {
	and, eor, sub, rsb, 	// 0000 to 0011
	add, not_defined, not_defined, not_defined, // 0100 to 0111
	tst, teq, cmp, not_defined, 
	orr, mov, not_defined, not_defined  // 1100 to 1111
};

void exec_data_processing(uint32_t code, memory_t *memory, uint32_t *regs) {
	// printf("%s\n", "Execution of DP starting.");

	processing_instr instr = *((processing_instr *) &code);

	if (!cond_check(instr.cond, *(uint32_t *)(regs + FLAG_REG))) {
		return;
	}	

	uint32_t rn = *(uint32_t *)(regs + instr.rn);
	uint32_t operand;

	if (instr.i) {
		uint32_t immediate = instr.operand & 0xFF;
		uint32_t rotation = ((instr.operand >> 8) << 1);

		operand = rotate_right(immediate, rotation);

	} else {
		uint32_t rm = instr.operand & 0xF;
		uint32_t shift = instr.operand >> 4;

		uint32_t shift_type = (shift >> 1) & 3;

		uint32_t amount;

		if (shift & 1) {
			// shift specified by a register
			uint32_t rs = shift >> 4;
			amount = *(regs + rs);
		} else {
			// shift specified by a constant
			amount = (shift >> 3) & 0xF;
		}

		operand = shift_table[shift_type](*(regs + rm), amount);

	}

	// printf("Opcode : %d\n", instr.opcode);

	*(regs + instr.rd) = operation_table[instr.opcode & 15](rn, operand);


	if (instr.s) {

	}

	// printf("Execution of DP ending\n");

}
