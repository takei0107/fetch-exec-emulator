#include"cpu.h"

#include<stdlib.h>
#include<string.h>

// 32bit汎用レジスタで表現できるサイズのMAX
#define MEMORY_SIZE_ALL (1L << 32)

#ifndef NDEBUG

#include<stdio.h>

typedef struct {
	memory_t test_memory;
	size_t pgm_size;
	memory_addr_t pgm_start_addr;
	memory_addr_t pgm_end_addr;
} test_params_t;
#endif

static memory_t init_memory(const size_t size)
{
	memory_t memory;
	memory= (memory_t)malloc(sizeof(size));
	return memory;
}

int emulator_run(
#ifndef NDEBUG
test_params_t test_params,
#endif
size_t init_memory_size
)
{
	cpu_init_params_t cpu_init_params;
	memory_t memory, memory_pgm_start_ptr;
	size_t memory_pgm_size;
	memory_addr_t pgm_start_addr, pgm_end_addr;

	// メモリ初期化
#ifndef NDEBUG
	memory = test_params.test_memory;
#else
	memory = init_memory(init_memory_size);
#endif

	cpu_init_params.memory_ptr = memory;
	cpu_init_params.memory_size = init_memory_size;

#ifndef NDEBUG
	memory_pgm_start_ptr = memory;
	memory_pgm_size = test_params.pgm_size;
	pgm_start_addr = test_params.pgm_start_addr;
	pgm_end_addr = test_params.pgm_end_addr;
#else
	// デバッグでないならファイルとかから命令をロードする。
#endif
	cpu_init_params.memory_pgm_ptr = memory_pgm_start_ptr;
	cpu_init_params.memory_pgm_size = memory_pgm_size;

	// 命令メモリ以降をデータメモリとして利用する。
	cpu_init_params.memory_data_ptr = memory_pgm_start_ptr + (memory_pgm_size*4);
	cpu_init_params.memory_data_size = init_memory_size - memory_pgm_size;

	cpu_init_params.pgm_start_addr = pgm_start_addr;
	cpu_init_params.pgm_end_addr = pgm_end_addr;

	// CPU初期化
	init_cpu(cpu_init_params);
	data_path_exec(cpu_get_data_path());
}
