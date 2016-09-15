/*
 * main.c
 *
 *  Created on: Mar 4, 2016
 *      Author: pedro
 */

#include "leon3_traps.h"
#include "leon3_irqs.h"
#include "leon3_traps.h"
#include "leon3_uart.h"
#include "leon3_bprint.h"

#include "leon3_monotonic_clk.h"
#include "leon3_timer_unit_drv.h"
#include "leon3_timing_service_config.h"
#include "leon3_ttre.h"

//declaracion de las funciones para poder usarlas
void ROBOTAvoidObstacles(void){
	leon3_print_string(" Avoid Obstacles\n");
}
void ROBOTAdvanceInPath(void){
	leon3_print_string(" Advance\n");
}
void ROBOTCalculatePath(void){
	leon3_print_string(" Calculate Path\n");
}

int main(){
	uint32_t aux1,aux2;

	//Install handlers for enable and disable irqs
	leon3_install_handler(LEON3_SPARC_ENABLE_IRQ_TRAPVECTOR,
	leon3_trap_handler_enable_irqs);
	leon3_install_handler(LEON3_SPARC_DISABLE_IRQ_TRAPVECTOR ,
	leon3_trap_handler_disable_irqs);
	//Init Monotonic Clock (rutina que inicializa las variables que gestionan  el roloj
	//monotonico y fija una referencia de tiempo unicersarl Y2K)
	//Year2K es una referencia de 32bit que va desde el 1 de enero del 2000
	InitMonotonicClock(date_time_to_Y2K(1, 1, 13, 0, 0, 1 ));

	//Rutina que inicializa el servicio de programación de la ejecución de rutinas en el
	//tiempo.
	TTRE_InitService();

	//Rutina que permite programar una rutina dentro de un ejecutivo cíclico definiendo
	//el offset con respecto al hiper-periodo.
	TTRE_ProgramRoutine(ROBOTAvoidObstacles, 00000);
	TTRE_ProgramRoutine(ROBOTCalculatePath, 100000);
	TTRE_ProgramRoutine(ROBOTAvoidObstacles, 200000);
	TTRE_ProgramRoutine(ROBOTAdvanceInPath, 300000);

	//Rutina que permite programar una rutina cata tick dentro de un ejecutivo cíclico.
	//Este servicio nos va a permitir instalar la rutina de gestión del tiempo monotónico.
	TTRE_ProgramRoutineEveryTick(UpdateMonotonicClock);

	//Init Timing Service
	InitTimingService(IRQHandlerExecuteProgrammedRoutines);

	aux2=0;
	while(1){
		aux1=GetUniversalTime_Y2K();//da el valor del tiempo pasado desde el Y2K
		//Cada segundo
		if(aux1!=aux2){
			leon3_sys_call_disable_irqs();
			print_date_time_from_Y2K(aux1);//imprime el valor actual del tiempo universal
			aux2=aux1;
			leon3_sys_call_enable_irqs();
		}
	}
	return 0;
}


