#include"__adder.h"

adder_t *adder_init(const uint32_t step)
{
	adder_t *adder;
	adder = (adder_t *)malloc(sizeof(adder_t));
	adder->step = step;
	return adder;
}

memory_addr_t adder_perform(adder_t *adder, memory_addr_t ptr)
{
	return ptr + adder->step;
}
