/*
 * main.c
 *
 *  Created on: Feb 5, 2016
 *      Author: pedro
 */

//archivo en el que se encuentra la funcion especicicada usada en main

//Declaraciones del uso de lib y demas
#include "leon3_uart.h"

//especificamos una mascara con la que compararemos para verificar si esta en un estado concreto un valor  de status
#define LEON3_UART_TFF (0x200) //0x200en exa es 512 en decimal que en binario es 0..1000000000 que es el bit que queremos obtener

//Declaracion del registro y su estructura
struct UART_regs{
	/** \brief UART Data Register */
	volatile uint32_t Data; // 0x80000100
	/** \brief UART Status Register */
	volatile uint32_t Status; // 0x80000104
	/** \brief UART Control Register */
	volatile uint32_t Ctrl; // 0x80000108
	/** \brief UART Scaler Register */
	volatile uint32_t Scaler; // 0x8000010C
};

//Definicion del registro de la estructura y lo ubucamos en 0x80000100
struct	UART_regs * pLEON3_UART_REGS = 0x80000100;

//funcion que recibe un caracter y espera hasta que le permitan escribir o venza el tiempo
int8_t leon3_putchar(char c){
	uint32_t write_timeout=0;

	//esperamos por permiso mientras tengamos tiempo
	while(((LEON3_UART_TFF & pLEON3_UART_REGS->Status)==0x200) && (write_timeout < 0xAAAAA)){
		write_timeout++;
	}

	//Si no hemos llegado al limite de tiempo escribir en data
	if(write_timeout < 0xAAAAA){
		pLEON3_UART_REGS->Data = (uint32_t)c;	//pasamos el valor a el registo en la posicion data
	}
	return (write_timeout == 0xAAAAA);	//salida en funcion de lo que haya pasado
}
