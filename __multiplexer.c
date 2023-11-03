#include"__multiplexer.h"

multiplexer_t *init_multiplexer()
{
	multiplexer_t *multiplexer;
	multiplexer = (multiplexer_t *)malloc(sizeof(multiplexer_t));
	multiplexer->signal = USE_DATA_ONE;
	return multiplexer;
}

void multiplexer_signal_received(multiplexer_t *multiplexer, MUL_SIGNAL signal)
{
	multiplexer->signal = signal;
}


multiplexer_in_out_t multiplexer_data_received(multiplexer_t *multiplexer, multiplexer_in_out_t data_one, multiplexer_in_out_t data_two)
{
	switch(multiplexer->signal) {
		case USE_DATA_ONE:
			return data_one;
		case USE_DATA_TWO:
			return data_two;
	}
}
