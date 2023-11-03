#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include<stdint.h>

#include"__operation.h"

typedef enum {
	USE_DATA_ONE,
	USE_DATA_TWO
} MUL_SIGNAL;

typedef struct {
	MUL_SIGNAL signal;
} multiplexer_t;

multiplexer_t *init_multiplexer();

typedef uint32_t multiplexer_in_out_t;

void multiplexer_signal_received(multiplexer_t *multiplexer, MUL_SIGNAL signal);

multiplexer_in_out_t multiplexer_data_received(multiplexer_t *multiplexer, multiplexer_in_out_t data_one, multiplexer_in_out_t data_two);

#endif
