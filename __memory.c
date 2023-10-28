#include"__memory.h"

memory_area_t *memory_area_init(uint32_t size)
{
	memory_area_t *area;
	area = (memory_area_t *)malloc(sizeof(memory_area_t));
	area->arr = (memory_t *)malloc(sizeof(memory_t) * size);
	return area;
}

memory_t memory_area_fetch(memory_area_t *memory, memory_addr_t addr)
{
	return memory->arr[addr];
}
