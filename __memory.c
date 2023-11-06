#include"__memory.h"

MEM_SIGNAL data_memory_signal = MEM_SIG_NOOP;

void memory_signal_received(MEM_SIGNAL signal)
{
	data_memory_signal = signal;
}

memory_data_out_t data_memory_perform(memory_t data_memory, memory_addr_t addr_in, memory_val_t data_in)
{
	switch(data_memory_signal) {
		case MEM_SIG_NOOP:
			return 0;
		case MEM_SIG_WRITE:
			data_memory[addr_in].val = data_in;
			return 0;
		case MEM_SIG_READ:
			return (memory_data_out_t)data_memory[addr_in].val;
	}
}
