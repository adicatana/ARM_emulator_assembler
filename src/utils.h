#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdint.h>
#include "types.h"

// Bit operations
uint32_t rotate_right(uint32_t, uint32_t);
uint32_t convert_endians(uint32_t);

void print_state(memory_t *, uint32_t *);


#endif