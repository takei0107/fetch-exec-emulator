#include"cpu.h"

static cpu_t cpu;

static void on_decoded(ins_decoded_t decoded)
{
	controller_opcode_received(cpu.controller, decoded.opcode);
}

void init_cpu(cpu_init_params_t params)
{
	controller_t *controller;
	data_path_init_params_t data_path_params;
	data_path_t *data_path;

	// データパス初期化
	data_path_params.memory_pgm_ptr = params.memory_pgm_ptr;
	data_path_params.memory_data_ptr = params.memory_data_ptr;

	data_path_params.pgm_start_addr = params.pgm_start_addr;
	data_path_params.pgm_end_addr = params.pgm_end_addr;
	data_path_params.on_decoded = on_decoded;
	data_path = init_data_path(data_path_params);

	// コントローラー初期化
	controller = init_controller(data_path);
	
	// cpu初期化
	cpu.data_path = data_path;
	cpu.controller = controller;
}

data_path_t *cpu_get_data_path()
{
	return cpu.data_path;
}


