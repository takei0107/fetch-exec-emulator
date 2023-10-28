#include<stdlib.h>

#include"data_path.h"

int main()
{
	data_path_init_params params;
	data_path_t data_path;

	uint32_t ins;
	/** 
	 * test
	 *
	 * 1. テスト用の命令開始位置と終了位置を設定
	 * 2. 命令メモリに命令データをストアする
	 *
	 **/
	// 疑似開始位置と終了位置
	uint32_t test_start = 0x00000000;
	uint32_t test_end = 0x00000010;
	params.pgm_start_addr = test_start;
	params.pgm_end_addr = test_end;

	data_path = init_data_path(params);
	ins = 0b00010000100000000000000000000000;
	data_path.memory_pgm->arr[0].val = (ins & 0x000000ff);
	data_path.memory_pgm->arr[1].val = (ins & 0x0000ff00) >> 8;
	data_path.memory_pgm->arr[2].val = (ins & 0x00ff0000) >> 16;
	data_path.memory_pgm->arr[3].val = (ins & 0xff000000) >> 24;
	ins = 0b00010001000000000000000000000001;
	data_path.memory_pgm->arr[4].val = (ins & 0x000000ff);
	data_path.memory_pgm->arr[5].val = (ins & 0x0000ff00) >> 8;
	data_path.memory_pgm->arr[6].val = (ins & 0x00ff0000) >> 16;
	data_path.memory_pgm->arr[7].val = (ins & 0xff000000) >> 24;
	ins = 0b00001000100100011000000000000000;
	data_path.memory_pgm->arr[8].val = (ins & 0x000000ff);
	data_path.memory_pgm->arr[9].val = (ins & 0x0000ff00) >> 8;
	data_path.memory_pgm->arr[10].val = (ins & 0x00ff0000) >> 16;
	data_path.memory_pgm->arr[11].val = (ins & 0xff000000) >> 24;
	ins = 0b00011000000110000000000000000010;
	data_path.memory_pgm->arr[12].val = (ins & 0x000000ff);
	data_path.memory_pgm->arr[13].val = (ins & 0x0000ff00) >> 8;
	data_path.memory_pgm->arr[14].val = (ins & 0x00ff0000) >> 16;
	data_path.memory_pgm->arr[15].val = (ins & 0xff000000) >> 24;
	return data_path_exec(data_path);
}
