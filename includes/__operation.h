#ifndef OPERATION_H
#define OPERATION_H

typedef enum {
	ADD   = 0b00000001,
	LOAD  = 0b00000010,
	STORE = 0b00000011,
	JUMP  = 0b00000100
} OPCODE;

#endif
