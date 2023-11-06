#ifndef MEMORY_H
#define MEMORY_H

#include<stdlib.h>
#include<stdint.h>

typedef enum {
	MEM_SIG_NOOP,
	MEM_SIG_READ,
	MEM_SIG_WRITE
} MEM_SIGNAL;

typedef uint32_t memory_addr_t;
typedef uint8_t memory_val_t;

typedef struct {
	memory_val_t val;
} memory_cell_t;

typedef memory_cell_t *memory_t;

typedef uint32_t memory_data_out_t;

memory_data_out_t fetch_ins(memory_t memory, memory_addr_t addr);

void memory_signal_received(MEM_SIGNAL signal);

memory_data_out_t data_memory_perform(memory_t data_memory, memory_addr_t addr_in, memory_val_t data_in);

#endif
