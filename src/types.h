#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

#define MEMORY_SIZE 65536
#define WORD_LENGTH 32

// Registers related constants
#define NO_OF_GENERAL_REGISTERS 13
#define NO_OF_REGISTERS 17
#define PC_REG 15
#define FLAG_REG 16
#define INIT_REG_VALUE 0

#define START_INSTRUCTION 0x0f000000

typedef uint32_t boolean;
typedef unsigned int bit;

typedef enum {
	START,
	DATA_PROCESSING,
	MULTIPLY,
	DATA_TRANSFER,
	BRANCH,
	HALT
} instruction_t;


typedef struct {
	instruction_t type;
	uint32_t code;
} instruction;

// The state of the ARM machine
uint32_t registers[NO_OF_REGISTERS];

typedef struct {
    uint32_t addr[MEMORY_SIZE];
} memory_t;

#endif
