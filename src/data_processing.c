#include "data_processing.h"

typedef struct __attribute__((__packed__)) {
    bit operand : 12;
    bit rd : 4;
    bit rn : 4;
    bit s : 1;
    bit opcode : 4;
    bit i : 1;
    bit unused : 2;
    bit cond : 4;
} processing_instr;

typedef void (*get_operation_code)(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg);

void and(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn & operand;
    *z = (res == 0);
    *n = (res >> 31);
    *reg = res;
}
void eor(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn ^ operand;
    *z = (res == 0);
    *n = (res >> 31);
    *reg = res;
}
void sub(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn - operand;
    *z = (res == 0);
    *c = (~res >> 31);  
    *n = (res >> 31);
    *reg = res;
}
void rsb(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = operand - rn;
    *z = (res == 0);
    *c = (res >> 31);
    *n = (res >> 31);
    *reg = res;
}
void add(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn + operand;
    *z = (res == 0);
    *c = (res >> 31);
    *n = (res >> 31);
    *reg = res;
}
void tst(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn & operand;
    *z = (res == 0);
    *n = (res >> 31);
}
void teq(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn ^ operand;
    *z = (res == 0);
    *n = (res >> 31);
}
void cmp(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn - operand;
    *z = (res == 0);
    *c = ((~res) >> 31);        
    *n = (res >> 31);
}
void orr(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = rn | operand;
    *z = (res == 0);
    *n = (res >> 31);
    *reg = res;
}
void mov(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    uint32_t res = operand;
    *z = (res == 0);
    *n = (res >> 31);
    *reg = res;
}
void not_defined(uint32_t rn, uint32_t operand, uint32_t *z, uint32_t *n, uint32_t *c, uint32_t * const reg) {
    *reg = 0;
}

const get_operation_code operation_table[16] = {
    and, eor, sub, rsb,                         // 0000 to 0011
    add, not_defined, not_defined, not_defined, // 0100 to 0111
    tst, teq, cmp, not_defined,                 // 1000 to 1011
    orr, mov, not_defined, not_defined          // 1100 to 1111
};

void exec_data_processing(uint32_t code, uint32_t * const regs) {
    log(("%s\n", "Execution of a DATA PROCESSING instruction starting."));

    processing_instr instr = *((processing_instr *) &code);

    if (!cond_check(instr.cond, *(regs + FLAG_REG))) {
        return;
    }   

    uint32_t rn = *(regs + instr.rn);
    uint32_t operand, z_flag, n_flag, c_flag;

    z_flag = n_flag = c_flag = 0;

    get_flags(regs + FLAG_REG, &z_flag, &n_flag, &c_flag);


    operand = compute_operand(instr.operand, instr.i, regs, &c_flag);       


    log(("%s%d\n", "Opcode: ", instr.opcode));

    operation_table[instr.opcode & 15](rn, operand, &z_flag, &n_flag, &c_flag, regs + instr.rd);

    if (instr.s) {
        set_flags(regs + FLAG_REG, z_flag, n_flag, c_flag);
    }

    log(("%s\n", "Execution of DP ending."));

}

uint32_t assemble_dp(char * const instruction) {

    log(("%s%s\n", "Assembling a DP instruction: ", instruction));

    processing_instr instr;

    memset(&instr, 0, sizeof(instr));

    instr.cond = 0xE;

    char *token = strtok(instruction, " ");

    if (!strcmp(token, "and") || !strcmp(token, "eor")
        || !strcmp(token, "sub") || !strcmp(token, "rsb")
        || !strcmp(token, "add") || !strcmp(token, "orr")) {
    } else if (!strcmp(token, "mov")) {
        char *destination_reg = strtok(NULL, ",");
        log(("destination_reg: %s\n", destination_reg));
        char *expression = strtok(NULL, "#");
        log(("expression: %s\n", expression));

        instr.i = 1;

        instr.opcode = 13;

        int immediate = atoi(expression);


    } else {

        instr.s = 1;

    }

    return *((uint32_t*)&instr);

}