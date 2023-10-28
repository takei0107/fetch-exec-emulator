#include"data_path.h"

int main()
{
	data_path_init_params params;
	data_path_t data_path;

	// 疑似開始位置と終了位置
	uint32_t test_start = 0x00000000;
	uint32_t test_end = 0x00000010;
	params.pgm_start_addr = test_start;
	params.pgm_end_addr = test_end;

	data_path = init_data_path(params);
	
	return data_path_exec(data_path);
}
