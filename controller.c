#include"controller.h"

#include<stdio.h>

controller_t *init_controller(data_path_t *data_path)
{
	controller_t *controller;
	controller = (controller_t *)malloc(sizeof(controller_t));
	controller->data_path = data_path;
	return controller;
}


void controller_opcode_received(controller_t *controller, uint8_t raw_opcode)
{
	switch((OPCODE)raw_opcode) {
		case ADD:
			register_unit_signal_received(controller->data_path->register_unit, SIG_ADD);
			multiplexer_signal_received(controller->data_path->m2, USE_DATA_ONE);
			multiplexer_signal_received(controller->data_path->m3, USE_DATA_TWO);
			memory_signal_received(MEM_SIG_NOOP);
			break;
		case STORE:
			register_unit_signal_received(controller->data_path->register_unit, SIG_STORE);
			multiplexer_signal_received(controller->data_path->m2, USE_DATA_TWO);
			memory_signal_received(MEM_SIG_WRITE);
			break;
		case LOAD:
			register_unit_signal_received(controller->data_path->register_unit, SIG_LOAD);
			multiplexer_signal_received(controller->data_path->m2, USE_DATA_TWO);
			multiplexer_signal_received(controller->data_path->m3, USE_DATA_ONE);
			memory_signal_received(MEM_SIG_READ);
			break;
	}
}

