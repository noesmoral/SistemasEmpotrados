/*
 * main.c
 *
 *  Created on: Mar 4, 2016
 *      Author: pedro
 */

#include "leon3_traps.h"
#include "leon3_irqs.h"
#include "leon3_monotonic_clk.h"
#include "leon3_timer_unit_drv.h"
#include "leon3_timing_service_config.h"

int main(){
	uint32_t aux1,aux2;
	//Instalar manejadores para habilitar y deshabilitar irqs
	leon3_install_handler(LEON3_SPARC_ENABLE_IRQ_TRAPVECTOR,leon3_trap_handler_enable_irqs);
	leon3_install_handler(LEON3_SPARC_DISABLE_IRQ_TRAPVECTOR ,leon3_trap_handler_disable_irqs);
	//Inicializar Reloj Monotónico.
	InitMonotonicClock(date_time_to_Y2K(1, 1, 13, 0, 0, 1 ));
	//Iniciar el Servicio de Temporización para que en cada
	//interrupción se invoque a la rutina que actualiza el reloj
	//monotónico
	InitTimingService(IRQHandlerUpdateMonotonicClock);
	aux2=0;
	while(1){
			aux1=GetUniversalTime_Y2K();
			//Cada 10 segundos imprimimos el tiempo
			if(((aux1%10)==0)&& aux1!=aux2){
				leon3_sys_call_disable_irqs();
				print_date_time_from_Y2K(aux1);
				aux2=aux1;
				leon3_sys_call_enable_irqs();
			}
	}
	return 0;
}

