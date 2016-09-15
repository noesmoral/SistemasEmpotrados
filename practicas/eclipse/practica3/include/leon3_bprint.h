/*
 * leon3_bprint.h
 *
 *  Created on: Feb 12, 2016
 *      Author: pedro
 */

#ifndef LEON3_BPRINT_H_
#define LEON3_BPRINT_H_

#include "leon3_types.h"

//transmite a través del puerto serie la cadena de caracteres
//pasada por parámetro.
int8_t leon3_print_string(char* str);

//transmite a través del puerto serie el entero transformado en
//cadena de caracteres.
int8_t leon3_print_uint8(uint8_t i);

//Esta función implementa una función análoga a la función
//leon3_print_uint8 que se realizó en la práctica anterior, pero trabajando con
//un entero de 32 bits.
int8_t leon3_print_uint32(uint32_t i);

#endif /* LEON3_BPRINT_H_ */
