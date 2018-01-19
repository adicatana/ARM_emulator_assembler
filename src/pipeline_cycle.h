#ifndef __PIPELINE_CYCLE_H__
#define __PIPELINE_CYCLE_H__

#include <stdio.h>
#include "types.h"
#include "multiply.h"
#include "data_processing.h"
#include "data_transfer.h"
#include "branch.h"

void clear_cycle(uint32_t * const, uint32_t * const, instruction * const);

uint32_t fetch(const memory_t * const, uint32_t);
instruction decode(uint32_t);
void execute(instruction, const memory_t * const, uint32_t * const);

#endif