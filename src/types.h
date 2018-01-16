#ifndef __TYPES_H__
#define __TYPES_H__

#define MEMORY_SIZE 65536
#define NO_OF_REGISTERS 17
#define PC_REG 15
#define FLAG_REG 16

uint32_t registers[NO_OF_REGISTERS];

typedef struct {

    uint32_t addr[MEMORY_SIZE];

} memory_t;

#endif
