#ifndef __PIPELINE_CYCLE_H__
#define __PIPELINE_CYCLE_H__

#include <stdint.h>
#include "types.h"

uint32_t fetch(memory_t* mem, uint32_t PC);

uint32_t decode(uint32_t instruction);

void execute(uint32_t instruction);

#endif