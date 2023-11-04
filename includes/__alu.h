#ifndef ALU_H
#define ALU_H

#include"__operation.h"
#include"__multiplexer.h"
#include"__register.h"

typedef uint32_t alu_out_t;

alu_out_t alu_perform(register_val_t register_val, multiplexer_in_out_t multiplexer_out, OPCODE opcode);

#endif
