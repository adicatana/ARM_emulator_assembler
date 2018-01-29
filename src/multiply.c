#include "multiply.h"

typedef struct __attribute__((__packed__)) {
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

void exec_multiply(uint32_t code, uint32_t * const regs) {
	
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

uint32_t assemble_mult(char * const instruction) {

    log(("%s%s\n", "Assembling a MULTIPLY instruction: ", instruction));

	multiply_instr instr;

	memset(&instr, 0, sizeof(instr));

	instr.cond = 14;
	instr.unused_1 = 9;

    char *type = strtok(instruction, " ");	

	char *rd = strtok(NULL, ", ");
	char *rm = strtok(NULL, ", ");
	char *rs = strtok(NULL, ", ");				

	instr.rd = atoi(++rd);
	instr.rm = atoi(++rm);
	instr.rs = atoi(++rs);		

	log(("rd : %d\n", instr.rd));
	log(("rm : %d\n", instr.rm));
	log(("rs : %d\n", instr.rs));


	if (!strcmp(type, "mul")) {

		instr.a = 0;

	} else if (!strcmp(type, "mla")) {

		instr.a = 1;

		char *rn = strtok(NULL, ", ");
		instr.rn = atoi(++rn);
		log(("rn : %d\n", instr.rn));		



	} 

	return *((uint32_t *)&instr);
}
