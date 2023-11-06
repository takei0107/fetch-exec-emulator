#include<stdlib.h>

#include"__program_counter.h"

#define STEP 4

program_counter_t *program_counter_init(memory_addr_t pgm_start_addr, memory_addr_t pgm_end_addr)
{
	program_counter_t *ctr = (program_counter_t *)malloc(sizeof(program_counter_t));
	ctr->ptr = pgm_start_addr;
	ctr->pgm_start_addr = pgm_start_addr;
	ctr->pgm_end_addr = pgm_end_addr;
	return ctr;
}
