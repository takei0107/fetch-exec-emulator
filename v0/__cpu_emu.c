/**
 * コンピュータアーキテクチャのエッセンス【第2版】の第6章に登場するCPUのエミュレータ実装
 *
 * - 32ビット固定
 *
 *   |opcode:5bit        |regA:4bit      |regA:4bit    |dst reg:4bit   |offset:15bit                                               |
 *   |___|___|___|___|___|___|___|___|___|___|___|__|__|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
 *
 *
 *
 * - 汎用32bitレジスタ16個(r0 ~ r15)
 * - 4つの命令(opcode)
 * -- add    00001
 * -- load   00010
 * -- store  00011
 * -- jump   00100
 *
 *
 *
 * 【サンプル】
 * 
 *   00001 0010 0011 0100 000000000000000
 *
 * > add 0010 0011 0100
 * > add reg2(0010) reg3(0011) reg4(0100)
 * > reg4 <- reg2 + reg3
 *
 **/

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#include<assert.h>

#include"__memory_emu.c"
#include"__program_counter_emu.c"

enum OPCODE {
	ADD   = 0b00001,
	LOAD  = 0b00010,
	STORE = 0b00011,
	JUMP  = 0b00100
};

// デコードされた命令の各フィールド
struct _decoded_t {
	uint8_t regA    :  4;
	uint8_t regB    :  4;
	uint8_t dst     :  4;
    uint8_t opcode  :  5;
	uint16_t offset : 15;
};
typedef struct _decoded_t decoded_t;

// レジスタ
struct _register__t {
	uint32_t val;
};
typedef struct _register__t register__t;

typedef void (*op_func)(decoded_t);


// 汎用レジスタ
static register__t generalRegisters[16] = {0};

decoded_t decode(program_t prog)
{
	decoded_t t;

	t.opcode = (0xf8000000 & prog) >> 27;
	t.regA   = (0x07800000 & prog) >> 23;
	t.regB   = (0x00780000 & prog) >> 19;
	t.dst    = (0x00078000 & prog) >> 15;
	t.offset = 0x00007fff & prog;

	return t;
}

void add_op(decoded_t decoded)
{
	register__t op1Reg, op2Reg, dstReg;

	op1Reg = generalRegisters[decoded.regA];
	op2Reg = generalRegisters[decoded.regB];

	dstReg = generalRegisters[decoded.dst];
	dstReg.val = op1Reg.val + op2Reg.val;
	printf("%d %d %d\n", dstReg.val, op1Reg.val, op2Reg.val);

	generalRegisters[decoded.dst] = dstReg;
}

void load_op(decoded_t decoded)
{
	register__t op1Reg, dstReg;
	uint16_t offset;

	op1Reg = generalRegisters[decoded.regA];
	dstReg = generalRegisters[decoded.dst];
	offset = decoded.offset;

	// dstRegの値 + offsetにあるメモリにアクセス
	uint8_t memory = memory_fetch(DATA, (memory_address_t)(dstReg.val + offset));
	// op1Regの値をメモリの値で更新
	op1Reg.val = memory;

	generalRegisters[decoded.regA] = op1Reg;
}

void store_op(decoded_t decoded)
{
	// offset(regA) <- regB
	register__t op1Reg, op2Reg;
	uint16_t offset;

	op1Reg = generalRegisters[decoded.regA];
	op2Reg = generalRegisters[decoded.regB];
	offset = decoded.offset;

	memory_store((memory_address_t)(op1Reg.val + offset), op2Reg.val);
}

void jump_op(decoded_t decoded)
{
	register__t op1Reg;
	uint16_t offset;
	uint32_t toPtr;

	op1Reg = generalRegisters[decoded.regA];
	offset = decoded.offset;

	toPtr = op1Reg.val + offset;

	ptr = toPtr;
}

op_func assign_op_func(decoded_t decoded)
{
	op_func op = NULL;
	switch(decoded.opcode) {
		case ADD:
			op = add_op;
			break;
		case LOAD:
			op = load_op;
			break;
		case STORE:
			op = store_op;
			break;
		case JUMP:
			op = jump_op;
			break;
	}
	return op;
}

int test()
{
	uint32_t ins;
	program_t prog;
	decoded_t decoded;
	op_func operator;

	memory_store(0, 2);
	memory_store(1, 3);

	// r1 <- 0(r0)
	// レジスタ1にレジスタ0の値+オフセット(0)のアドレスのメモリの値(addr = 0, val = 2)をロード
	ins = 0b00010000100000000000000000000000;
	program_memory[0] = (uint8_t)(ins & 0x000000ff);
	program_memory[1] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[2] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[3] = (uint8_t)((ins & 0xff000000) >> 24);
	// r2 <- 1(r0)
	// レジスタ2にレジスタ0の値+オフセット(1)のアドレスのメモリの値(addr = 1, val = 3)をロード
	ins = 0b00010001000000000000000000000001;
	program_memory[4] = (uint8_t)(ins & 0x000000ff);
	program_memory[5] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[6] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[7] = (uint8_t)((ins & 0xff000000) >> 24);
	// r3 <- r1 + r2 = 5
	// レジスタ1の値(2) + レジスタ2の値(3)をレジスタ3にストア
	ins = 0b00001000100100011000000000000000;
	program_memory[8] = (uint8_t)(ins & 0x000000ff);
	program_memory[9] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[10] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[11] = (uint8_t)((ins & 0xff000000) >> 24);
	// 2(r0) <- r3
	// レジスタ3の値(5)をレジスタ0の値+オフセット(2)のアドレスにストア
	ins = 0b00011000000110000000000000000010;
	program_memory[12] = (uint8_t)(ins & 0x000000ff);
	program_memory[13] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[14] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[15] = (uint8_t)((ins & 0xff000000) >> 24);

	// jump 27(r3)
	// レジスタ3の値(5)+オフセット(27)のアドレスの命令にジャンプ
	ins = 0b00100001100000000000000000011011;
	program_memory[16] = (uint8_t)(ins & 0x000000ff);
	program_memory[17] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[18] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[19] = (uint8_t)((ins & 0xff000000) >> 24);

	// r4 <- 0(r1)
	// レジスタ4にレジスタ1の値(2)+オフセット(0)のアドレスのメモリの値(addr = 2, val = 5)をロード
	ins = 0b00010010000000001000000000000000;
	program_memory[32] = (uint8_t)(ins & 0x000000ff);
	program_memory[33] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[34] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[35] = (uint8_t)((ins & 0xff000000) >> 24);

	// r5 <- r1 + r4
	// レジスタ1の値(2) + レジスタ4の値(5)をレジスタ5にストア
	ins = 0b00001000101000101000000000000000;
	program_memory[36] = (uint8_t)(ins & 0x000000ff);
	program_memory[37] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[38] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[39] = (uint8_t)((ins & 0xff000000) >> 24);

	// 2(r0) <- r5
	// レジスタ5の値(7)をレジスタ0の値+オフセット(3)のアドレスにストア
	ins = 0b00011000001010000000000000000011;
	program_memory[40] = (uint8_t)(ins & 0x000000ff);
	program_memory[41] = (uint8_t)((ins & 0x0000ff00) >> 8);
	program_memory[42] = (uint8_t)((ins & 0x00ff0000) >> 16);
	program_memory[43] = (uint8_t)((ins & 0xff000000) >> 24);

	prog = issue_next_program();
	decoded = decode(prog);
	operator = assign_op_func(decoded);
	operator(decoded);

	prog = issue_next_program();
	decoded = decode(prog);
	operator = assign_op_func(decoded);
	operator(decoded);

	prog = issue_next_program();
	decoded = decode(prog);
	operator = assign_op_func(decoded);
	operator(decoded);

	prog = issue_next_program();
	decoded = decode(prog);
	operator = assign_op_func(decoded);
	operator(decoded);

	prog = issue_next_program();
	decoded = decode(prog);
	operator = assign_op_func(decoded);
	operator(decoded);

	// jumped
	printf("%x\n", ptr);

	prog = issue_next_program();
	decoded = decode(prog);
	printf("opcode: %#x\n", decoded.opcode);
	printf("regA  : %#x\n", decoded.regA);
	printf("regB  : %#x\n", decoded.regB);
	printf("dst   : %#x\n", decoded.dst);
	printf("offset: %#x\n", decoded.offset);
	operator = assign_op_func(decoded);
	operator(decoded);

	prog = issue_next_program();
	decoded = decode(prog);
	printf("opcode: %#x\n", decoded.opcode);
	printf("regA  : %#x\n", decoded.regA);
	printf("regB  : %#x\n", decoded.regB);
	printf("dst   : %#x\n", decoded.dst);
	printf("offset: %#x\n", decoded.offset);
	operator = assign_op_func(decoded);
	operator(decoded);

	printf("reg5.val=%x\n", generalRegisters[5].val);

	prog = issue_next_program();
	decoded = decode(prog);
	printf("opcode: %#x\n", decoded.opcode);
	printf("regA  : %#x\n", decoded.regA);
	printf("regB  : %#x\n", decoded.regB);
	printf("dst   : %#x\n", decoded.dst);
	printf("offset: %#x\n", decoded.offset);
	operator = assign_op_func(decoded);
	operator(decoded);

//	printf("opcode: %#x\n", decoded.opcode);
//	printf("regA  : %#x\n", decoded.regA);
//	printf("regB  : %#x\n", decoded.regB);
//	printf("dst   : %#x\n", decoded.dst);
//	printf("offset: %#x\n", decoded.offset);

	printf("%d\n", memory_fetch(DATA, 3));
	assert(memory_fetch(DATA, 3) == 7);
	return 0;
}

int main()
{
	return test();
}
