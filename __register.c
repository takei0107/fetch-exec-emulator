#include"__register.h"

#include<string.h>

register_unit_t init_register_unit()
{
	register_unit_t unit;
	memset(unit.gp_register, 0, sizeof(unit.gp_register));
	return unit;
}
