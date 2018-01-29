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

void exec_data_transfer(uint32_t code, memory_t * const memory, uint32_t * const regs) {
	log(("%s\n", "Execution of a DATA TRANSFER instruction starting."));

	transfer_instr instr = *((transfer_instr *) &code);

	if (!cond_check(instr.cond, *(regs + FLAG_REG))) {
		return;
	}	

	// data transfer will not modify carry flags
	uint32_t SEAM_C_FLAG = 0;

	uint32_t offset = compute_operand(instr.offset, !instr.i, regs, &SEAM_C_FLAG);

	uint32_t base_reg = *(regs + instr.rn);

	if (instr.u) {
		base_reg += offset;
	} else {
		base_reg -= offset;
	}

	if (!instr.p) {
		uint32_t aux = base_reg;
		base_reg = *(regs + instr.rn);
		*(regs + instr.rn) = aux;
	}

	if (base_reg > MEMORY_SIZE) {

		printf("Error: Out of bounds memory access at address 0x%08x\n", base_reg);
		return;

	}

	if (instr.l) {
		regs[instr.rd] = *(uint32_t *)((char *)(memory->addr) + base_reg);
	} else {
		*(uint32_t *)((char *)(memory->addr) + base_reg) = regs[instr.rd];
	}


	log(("%s\n", "Execution of DT ending."));

}

uint32_t assemble_sdt(char * const instruction) {

    log(("%s%s\n", "Assembling a SGT instruction: ", instruction));

    transfer_instr instr;

    memset(&instr, 0, sizeof(instr));

    instr.cond = 0xE;
    instr.unused_2 = 1;

    char instr_copy[BUFFER_SIZE_ASSEMBLER];

    strncpy(instr_copy, instruction, BUFFER_SIZE_ASSEMBLER);

    char *type = strtok(instruction, " ");

    char *destination_reg = strtok(NULL, ",");
    log(("destination_reg: %s\n", destination_reg));

    destination_reg++;
    instr.rd = atoi(destination_reg);
    log(("destination reg number: %d\n", instr.rd));

    if (!strcmp(type, "ldr")) {
    	instr.l = 1;

        char *expression = strtok(NULL, " ,#");
        log(("expression: %s\n", expression)); 	

        if (expression[0] == '=') {
        	instr.p = 1;
        	expression++;
	        log(("expression: %s\n", expression));

	        uint32_t immediate;

	        sscanf(expression, "%x", &immediate);

	        if (immediate <= 0xFF) {
	        	instr_copy[0] = 'm';
	        	instr_copy[1] = 'o';
	        	instr_copy[2] = 'v';
	        	return assemble_dp(instr_copy);
	        } else {

	        }

        }

    } else {

    }

	return *((uint32_t *)&instr);
}
