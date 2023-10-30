#include"__memory.h"
#include"__instruction.h"

ins_raw_t fetch_ins(memory_t memory, memory_addr_t addr)
{
	memory_t tmp;

	tmp = &memory[addr];
	return *(ins_raw_t *)tmp;
}
