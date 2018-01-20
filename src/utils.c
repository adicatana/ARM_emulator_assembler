#include "utils.h"

uint32_t compute_operand(uint32_t instr_operand, boolean is_immediate, const uint32_t * const regs, uint32_t * const c_flag) {

	if (is_immediate) {
		uint32_t immediate = instr_operand & IMMEDIATE_MASK;
		uint32_t rotation = ((instr_operand >> 8) << 1);

		uint32_t SEAM_CARRY = 0;

		return rotate_right(immediate, rotation, &SEAM_CARRY);

	} else {
		uint32_t rm = instr_operand & RM_REG_MASK;
		uint32_t shift = instr_operand >> 4;

		uint32_t shift_type = (shift >> 1) & SHIFT_TYPE_MASK;

		uint32_t amount;

		if (shift & 1) {
			// shift specified by a register
			uint32_t rs = shift >> 4;
			amount = *(regs + rs);
		} else {
			// shift specified by a constant
			amount = (shift >> 3);
		}

		return shift_table[shift_type](*(regs + rm), amount, c_flag);
	}
}

uint32_t logical_left(uint32_t reg, uint32_t amount, uint32_t * const carry) {
	log(("%s%x%s%d\n", "Logical shift left, reg 0x", reg, " and amount ", amount));
	*carry = amount ? (((reg << (amount - 1)) >> 31) & 1) : 0;
	return reg << amount;
}

uint32_t logical_right(uint32_t reg, uint32_t amount, uint32_t * const carry) {
	log(("%s%x%s%d\n", "Logical shift right, reg 0x", reg, " and amount ", amount));	
	*carry = amount ? ((reg >> (amount - 1)) & 1) : 0;
	return reg >> amount;
}

uint32_t arithmetic_right(uint32_t reg, uint32_t amount, uint32_t * const carry) {
	log(("%s%x%s%d\n", "Arithmetic shift right, reg 0x", reg, " and amount ", amount));	
	uint32_t MSB = (reg & MSB_MASK);
	uint32_t CARRY_MASK = 0;
	for (int i = 0; i < amount; i++) {
		CARRY_MASK |= (MSB >> i);
	}
	return logical_right(reg, amount, carry) | CARRY_MASK;
}

uint32_t rotate_right(uint32_t immediate, uint32_t rotation, uint32_t * const carry) {
	log(("%s%x%s%d\n", "Rotate right, immediate 0x", immediate, " and rotation ", rotation));

	rotation %= WORD_LENGTH;

	uint64_t extended_immediate = (uint64_t) immediate << WORD_LENGTH | immediate;
	extended_immediate >>= rotation;

	*carry = rotation ? ((immediate >> (rotation - 1)) & 1) : 0;

	return (uint32_t)extended_immediate;

}

get_shifted_value shift_table[4] = {logical_left, logical_right, arithmetic_right, rotate_right};

uint32_t convert_endians(uint32_t word) {

	uint32_t converted_word = 0;

	converted_word += (0xFF000000 & word) >> 24;
	converted_word += (0x00FF0000 & word) >> 8;
	converted_word += (0x0000FF00 & word) << 8;
	converted_word += (0x000000FF & word) << 24;

	return converted_word;
}

void print_state(const memory_t * const mem, uint32_t * const regs) {

	printf("%s", "Registers:\n");

	for (uint32_t i = 0; i < NO_OF_GENERAL_REGISTERS; i++) {
		printf("$%-2d : %10d (0x%08x)\n", i, regs[i], regs[i]);
	} 

	printf("PC  : %10d (0x%08x)\n", regs[PC_REG], regs[PC_REG]);
	printf("CPSR: %10d (0x%08x)\n", regs[FLAG_REG], regs[FLAG_REG]);
	
	printf("%s", "Non-zero memory:\n");

	for (uint32_t i = 0; i < MEMORY_SIZE; i++) {
		uint32_t word = *(uint32_t *)&mem->addr[i];
		if (word) {
			printf("0x%08x: 0x%08x\n", 4 * i, convert_endians(word));
		}
	}
}

char *get_type(instruction_t e) {
	switch (e) {
		case 0: return "START";
		case 1: return "DATA_PROCESSING";
		case 2: return "MULTIPLY";
		case 3: return "DATA_TRANSFER";
		case 4: return "BRANCH";
		case 5: return "HALT";
		default: return "UNDEFINED";
	}
}
