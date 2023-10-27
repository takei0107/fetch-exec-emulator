#include<string.h>

#define PROGMEMORYSIZE 1L<<16
#define DATAMEMORYSIZE 1L<<16

typedef enum {
	PROG,
	DATA
} MEMORY_TYPE;

static uint8_t program_memory[PROGMEMORYSIZE] = {0};
static uint8_t data_memory[DATAMEMORYSIZE] = {0};

// 32bitアドレス
typedef uint32_t memory_address_t;

uint8_t memory_fetch(MEMORY_TYPE type, memory_address_t addr)
{
	uint8_t memory;
	switch(type) {
		case PROG:
			memory = program_memory[addr];
			break;
		case DATA:
			memory = data_memory[addr];
			break;
	}
	return memory;
}

void memory_store(memory_address_t addr, uint8_t val)
{
	data_memory[addr] = val;
}
