#include"__ins_decoder.h"

ins_decoded_t decode(memory_data_out_t ins_raw)
{
	ins_decoded_t decoded;

	// opcode
	decoded.opcode = (BIT_PATTERN_OPCODE & ins_raw) >> SHIFT_OPCODE;
	// regA
	decoded.regA = (BIT_PATTERN_REG_A & ins_raw) >> SHIFT_REG_A;
	// regB
	decoded.regB = (BIT_PATTERN_REG_B & ins_raw) >> SHIFT_REG_B;
	// dst reg
	decoded.dst = (BIT_PATTERN_DST_GEG & ins_raw) >> SHIFT_DST_REG;
	// offset
	decoded.offset = (BIT_PATTERN_OFFSET & ins_raw) >> SHIFT_OFFSET;

	return decoded;
}
