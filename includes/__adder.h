#ifndef ADDER_H
#define ADDER_H

#include<stdint.h>

#include"__memory.h"

typedef struct {
	uint32_t step;
} adder_t;

adder_t adder_init(const uint32_t step);

memory_addr_t adder_perform(adder_t adder, memory_addr_t ptr);

#endif
