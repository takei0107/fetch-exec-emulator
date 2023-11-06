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
	uint32_t test_end = 0x00000044;
	test_param.pgm_start_addr = test_start;
	test_param.pgm_end_addr = test_end;
	test_param.pgm_size = 32;

	test_param.test_memory = init_memory(MEMORY_SIZE_ALL);
	test_param.test_memory[128].val = 4;
	test_param.test_memory[129].val = 7;
	test_param.test_memory[130].val = 56;
	test_param.test_memory[131].val = 33;

	// load
	ins = 0b00010000000000001000000000000000;
	test_param.test_memory[0].val = (ins & 0x000000ff);
	test_param.test_memory[1].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[2].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[3].val = (ins & 0xff000000) >> 24;
	// load
	ins = 0b00010000000000010000000000000001;
	test_param.test_memory[4].val = (ins & 0x000000ff);
	test_param.test_memory[5].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[6].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[7].val = (ins & 0xff000000) >> 24;
	// add
	ins = 0b00001000100100011000000000000000;
	test_param.test_memory[8].val = (ins & 0x000000ff);
	test_param.test_memory[9].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[10].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[11].val = (ins & 0xff000000) >> 24;
	// store
	ins = 0b00011000000110000000000000000100;
	test_param.test_memory[12].val = (ins & 0x000000ff);
	test_param.test_memory[13].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[14].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[15].val = (ins & 0xff000000) >> 24;
	// jump
	ins = 0b00100000000000000000000000110000;
	test_param.test_memory[16].val = (ins & 0x000000ff);
	test_param.test_memory[17].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[18].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[19].val = (ins & 0xff000000) >> 24;
	// add
	ins = 0b00001001101100111000000000000000;
	test_param.test_memory[20].val = (ins & 0x000000ff);
	test_param.test_memory[21].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[22].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[23].val = (ins & 0xff000000) >> 24;
	// store
	ins = 0b00011000001110000000000000000110;
	test_param.test_memory[24].val = (ins & 0x000000ff);
	test_param.test_memory[25].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[26].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[27].val = (ins & 0xff000000) >> 24;
	// jump
	ins = 0b00100000000000000000000001000100;
	test_param.test_memory[28].val = (ins & 0x000000ff);
	test_param.test_memory[29].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[30].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[31].val = (ins & 0xff000000) >> 24;
	// load
	ins = 0b00010000000000100000000000000010;
	test_param.test_memory[48].val = (ins & 0x000000ff);
	test_param.test_memory[49].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[50].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[51].val = (ins & 0xff000000) >> 24;
	// load
	ins = 0b00010000000000101000000000000011;
	test_param.test_memory[52].val = (ins & 0x000000ff);
	test_param.test_memory[53].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[54].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[55].val = (ins & 0xff000000) >> 24;
	// add
	ins = 0b00001010001010110000000000000000;
	test_param.test_memory[56].val = (ins & 0x000000ff);
	test_param.test_memory[57].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[58].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[59].val = (ins & 0xff000000) >> 24;
	// store
	ins = 0b00011000001100000000000000000101;
	test_param.test_memory[60].val = (ins & 0x000000ff);
	test_param.test_memory[61].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[62].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[63].val = (ins & 0xff000000) >> 24;
	// jump
	ins = 0b00100000000000000000000000010100;
	test_param.test_memory[64].val = (ins & 0x000000ff);
	test_param.test_memory[65].val = (ins & 0x0000ff00) >> 8;
	test_param.test_memory[66].val = (ins & 0x00ff0000) >> 16;
	test_param.test_memory[67].val = (ins & 0xff000000) >> 24;

	emulator_run(test_param, MEMORY_SIZE_ALL);
	assert(test_param.test_memory[132].val == 11);
	assert(test_param.test_memory[133].val == 89);
	assert(test_param.test_memory[134].val == 100);

	return 0;
}
