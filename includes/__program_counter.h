#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include"__memory.h"

// 32bit 命令長
typedef uint32_t program_t;

typedef struct {
	memory_addr_t ptr;
} program_counter_t;

program_counter_t program_counter_init(memory_addr_t pgm_start_addr);

#endif
