#ifndef __BRANCH_H__
#define __BRANCH_H__

#include <stdio.h>
#include "types.h"
#include "cond_flags.h"
#include "utils.h"

#define NO_B_INSTR 7

void exec_branch(uint32_t, uint32_t * const);

uint32_t assemble_branch(char * const);

#endif