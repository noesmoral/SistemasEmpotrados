/*
 * main.c
 *
 *  Created on: Feb 5, 2016
 *      Author: pedro
 */

#include "leon3_uart.h"	//Include del .h donde esta la funcion
#include "leon3_bprint.h"

int main(){
	//Programa 1
	//leon3_putchar('p');	//pasamos un p
	//leon3_putchar('2');	//pasamos un 2
	//leon3_putchar('\n');//pasamos un salto de linea

	//Programa 2
	char * pchar="cadena\n";
	leon3_print_string(pchar);
	leon3_print_uint8(155);

	return 0;
}
