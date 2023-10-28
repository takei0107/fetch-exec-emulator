#include"__memory.h"
#include"__instruction.h"

#include<stdlib.h>

ins_raw_t fetch_ins(memory_area_t *memory, memory_addr_t addr)
{
	int i;
	ins_raw_t ins;
	memory_t *mem;
	size_t ins_size;

	ins_size = sizeof(ins_raw_t);
	mem = (memory_t *)malloc(sizeof(memory_t) * ins_size);

	for(i = 0; i< ins_size; i++) {
		mem[i] = memory_area_fetch(memory, addr);
	}

	ins = *(ins_raw_t *)mem;

	free(mem);

	return ins;
}
