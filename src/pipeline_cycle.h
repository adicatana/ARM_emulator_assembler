#ifndef __PIPELINE_CYCLE_H__
#define __PIPELINE_CYCLE_H__

#include <stdio.h>
#include "types.h"
#include "multiply.h"
#include "data_processing.h"
#include "data_transfer.h"
#include "branch.h"

uint32_t fetch(memory_t*, uint32_t);

instruction decode(uint32_t);

void execute(instruction, memory_t *, uint32_t *);

#endif