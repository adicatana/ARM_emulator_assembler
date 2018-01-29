#include "encode.h"

const char* dp_instr[NO_DP_INSTR] = {
	"and", "eor", "sub", "rsb", "add", "orr", "mov", "tst", "teq", "cmp"
};

const char* mult_instr[NO_MULT_INSTR] = {
	"mul", "mla"
};

const char* sdt_instr[NO_SDT_INSTR] = {
	"ldr", "str"
};

const char* b_instr[NO_B_INSTR] = {
	"beq", "bne", "bge", "blt", "bgt", "ble", "b"
};

uint32_t assemble(char * const instruction) {
	log(("%s\n", instruction));

	char instr_copy[BUFFER_SIZE_ASSEMBLER - 1];

	strncpy(instr_copy, instruction, BUFFER_SIZE_ASSEMBLER - 1);

	char *type = strtok(instruction, " ");
	log(("%s%s\n", "The command is ", type));

	for (int i = 0; i < NO_DP_INSTR; i++) {
		if (!strcmp(dp_instr[i], type)) {
			return assemble_dp(instr_copy);
		}
	}

	for (int i = 0; i < NO_MULT_INSTR; i++) {
		if (!strcmp(mult_instr[i], type)) {			
			return assemble_mult(instr_copy);
		}
	}

	for (int i = 0; i < NO_SDT_INSTR; i++) {
		if (!strcmp(sdt_instr[i], type)) {
			return assemble_sdt[i](instr_copy);
		}
	}

	for (int i = 0; i < NO_B_INSTR; i++) {
		if (!strcmp(b_instr[i], type)) {
			return assemble_branch(instr_copy);
		}
	}		

	return 0;

}