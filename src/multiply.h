#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

#include <stdio.h>
#include "types.h"
#include "cond_flags.h"
#include "utils.h"

#define NO_MULT_INSTR 2

void exec_multiply(uint32_t, uint32_t * const);

typedef uint32_t (*mult_table)(char * const instruction);

mult_table assemble_mult[NO_MULT_INSTR];

#endif