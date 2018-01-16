#include "data_processing.h"

typedef struct {
	bit operand_2 : 12;
	bit rd : 4;
	bit rn : 4;
	bit s : 1;
	bit opcode : 4;
	bit i : 1;
	bit unused : 2;
	bit cond : 4;
} processing_instr;

void exec_data_processing(uint32_t code, memory_t *memory, uint32_t *regs) {
	printf("%s\n", "Execution of DP done.");

	processing_instr instr = *((processing_instr *) &code);

	if (!cond_check(instr.cond, *(uint32_t *)(regs + FLAG_REG))) {
		return;
	}	

	uint32_t rn = *(uint32_t *)(regs + instr.rn);

	if (instr.i) {
		uint32_t immediate = (uint32_t)(instr.operand_2 & 0xFF);
		
	} else {

	}

}
