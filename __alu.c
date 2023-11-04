#include"__alu.h"

alu_out_t alu_perform(register_val_t register_val, multiplexer_in_out_t multiplexer_out, OPCODE opcode)
{
	switch(opcode) {
		case ADD:
		case STORE:
		case LOAD:
		case JUMP:
		return register_val + multiplexer_out;
	}
}
