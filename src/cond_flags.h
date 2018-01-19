#ifndef __COND_FLAGS_H__
#define __COND_FLAGS_H__

#include "types.h"
#include <stdio.h>

void set_negative(uint32_t * const, uint32_t);

void set_zero(uint32_t * const, uint32_t);

boolean cond_check(uint32_t, uint32_t);

#endif