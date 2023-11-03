#ifndef REGISTER_H
#define REGISTER_H

#include<stdint.h>

#define REGISTER_SIZE 16

// レジスタ番号は0~15まで
typedef uint8_t register_number_t;

// 32bitレジスタ
typedef uint32_t register_val_t;

typedef enum {
	SIG_DEFAULT,
	SIG_ADD,
	SIG_STORE,
	SIG_LOAD
} CTR_SIGNAL;

typedef struct {
	register_val_t val;
} register__t;

typedef struct {
	register__t gp_register[REGISTER_SIZE]; // 汎用レジスタ
	CTR_SIGNAL signal;
} register_unit_t;

register_unit_t *init_register_unit();

void register_unit_signal_received(register_unit_t *register_unit, const CTR_SIGNAL signal);

typedef uint32_t data_in_t;

typedef struct {
	data_in_t data_in;
	register_number_t regA;
	register_number_t regB;
	register_number_t dst;
} register_unit_in_t;

typedef struct {
	register_val_t srcRegAVal;
	register_val_t srcRegBVal;
} register_unit_out_t;

register_unit_out_t register_unit_perform(register_unit_t *register_unit, register_unit_in_t in);

#endif
