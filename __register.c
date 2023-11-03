#include"__register.h"

#include<stdlib.h>
#include<string.h>

register_unit_t *init_register_unit()
{
	register_unit_t *unit = (register_unit_t *)malloc(sizeof(register_unit_t));
	memset(unit->gp_register, 0, sizeof(unit->gp_register));
	unit->signal = SIG_DEFAULT;
	return unit;
}

void register_unit_signal_received(register_unit_t *register_unit, const CTR_SIGNAL signal)
{
	register_unit->signal = signal;
}

register_unit_out_t register_unit_perform(register_unit_t *register_unit, register_unit_in_t in)
{
	register_unit_out_t out;
	switch(register_unit->signal) {
		case SIG_ADD:
			out.srcRegAVal = register_unit->gp_register[in.regA].val;
			out.srcRegBVal = register_unit->gp_register[in.regB].val;
			break;
		case SIG_STORE:
			out.srcRegAVal = register_unit->gp_register[in.regA].val;
			out.srcRegBVal = register_unit->gp_register[in.regB].val;
			break;
		case SIG_LOAD:
			out.srcRegAVal = register_unit->gp_register[in.regA].val;
			out.srcRegBVal = register_unit->gp_register[in.dst].val;
			break;
			
	}
	return out;
}
