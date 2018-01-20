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

#define IMMEDIATE_MASK 0xFF
#define RM_REG_MASK 0xF
#define SHIFT_TYPE_MASK 3

char *get_type(instruction_t);

uint32_t compute_operand(uint32_t, const uint32_t * const, uint32_t *);

// Bit operations
uint32_t logical_left(uint32_t, uint32_t, uint32_t * const);
uint32_t logical_right(uint32_t, uint32_t, uint32_t * const);
uint32_t arithmetic_right(uint32_t, uint32_t, uint32_t * const);
uint32_t rotate_right(uint32_t, uint32_t, uint32_t * const);

typedef uint32_t (*get_shifted_value)(uint32_t reg, uint32_t amoun, uint32_t * const carry);

extern get_shifted_value shift_table[4];

uint32_t convert_endians(uint32_t);

void print_state(const memory_t * const, uint32_t * const);


#endif