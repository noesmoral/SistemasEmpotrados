/*
 * main.c
 *
 *  Created on: Feb 19, 2016
 *      Author: pedro
 */

#include "leon3_uart.h"
#include "leon3_bprint.h"
#include "leon3_traps.h"
#include "leon3_irqs.h"

void hw_irq_vector_0x11_handler(void){
	leon3_print_string("handler hw irq vector 0x11\n");
}

int main(){
	//Instalar como manerjador del trap 0x83 la rutina
	//que habilita las interrupciones
	leon3_install_handler(0x83,leon3_trap_handler_enable_irqs);

	//instalar el manejador del trap que 0x83 la rutina
	//que desabilita las interrupciones
	leon3_install_handler(0x84,leon3_trap_handler_disable_irqs);

	//instalar la funcion hw_irq_vector_0x11_handler como
	//manejador de la interrupcion de nivel 1

	//COMPLETAR creo que es algo asi
	leon3_install_handler(0x11,	hw_irq_vector_0x11_handler);
	//

	//Habilitar las interrupciones
	leon3_sys_call_enable_irqs();

	//desenmascarar las interrupcoones de nivel 1 (correspondientes
	//al vector 0x11)
	leon3_unmask_irq(1);

	//fuerza la interrupcion
	leon3_sparc_force_irq(1);

	return 0;
}

