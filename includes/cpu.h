#ifndef CPU_H
#define CPU_H

#include"controller.h"
#include"data_path.h"

#include<stdint.h>

typedef struct {
	memory_addr_t pgm_start_addr;
	memory_addr_t pgm_end_addr;
} cpu_init_params;

typedef struct {
	data_path_t *data_path;
	controller_t *controller;
} cpu_t;

void init_cpu();

data_path_t cpu_get_data_path();

#endif
