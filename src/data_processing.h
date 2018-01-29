#ifndef __DATA_PROCESSING_H__
#define __DATA_PROCESSING_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "cond_flags.h"
#include "utils.h"


#define NO_DP_INSTR 10

void exec_data_processing(uint32_t, uint32_t * const);
uint32_t assemble_dp(char * const);

#endif