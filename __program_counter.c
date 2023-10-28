#include"__program_counter.h"

#define STEP 4

program_counter_t program_counter_init(memory_addr_t pgm_start_addr)
{
	program_counter_t ctr;
	ctr.ptr = pgm_start_addr;
	return ctr;
}
