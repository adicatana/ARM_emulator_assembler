#ifndef __DATA_TRANSFER_H__
#define __DATA_TRANSFER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "cond_flags.h"
#include "utils.h"
#include "data_processing.h"

#define NO_SDT_INSTR 2

void exec_data_transfer(uint32_t, memory_t * const, uint32_t * const);

uint32_t assemble_sdt(char * const instruction);

#endif