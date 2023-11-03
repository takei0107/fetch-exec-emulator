#ifndef INS_DECODER_H
#define INS_DECODER_H

#include<stdint.h>

#include"__register.h"
#include"__instruction.h"

#define INS_SIZE 32

#define OPCODE_SIZE   5
#define REG_A_SIZE    4
#define REG_B_SIZE    4
#define DST_REG_SIZE  4
#define OFFSET_SIZE   15

#define BIT_PATTERN_OPCODE  0xf8000000
#define BIT_PATTERN_REG_A   0x07800000
#define BIT_PATTERN_REG_B   0x00780000
#define BIT_PATTERN_DST_GEG 0x00078000
#define BIT_PATTERN_OFFSET  0x00007fff

#define SHIFT_OPCODE  (INS_SIZE - OPCODE_SIZE)
#define SHIFT_REG_A   (SHIFT_OPCODE - REG_A_SIZE)
#define SHIFT_REG_B   (SHIFT_REG_A - REG_B_SIZE)
#define SHIFT_DST_REG (SHIFT_REG_B - DST_REG_SIZE)
#define SHIFT_OFFSET  (SHIFT_DST_REG - OFFSET_SIZE)

typedef struct {
	uint8_t opcode          : OPCODE_SIZE;
	uint16_t offset         : OFFSET_SIZE;
	register_number_t regA  : REG_A_SIZE;
	register_number_t regB  : REG_B_SIZE;
	register_number_t dst   : DST_REG_SIZE;
} ins_decoded_t;

ins_decoded_t decode(ins_raw_t ins_raw);

#endif
