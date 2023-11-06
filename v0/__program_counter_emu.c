#include<stdint.h>

#define STEP 4

typedef uint32_t program_t;

// 命令ポインタ
static uint32_t ptr = 0x00000000;

void static adder()
{
	ptr = ptr + STEP;
}

program_t issue_next_program()
{
	int i;
	memory_address_t tmpAddr;
	uint8_t progAddrArr[4];
	program_t nextProg;

	// バイトリトルオーダー
	for(i = 0; i < STEP; i++) {
		tmpAddr = ptr + i;
		progAddrArr[i] = memory_fetch(PROG, tmpAddr);
	}

	adder();

	return *(program_t *)(progAddrArr);
}
