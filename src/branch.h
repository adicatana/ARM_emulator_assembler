#ifndef __BRANCH_H__
#define __BRANCH_H__

#include <stdio.h>
#include "types.h"
#include "cond_flags.h"
#include "utils.h"

void exec_branch(uint32_t, const memory_t * const, uint32_t * const);

#endif