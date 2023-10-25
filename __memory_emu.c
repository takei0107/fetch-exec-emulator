#include<string.h>

#define MEMORYSIZE 1024*1024

static uint8_t memory[MEMORYSIZE] = {0};

typedef uint16_t memory_address_t;

uint8_t memory_fetch(memory_address_t addr)
{
	return memory[addr];
}

void memory_store(memory_address_t addr, uint8_t val)
{
	memory[addr] = val;
}
