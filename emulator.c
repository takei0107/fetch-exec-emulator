#include"data_path.h"

int main()
{
	data_path_init_params params;
	data_path_t data_path;

	data_path = init_data_path(params);
	
	return data_path_exec(data_path);
}
