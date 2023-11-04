#include<stdlib.h>
#include<assert.h>

#include"../emulator.c"

// 32bit汎用レジスタで表現できるサイズのMAX
#define MEMORY_SIZE_ALL (1L << 32)

int main()
{
	test_params_t test_param;
	data_path_t data_path;

	uint32_t ins;

	// 疑似開始位置と終了位置
	uint32_t test_start = 0x00000000;
	uint32_t test_end = 0x00000010;
	test_param.pgm_start_addr = test_start;
	test_param.pgm_end_addr = test_end;
	test_param.pgm_size = 4;

	test_param.test_memory = init_memory(MEMORY_SIZE_ALL);
	test_param.test_memory[16].val = 4;
	test_param.test_memory[17].val = 7;

	ins = 0b00010000000000001000000000000000;
	test_param.test_memory[0].val = (ins & 0x000000ff);
	test_param.test_memory[1].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[2].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[3].val = (ins & 0xff000000) >> 24;
	ins = 0b00010000000000010000000000000001;
	test_param.test_memory[4].val = (ins & 0x000000ff);
	test_param.test_memory[5].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[6].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[7].val = (ins & 0xff000000) >> 24;
	ins = 0b00001000100100011000000000000000;
	test_param.test_memory[8].val = (ins & 0x000000ff);
	test_param.test_memory[9].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[10].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[11].val = (ins & 0xff000000) >> 24;
	ins = 0b00011000000110000000000000000010;
	test_param.test_memory[12].val = (ins & 0x000000ff);
	test_param.test_memory[13].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[14].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[15].val = (ins & 0xff000000) >> 24;

	emulator_run(test_param, MEMORY_SIZE_ALL);
	assert(test_param.test_memory[18].val == 11);

}
