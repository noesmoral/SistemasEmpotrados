/*
 * leon3_bprint.h
 *
 *  Created on: Feb 12, 2016
 *      Author: pedro
 */

#ifndef LEON3_BPRINT_H_
#define LEON3_BPRINT_H_

#include "leon3_types.h"	//incliye los tipos de datos ya definidos

//transmite a través del puerto serie la cadena de caracteres
//pasada por parámetro.
int8_t leon3_print_string(char* str);	//el final de la cadena tiene que ser '\0'

//transmite a través del puerto serie el entero transformado en
//cadena de caracteres.
int8_t leon3_print_uint8(uint8_t i);	//tamaño maximo 8 bit 255 por lo que solo tiene 3 caracteres

#endif /* LEON3_BPRINT_H_ */
