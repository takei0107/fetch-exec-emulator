#ifndef MEMORY_H
#define MEMORY_H

#include<stdlib.h>
#include<stdint.h>

typedef uint32_t memory_addr_t;
typedef uint8_t memory_val_t;

typedef struct {
	memory_val_t val;
} memory_t;

typedef struct {
	memory_t *arr;
} memory_area_t;

typedef struct {
	memory_area_t *pgm_area;
	memory_area_t *data_area;
} memory_all_t;

memory_area_t *memory_area_init(uint32_t size);

memory_t memory_area_fetch(memory_area_t *memory, memory_addr_t addr);

#endif
