#ifndef DATA_PATH_H
#define DATA_PATH_H

#include"__program_counter.h"
#include"__memory.h"
#include"__adder.h"

// データパス構造体
typedef struct {
	program_counter_t pgm_ctr;
	memory_area_t *memory_data;
	memory_area_t *memory_pgm;
	adder_t adder;
} data_path_t;



#endif
