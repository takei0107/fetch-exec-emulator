#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<stdint.h>

#include"data_path.h"
#include"__operation.h"
#include"__register.h"
#include"__multiplexer.h"

typedef struct {
	data_path_t *data_path;
} controller_t;

controller_t *init_controller(data_path_t *data_path);

void controller_opcode_received(controller_t *controller, uint8_t raw_opcode);
#endif
