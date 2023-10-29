#ifndef DATA_PATH_H
#define DATA_PATH_H

#include"__program_counter.h"
#include"__memory.h"
#include"__adder.h"
#include"__register.h"
#include"__ins_decoder.h"

typedef struct {
	memory_area_t *pgm_area;
	memory_area_t *data_area;
} memory_all_t;

typedef void (*on_decoded_func)(uint8_t opcode);

typedef struct {
	memory_addr_t pgm_start_addr;
	memory_addr_t pgm_end_addr;
	on_decoded_func on_decoded;
} data_path_init_params;

// データパス構造体
typedef struct {
	program_counter_t pgm_ctr;
	memory_area_t *memory_data;
	memory_area_t *memory_pgm;
	adder_t adder;
	register_unit_t *register_unit;
	on_decoded_func on_decoded;
} data_path_t;

data_path_t init_data_path(data_path_init_params params);
int data_path_exec(data_path_t data_path);

#endif
