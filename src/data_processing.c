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

void compute_instruction(processing_instr * const instr, char *expression) {

    if (expression[0] == 'r') {
        instr->operand = atoi(++expression);
    } else {

        instr->i = 1;

        uint32_t immediate;

        if (strlen(expression) >= 2 && expression[1] == 'x') {
            sscanf(expression, "%x", &immediate);
        } else {
            immediate = atoi(expression);
        }

        log(("immediate value is %d\n", immediate));

        uint32_t operand = immediate;

        uint32_t count = 0;

        uint32_t SEAM_CARRY = 0;

        // NOT SURE YET
        while ((operand & 0xFF) != operand) {
            operand = revert_number(immediate);
            count++;
            operand = rotate_right(operand, 2 * count, &SEAM_CARRY);
            operand = revert_number(operand);
            SEAM_CARRY = 0;
        }

        log(("Operand %d\n", operand));
        log(("COUNT : %d\n", count));

        instr->operand = (count << 8) | operand;

    }
}

uint32_t assemble_dp(char * const instruction) {

    log(("%s%s\n", "Assembling a DP instruction: ", instruction));

    processing_instr instr;

    memset(&instr, 0, sizeof(instr));

    instr.cond = 0xE;

    char *type = strtok(instruction, " ");

    char *destination_reg = strtok(NULL, ",");
    log(("destination_reg: %s\n", destination_reg));

    destination_reg++;
    instr.rd = atoi(destination_reg);
    log(("destination reg number: %d\n", instr.rd));


    if (!strcmp(type, "and") || !strcmp(type, "eor")
        || !strcmp(type, "sub") || !strcmp(type, "rsb")
        || !strcmp(type, "add") || !strcmp(type, "orr")) {


        if (!strcmp(type, "and")) {
            instr.opcode = 0;
        } else if (!strcmp(type, "eor")) {
            instr.opcode = 1;
        } else if (!strcmp(type, "sub")) {
            instr.opcode = 2;
        } else if (!strcmp(type, "rsb")) {
            instr.opcode = 3;
        } else if (!strcmp(type, "add")) {
            instr.opcode = 4;
        } else {
            instr.opcode = 12;
        }

        char *rn = strtok(NULL, ", ");

        instr.rn = atoi(++rn);

        char *expression = strtok(NULL, " #");
        log(("expression: %s\n", expression));

        compute_instruction(&instr, expression);

    } else {

        char *expression = strtok(NULL, " ,#");
        log(("expression: %s\n", expression));

        compute_instruction(&instr, expression);

        if (!strcmp(type, "mov")) {
            instr.opcode = 13;        
            
        } else {

            // these instructions do not modify rd, but rn
            int aux = instr.rn; 
            instr.rn = instr.rd;
            instr.rd = aux;

            if (!strcmp(type, "tst")) {
                instr.opcode = 8;
            } else if (!strcmp(type, "teq")) {
                instr.opcode = 9;
            } else if (!strcmp(type, "cmp")) {
                instr.opcode = 10;
            }

            instr.s = 1;
        }


    }

    return *((uint32_t*)&instr);

}

