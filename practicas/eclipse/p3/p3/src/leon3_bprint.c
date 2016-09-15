/*
 * leon3_bprint.c
 *
 *  Created on: Feb 12, 2016
 *      Author: pedro
 */

#include "leon3_bprint.h"
#include "leon3_uart.h"

int8_t leon3_print_string(char* str){
	//variables aux
	int cont=0;

	while(str[cont]!='\0'){	//recorre el arry de char hasta encontrar el /0
		leon3_putchar(str[cont]);
		cont++;
	}
	return 0;
}

int8_t leon3_print_uint8(uint8_t i){
	int aux=0;

	if (i<=9){	//caso de solo unidades
		aux=i;				//unidades
		leon3_putchar('0'+aux);
	}else if(i>9 && i<=99){	//caso de decenas y unidades
		aux=((i/10)%10);	//decenas
		leon3_putchar('0'+aux);
		aux=i%10;			//unidades
		leon3_putchar('0'+aux);
	}else{		//caso de centenas decenas y unidades
		aux=((i/10)/10);	//centenas
		leon3_putchar('0'+aux);
		aux=((i/10)%10);	//decenas
		leon3_putchar('0'+aux);
		aux=i%10;			//unidades
		leon3_putchar('0'+aux);
	}
	leon3_putchar('\n');	//salto de linea para que sea mas legible
	return 0;
}

int8_t leon3_print_uint32(uint32_t i){
		int aux=i;
		int vector[10];
		int cont=0;

		do{	//alamcenamos en orden desde unidades hacia arriba
			vector[cont]=aux%10;
			aux=aux/10;
			cont++;
		}while(aux%10!=0);

		do{	//mostramos en orden desde el ultimo insertado hasta unidades
			cont--;
			leon3_putchar('0'+vector[cont]);
		}while(cont!=0);

		leon3_putchar('\n');	//salto de linea para que sea mas legible
		return 0;
}



