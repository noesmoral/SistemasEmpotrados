/*
 * main.c
 *
 *  Created on: Feb 29, 2016
 *      Author: pedro
 */


#include "leon3_uart.h"
#include "leon3_bprint.h"
#include "leon3_traps.h"
#include "leon3_irqs.h"

void hw_irq_vector_0x11_handler(void){
	leon3_print_string("handler hw irq vector 0x11\n");
}

void trap_division_0_handler(void){
	leon3_print_string("error, division por cero\n");
}

//main normal
int main(){
	//Instalar como manerjador del trap 0x83 la rutina
	//que habilita las interrupciones
	leon3_install_handler(0x83,leon3_trap_handler_enable_irqs);

	//instalar el manejador del trap que 0x83 la rutina
	//que desabilita las interrupciones
	leon3_install_handler(0x84,leon3_trap_handler_disable_irqs);

	//instalar la funcion hw_irq_vector_0x11_handler como
	//manejador de la interrupcion de nivel 1
	leon3_install_handler(0x11,	hw_irq_vector_0x11_handler);

	//Habilitar las interrupciones
	leon3_sys_call_enable_irqs();

	//Apartado 4: Repetir la ejecución poniendo un breakpoint en la primera instrucción de la
	//función leon3_trap_handler_enable_irqs definida en leon3_irqs_asm.S y
	//otro en la llamada a la función leon3_sys_call_enable_irqs que se
	//encuentra en el main, y que se ha definido como wrapper del trap 3 (vector
	//0x83). Ejecutar paso a paso para comprobar cual es el comportamiento. ¿A qué
	//función salta tras la instrucción en ensamblador ta ? salta a la llamada/funcion leon3_trap_handler_enable_irqs

	//Apartado 6:Hacer lo mismo pero llamando a leon3_sys_call_disable_irqs() en vez de
	//a leon3_sys_call_enable_irqs() y comprobando que tampoco se genera ningún mensaje.
	//leon3_sys_call_disable_irqs();	//tampoco genera mensaje

	//desenmascarar las interrupcoones de nivel 1 (correspondientes
	//al vector 0x11)
	leon3_unmask_irq(1);

	//Apartado 5: Repetir la ejecución enmascarando la interrupción (usa leon3_mask_irq ) antes
	//de leon3_sparc_force_irq(1) y comprobar que no se genera ningún mensaje por pantalla.
	//leon3_mask_irq(1);	//salta el mensaje no lo muestra

	//fuerza la interrupcion
	leon3_sparc_force_irq(1);

	return 0;
}

//Apartado 7:Ejecutar el siguiente código. ¿Qué ocurre? Sabiendo que cuando se produce una
//división por 0 la rutina que lo gestiona llama al trap 0x82, ¿cómo utilizarías la
//función leon3_install_handler para conseguir que el programa no se cuelgue
//y en su lugar imprima un mensaje que diga “error, división por cero”?
/*int main(){
	uint8_t i;
	uint8_t j;

	//Instalamos la funcion que detecta divisiones entre 0
	leon3_install_handler(0x82,trap_division_0_handler);

	for(i=10; i>0; i--)
		j=j/(i-9);

	return 0;
}*/
