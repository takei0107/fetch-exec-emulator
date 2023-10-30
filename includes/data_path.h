#ifndef DATA_PATH_H
#define DATA_PATH_H

#include"__program_counter.h"
#include"__memory.h"
#include"__adder.h"
#include"__register.h"
#include"__ins_decoder.h"

// 命令アドレス加算用のアダーの1回で進むアドレス
#define ADDER_STEP 4

typedef void (*on_decoded_func)(uint8_t opcode);

typedef struct {
	memory_t memory_pgm_ptr;
	size_t memory_pgm_size;
	memory_t memory_data_ptr;
	size_t memory_data_size;
	memory_addr_t pgm_start_addr;
	memory_addr_t pgm_end_addr;
	on_decoded_func on_decoded;
} data_path_init_params_t;

// データパス構造体
typedef struct {
	memory_t memory_pgm;
	memory_t memory_data;
	program_counter_t *pgm_ctr;
	adder_t *adder;
	register_unit_t *register_unit;
	on_decoded_func on_decoded;
} data_path_t;

data_path_t *init_data_path(data_path_init_params_t params);
int data_path_exec(data_path_t data_path);

#endif
