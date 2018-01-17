#include "utils.h"

// uint32_t rotate_right(uint32_t immediate, uint32_t rotation) {
// 	rotation %= 32;

// 	uint64_t extended_immediate = immediate;
// 	extended_immediate <<= 32;
// 	extended_immediate |= immediate;

// 	extended_immediate >>= rotation;

// 	return (uint32_t)extended_immediate;

// }

uint32_t convert_endians(uint32_t word) {

	uint32_t converted_word = 0;

	converted_word += (0xFF000000 & word) >> 24;
	converted_word += (0x00FF0000 & word) >> 8;
	converted_word += (0x0000FF00 & word) << 8;
	converted_word += (0x000000FF & word) << 24;

	return converted_word;
}

void print_state(memory_t *mem, uint32_t *regs) {

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
			printf("0x%08x: 0x%08x\n", i, convert_endians(word));
		}
	}
}