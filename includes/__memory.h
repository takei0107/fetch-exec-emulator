#ifndef MEMORY_H
#define MEMORY_H

#include<stdlib.h>
#include<stdint.h>

#include"__instruction.h"

typedef uint32_t memory_addr_t;
typedef uint8_t memory_val_t;

typedef struct {
	memory_val_t val;
} memory_cell_t;

typedef memory_cell_t *memory_t;


ins_raw_t fetch_ins(memory_t memory, memory_addr_t addr);
#endif
