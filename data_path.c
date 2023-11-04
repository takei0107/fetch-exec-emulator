#include"data_path.h"

#include<stdlib.h>
#include<stdbool.h>

#ifndef NDEBUG
#include<assert.h>
#include<stdio.h>
#endif

data_path_t *init_data_path(data_path_init_params_t params)
{
	data_path_t *data_path;

	data_path = (data_path_t *)malloc(sizeof(data_path_t));

	data_path->memory_pgm = params.memory_pgm_ptr;
	data_path->memory_data = params.memory_data_ptr;
	
	// レジスタユニット初期化
	data_path->register_unit = init_register_unit();

	// プログラムカウンタ初期化
	data_path->pgm_ctr = program_counter_init(params.pgm_start_addr, params.pgm_end_addr);
	// adder初期化
	data_path->adder = adder_init(ADDER_STEP);

	// マルチプレクサ初期化
	data_path->m1 = init_multiplexer();
	data_path->m2 = init_multiplexer();
	data_path->m3 = init_multiplexer();

	data_path->on_decoded = params.on_decoded;

	return data_path;
}

int data_path_exec(data_path_t *data_path)
{
	memory_addr_t pgm_ctr_ptr, pgm_end_addr;
	memory_data_out_t ins_raw, memory_data_out;
	ins_decoded_t decoded;
	register_unit_in_t register_unit_in;
	register_unit_out_t register_unit_out;
	multiplexer_in_out_t multiplexer_out;
	alu_out_t alu_out;
	data_in_t data_in = 0;
	
	pgm_end_addr = data_path->pgm_ctr->pgm_end_addr;

	// クロック/ループ一回
	while((pgm_ctr_ptr = data_path->pgm_ctr->ptr) < pgm_end_addr) {
		data_path->pgm_ctr->ptr = adder_perform(data_path->adder, pgm_ctr_ptr);
		ins_raw = fetch_ins(data_path->memory_pgm, pgm_ctr_ptr);
		decoded = decode(ins_raw);
#ifndef NDEBUG
		// debug
		printf("\n");
		printf("##############################################\n");
		printf("ins:    0x%08x\n", ins_raw);
		printf("opcode: 0x%08x\n", decoded.opcode);
		printf("regA:   0x%08x\n", decoded.regA);
		printf("regB:   0x%08x\n", decoded.regB);
		printf("dst:    0x%08x\n", decoded.dst);
		printf("offset: 0x%08x\n", decoded.offset);
		printf("##############################################\n");
#endif
		data_path->on_decoded(decoded);

		register_unit_in.data_in = data_in;
		register_unit_in.regA = decoded.regA;
		register_unit_in.regB = decoded.regB;
		register_unit_in.dst = decoded.dst;

		register_unit_out = register_unit_perform(data_path->register_unit, register_unit_in);
		multiplexer_out = multiplexer_data_received(data_path->m2, register_unit_out.srcRegBVal, (multiplexer_in_out_t)decoded.offset);


		alu_out = alu_perform(register_unit_out.srcRegAVal, multiplexer_out, (OPCODE)decoded.opcode);

		memory_data_out = data_memory_perform(data_path->memory_data, alu_out, register_unit_out.srcRegBVal);
		if ((OPCODE)decoded.opcode == STORE) {
			continue;
		}

		multiplexer_out = multiplexer_data_received(data_path->m3, memory_data_out, alu_out);

		if ((OPCODE)decoded.opcode == ADD || (OPCODE)decoded.opcode == LOAD) {
			register_unit_signal_received(data_path->register_unit, SIG_SAVE);
			
			register_unit_in.data_in = multiplexer_out;
			register_unit_in.dst = decoded.dst;

			register_unit_perform(data_path->register_unit, register_unit_in);
		}

		
	}
	return 0;
}

