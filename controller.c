#include"controller.h"

#include<stdio.h>

controller_t *init_controller(data_path_t *data_path)
{
	controller_t *controller;
	controller = (controller_t *)malloc(sizeof(controller_t));
	controller->register_unit = data_path->register_unit;
	controller->m1 = data_path->m1;
	controller->m2 = data_path->m2;
	controller->m3 = data_path->m3;
	return controller;
}


void controller_opcode_received(controller_t *controller, uint8_t raw_opcode)
{
	switch((OPCODE)raw_opcode) {
		case ADD:
			register_unit_signal_received(controller->register_unit, SIG_ADD);
			multiplexer_signal_received(controller->m2, USE_DATA_ONE);
			break;
		case STORE:
			register_unit_signal_received(controller->register_unit, SIG_STORE);
			multiplexer_signal_received(controller->m2, USE_DATA_TWO);
			break;
		case LOAD:
			register_unit_signal_received(controller->register_unit, SIG_LOAD);
			multiplexer_signal_received(controller->m2, USE_DATA_TWO);
			break;
	}
}

