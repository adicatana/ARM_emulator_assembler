#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdint.h>
#include "types.h"

#if 0
  #define log(a) printf a
#else
  #define log(a) (void)0
#endif

// Bit masks
#define MSB_MASK (1 << 31)
#define BRANCH_MASK (1 << 27)
#define DATA_TRANSFER_MASK (1 << 26)
#define MULTIPLY_MASK (9 << 4)
#define START_MASK START_INSTRUCTION

char *get_type(instruction_t);

// Bit operations
uint32_t logical_left(uint32_t, uint32_t);
uint32_t logical_right(uint32_t, uint32_t);
uint32_t arithmetic_right(uint32_t, uint32_t);
uint32_t rotate_right(uint32_t, uint32_t);

typedef uint32_t (*get_shifted_value)(uint32_t reg, uint32_t amount);

extern get_shifted_value shift_table[4];

uint32_t convert_endians(uint32_t);

void print_state(memory_t *, uint32_t *);


#endif