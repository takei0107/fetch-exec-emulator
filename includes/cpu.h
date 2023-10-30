#ifndef CPU_H
#define CPU_H

#include"controller.h"
#include"data_path.h"

#include<stdint.h>

typedef struct {
	memory_t memory_ptr;
	size_t memory_size;
	memory_t memory_pgm_ptr;
	size_t memory_pgm_size;
	memory_t memory_data_ptr;
	size_t memory_data_size;
	memory_addr_t pgm_start_addr;
	memory_addr_t pgm_end_addr;
} cpu_init_params_t;

typedef struct {
	data_path_t *data_path;
	controller_t *controller;
} cpu_t;

void init_cpu();

data_path_t cpu_get_data_path();

#endif
