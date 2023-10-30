#include"controller.h"

controller_t *init_controller(data_path_t *data_path)
{
	controller_t *controller;
	controller = (controller_t *)malloc(sizeof(controller_t));
	controller->register_unit = data_path->register_unit;
	return controller;
}

void controller_opcode_received(controller_t *controller, OPCODE opcode)
{
	switch(opcode) {
		case ADD:
			register_unit_signal_received(controller->register_unit, SIG_ADD);
			break;
	}
}

