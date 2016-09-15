#include "leon3_uart.h"

int8_t leon3_print_string(char* str){
	int8_t error=0;
	
	while(*str!='\0'&&(!error)){
		error=leon3_putchar(*str);
		str++;
	}
	return error;
	
}

int8_t leon3_print_uint32(uint32_t i){
	
	int8_t error=0;
	uint32_t aux;
	int8_t first_digit=0;
	aux=1000000000;

	if(i==0)
		leon3_putchar('0');
	else{
		while(aux&&(!error)){
			uint8_t digit;

			digit=i/aux;
			i-=aux*digit;
			aux=aux/10;
			if(first_digit||digit){
				error=leon3_putchar('0'+digit);
				first_digit=1;
			}
		}
	}
	return error;
	
}

int8_t leon3_print_uint8(uint8_t i){

	int8_t error=0;
	uint8_t aux;
	int8_t first_digit=0;
	aux=100;

	if(i==0)
		leon3_putchar('0');
	else{
		while(aux&&(!error)){
			uint8_t digit;

			digit=i/aux;
			i-=aux*digit;
			aux=aux/10;
			if(first_digit||digit){
				error=leon3_putchar('0'+digit);
				first_digit=1;
			}
		}
	}
	return error;

}
