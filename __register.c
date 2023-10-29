#include"__register.h"

#include<string.h>

register_unit_t init_register_unit()
{
	register_unit_t unit;
	memset(unit.gp_register, 0, sizeof(unit.gp_register));
	unit.signal = SIG_DEFAULT;
	return unit;
}

void register_unit_signal_received(register_unit_t *register_unit, const CTR_SIGNAL signal)
{
	switch(signal) {
		case SIG_ADD:
			register_unit->signal = SIG_ADD;
			break;
	}
}
