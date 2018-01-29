#ifndef __DATA_TRANSFER_H__
#define __DATA_TRANSFER_H__

#include <stdio.h>
#include "types.h"
#include "cond_flags.h"
#include "utils.h"

#define NO_SDT_INSTR 2

void exec_data_transfer(uint32_t, memory_t * const, uint32_t * const);

typedef uint32_t (*sdt_table)(char * const instruction);

sdt_table assemble_sdt[NO_SDT_INSTR];

#endif