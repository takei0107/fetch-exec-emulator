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
	uint8_t val;
};
typedef struct _register__t register__t;

typedef void (*op_func)(decoded_t);


// 汎用レジスタ
static register__t generalRegisters[16] = {0};

decoded_t decode(uint32_t ins)
{
	decoded_t t;

	t.opcode = (0xf8000000 & ins) >> 27;
	t.regA   = (0x07800000 & ins) >> 23;
	t.regB   = (0x00780000 & ins) >> 19;
	t.dst    = (0x00078000 & ins) >> 15;
	t.offset = 0x00007fff & ins;

	return t;
}

void add_op(decoded_t decoded)
{
	register__t op1Reg, op2Reg, dstReg;

	op1Reg = generalRegisters[decoded.regA];
	op2Reg = generalRegisters[decoded.regB];

	dstReg = generalRegisters[decoded.dst];
	dstReg.val = op1Reg.val + op2Reg.val;
	//printf("%d %d %d\n", dstReg.val, op1Reg.val, op2Reg.val);

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
	uint8_t memory = memory_fetch((memory_address_t)(dstReg.val + offset));
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
	}
	return op;
}

int test()
{
	uint32_t ins;
	decoded_t decoded;
	op_func operator;

	memory_store(0, 2);
	memory_store(1, 3);

	// r1 <- 0(r0)
	ins = 0b00010000100000000000000000000000;
	decoded = decode(ins);
	operator = assign_op_func(decoded);
	operator(decoded);

	// r2 <- 1(r0)
	ins = 0b00010001000000000000000000000001;
	decoded = decode(ins);
	operator = assign_op_func(decoded);
	operator(decoded);

	// r3 <- r1 + r2
	ins = 0b00001000100100011000000000000000;
	decoded = decode(ins);
	operator = assign_op_func(decoded);
	operator(decoded);

	// 2(r0) <- r3
	ins = 0b00011000000110000000000000000010;
	decoded = decode(ins);
	operator = assign_op_func(decoded);
	operator(decoded);

//	printf("opcode: %#x\n", decoded.opcode);
//	printf("regA  : %#x\n", decoded.regA);
//	printf("regB  : %#x\n", decoded.regB);
//	printf("dst   : %#x\n", decoded.dst);
//	printf("offset: %#x\n", decoded.offset);
	assert(memory_fetch(2) == 5);
	return 0;
}

int main()
{
	return test();
}
