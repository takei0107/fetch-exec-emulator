#include"cpu.h"

static cpu_t cpu;

static void on_decoded(uint8_t opcode)
{
	controller_opcode_received(cpu.controller, opcode);
}

void init_cpu(cpu_init_params params)
{
	controller_t controller;
	data_path_init_params data_path_params;
	data_path_t data_path;

	// データパス初期化
	data_path_params.pgm_start_addr = params.pgm_start_addr;
	data_path_params.pgm_end_addr = params.pgm_end_addr;
	data_path_params.on_decoded = on_decoded;
	data_path = init_data_path(data_path_params);

	// コントローラー初期化
	controller = init_controller(data_path);
	
	// cpu初期化
	cpu.data_path = &data_path;
	cpu.controller = &controller;
}

data_path_t cpu_get_data_path()
{
	return *(cpu.data_path);
}


