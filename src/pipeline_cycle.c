#include "pipeline_cycle.h"

uint32_t fetch(memory_t* mem, uint32_t PC) {
	if (PC < 0) {
		return -1;
	}
	return *(uint32_t *)((char *)(mem->addr) + PC);
}

uint32_t decode(uint32_t instruction) {
	return instruction;
}

void execute(uint32_t instruction) {
	// nothing do to yet
}