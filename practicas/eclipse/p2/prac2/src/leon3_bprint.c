/*
 * leon3_bprint.c
 *
 *  Created on: Feb 12, 2016
 *      Author: pedro
 */

#include "leon3_bprint.h"	//incluimos las definiciones propias
#include "leon3_uart.h"		//incluimos las funciones de uart

int8_t leon3_print_string(char* str){
	//variables aux que sera el inicio de recorrido
	int cont=0;

	while(str[cont]!='\0'){			//recorre el arry de char hasta encontrar el \0 que indica el final
		leon3_putchar(str[cont]);	//se envia para imprimir el char en el que nos encontramos
		cont++;						//aumentamos el contador para que en la proxima iteracion se use el proximo caracter
	}
	return 0;
}

int8_t leon3_print_uint8(uint8_t i){
	//variable contador inicializada a 0
	int aux=0;

	if (i<=9){	//caso de solo unidades numero menor a 9
		aux=i;				//sacamos las unidades
		leon3_putchar('0'+aux);	//usamos el cacter 0 como base y le sumamos el numero tambien so podria usar directamente 'X'
	}else if(i>9 && i<=99){	//caso de decenas y unidades
		aux=((i/10)%10);	//sacamos las decenas
		leon3_putchar('0'+aux);
		aux=i%10;			//sacamos las unidades
		leon3_putchar('0'+aux);
	}else{		//caso de centenas decenas y unidades
		aux=((i/10)/10);	//sacamos las centenas
		leon3_putchar('0'+aux);
		aux=((i/10)%10);	//sacamos las decenas
		leon3_putchar('0'+aux);
		aux=i%10;			//sacamos las unidades
		leon3_putchar('0'+aux);
	}
	leon3_putchar('\n');	//salto de linea para que sea mas legible al mostrarse el codigo
	return 0;
}



