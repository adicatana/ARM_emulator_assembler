#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "cond_flags.h"
#include "utils.h"

#define NO_MULT_INSTR 2

void exec_multiply(uint32_t, uint32_t * const);

uint32_t assemble_mult(char * const);

#endif