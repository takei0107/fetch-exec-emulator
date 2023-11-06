#include"__memory.h"

memory_data_out_t fetch_ins(memory_t memory, memory_addr_t addr)
{
	memory_t tmp;

	tmp = &memory[addr];
	return *(memory_data_out_t *)tmp;
}
