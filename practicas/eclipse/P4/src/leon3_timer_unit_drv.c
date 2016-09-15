/*
 * leon3_timer_unit_ctrl.c
 *
 *  Created on: Mar 19, 2013
 *      Author: user
 */

#include "leon3_types.h"


//*******************************************************************
/** \brief structure for controlling Timer Registers */

struct Timer_regs{

	/** \brief Timer Counter Value Register */
	volatile uint32_t CounterValue;

	/** \brief Timer Reload Value Register */
	volatile uint32_t ReloadValue;

	/** \brief Timer Control Register */
	volatile uint32_t Ctrl;

	uint32_t 		  reserved;

};

//! LEON3 Timers integrated in the Timer Unit

#define LEON3_TIMER_UNIT_TIMERS 					2

//! LEON3 Timer Ctrl Masks

#define LEON3_TIMER_CHAIN_WITH_PREC_TIMER 	(0x020)
#define LEON3_TIMER_CLEAR_IRQ 				(0x010)
#define LEON3_TIMER_ENABLE_IRQ 				(0x008)
#define LEON3_TIMER_LOAD_TIMER 				(0x004)
#define LEON3_TIMER_RESTART 				(0x002)
#define LEON3_TIMER_ENABLE 					(0x001)


//*******************************************************************

/** \brief structure for controlling Timer Unit Registers */

struct TimerUnit_regs
{

	/** \brief Timer Unit Scaler Register */
	volatile uint32_t ScalerValue;			/* 0x80000300 */
	/** \brief Timer Unit Scaler Reload Value Register */
	volatile uint32_t ScalerReloadValue; 	/* 0x80000304 */
	/** \brief Timer Unit Configuration Register */
	volatile uint32_t ConfigReg; 			/* 0x80000308 */

	uint32_t 		 reserved; 				/* 0x8000030A */

	/** \brief Registers of the Timers*/
	volatile struct Timer_regs			Timer[LEON3_TIMER_UNIT_TIMERS];

};


//! LEON3 Timing Unit Masks

#define LEON3_TIMER_UNIT_ACTIVE_FREEZE (0x200)
#define LEON3_TIMER_UNIT_SEPARATE_IRQS (0x100)


//! LEON3 Timing Unit
struct TimerUnit_regs *pLEON3_TimerUnit_REGS = (struct TimerUnit_regs *)0x80000300;

//*******************************************************************

void leon3_TimerUnit_SetConfiguration( uint32_t scalerValue
									, bool_t timer_freeze_during_debug
									, bool_t separate_interrupts ){


	if(timer_freeze_during_debug)
		pLEON3_TimerUnit_REGS->ConfigReg|=LEON3_TIMER_UNIT_ACTIVE_FREEZE;
	else
		pLEON3_TimerUnit_REGS->ConfigReg&=(~LEON3_TIMER_UNIT_ACTIVE_FREEZE);

	if(separate_interrupts)
		pLEON3_TimerUnit_REGS->ConfigReg|=LEON3_TIMER_UNIT_SEPARATE_IRQS;
	else
		pLEON3_TimerUnit_REGS->ConfigReg&=(~LEON3_TIMER_UNIT_SEPARATE_IRQS);

	pLEON3_TimerUnit_REGS->ScalerReloadValue=scalerValue;
	pLEON3_TimerUnit_REGS->ScalerValue=scalerValue;

}


//*******************************************************************

uint8_t leon3_TimerConfig(uint8_t timerId
					, uint32_t timerValue
					, bool_t chain_with_prec_timer
					, bool_t restart_timer){

	/*Rutina que permite configurar los dos timers de la Timer Unit, fijando el valor
	de sus registros Timer Control Register, Timer Counter Value Register y Timer
	Counter Reload Value Register. Su prototipo es el siguiente:
	void leon3_TimerConfig(uint8_t timerId, uint32_t timerValue, bool_t chain_with_prec_timer, bool_t restart_timer);
	El parámetro timerId indica si se va configurar el timer0 ( timerId==0 ) o el
	timer1 ( timerId==1 ). El parametro timerValue inicializa el valor de los
	registros Timer Counter Value y Timer Counter Reload Value, mientras que los
	parámetros chain_with_prec_timer y restart_timer se utilizan para
	inicializar los campos CH y RX del registro Timer Control Register (ver la figura
	3). Para modificar el registro Timer Counter Value primero se fija el valor del
	Timer Counter Reload Value y después se activa el campo LD del Timer Control
	Register. El campo chain_with_prec_timer, por su parte, determina si el
	timer toma como pulso de entrada el pulso de salida del timer anterior (modoencadenado) o el pulso de salida del prescaler (En la version de evaluación de
	TSIM2 el modo encadenado está dehabilitado). El parámetro restart_timer ,
	por su parte, determina si tras la situación de undeflow el registro Timer Counter
	Value se reinicia ( restart_timer !=0) o no ( restart_timer ==0) con el valor
	de Timer Counter Reload Value. La siguiente figura muestra el conjunto de
	registros que constituyen el controlador de la Timer Unit.*/

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].ReloadValue=timerValue;

		if(chain_with_prec_timer){
			pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl|32;//chain_with_prec_timer CH
		}else{
			pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=(~(~(pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl)|32));
		}

		if(chain_with_prec_timer==0){
			pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl|2; //RS
		}else{
			pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=(~(~(pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl)|2)); //RS
		}

		// Se carga el valor
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl|=LEON3_TIMER_LOAD_TIMER;

	}else
		error=1;

	return error;

}

//*******************************************************************

uint8_t leon3_TimerEnableIRQ(uint8_t timerId){

	/*Rutinas que habilitan y deshabilitan la interrupción asociada a la situación de
	underflow de un timer.
	uint8_t leon3_TimerEnableIRQ(uint8_t timerId);
	uint8_t leon3_TimerDisableIRQ(uint8_t timerId);
	El parámetro timerId indica si la habilitación afecta al timer0 ( timerId==0 ) o o
	al timer1 ( timerId==1 ). Ambas funciones modifican el campo IE del registro
	Timer Control Register.*/

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl|8;

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerDisableIRQ(uint8_t timerId){

	/*Rutinas que habilitan y deshabilitan la interrupción asociada a la situación de
	underflow de un timer.
	uint8_t leon3_TimerEnableIRQ(uint8_t timerId);
	uint8_t leon3_TimerDisableIRQ(uint8_t timerId);
	El parámetro timerId indica si la habilitación afecta al timer0 ( timerId==0 ) o o
	al timer1 ( timerId==1 ). Ambas funciones modifican el campo IE del registro
	Timer Control Register.*/

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=(~(~(pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl)|8));

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerEnable(uint8_t timerId){

	/*Rutinas que habilitan y deshabilitan los timers.
	uint8_t leon3_TimerEnable(uint8_t timerId);
	uint8_t leon3_TimerDisable(uint8_t timerId);
	El parámetro timerId indica si la habilitación afecta al timer0 ( timerId==0 ) o o
	al timer1 ( timerId==1 ). Ambas funciones modifican el campo EN del registro
	Timer Control Register.*/

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl|1;

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerDisable(uint8_t timerId){

	/*Rutinas que habilitan y deshabilitan los timers.
	uint8_t leon3_TimerEnable(uint8_t timerId);
	uint8_t leon3_TimerDisable(uint8_t timerId);
	El parámetro timerId indica si la habilitación afecta al timer0 ( timerId==0 ) o o
	al timer1 ( timerId==1 ). Ambas funciones modifican el campo EN del registro
	Timer Control Register.*/

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=(~(~(pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl)|1));

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerUnit_ClearIRQ(uint8_t timerId){

	/*Rutina que borra el bit IP del registro Timer Control Register. Ese bit se pone
	automáticamente a 1 cuando se produce una interrupción debida a una situación
	de underflow. Debe ser borrado en el manejador de la interrupción para indicar
	que la interrupción ya ha sido atendida.
	uint8_t leon3_TimerUnit_ClearIRQ(uint8_t timerId);*/

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl=(~(~(pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl)|16));

	}else
		error=1;

	return error;

}


