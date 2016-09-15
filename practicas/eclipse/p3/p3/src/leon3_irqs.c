/*
 * leon_irqs.c
 *
 *  Created on: Feb 28, 2013
 *      Author: user
 */
#include "leon3_types.h"	//Incluimos para poder utilizar las llamadas a las funciones

uint32_t * LEON3_ICLEAR =  (uint32_t *) (0x80000000 + 0x20c);	//registro iclear ubicado en 0x8000020c
uint32_t * LEON3_IMASK =  (uint32_t *) (0x80000000 + 0x240);	//registro imask ubicado en 0x80000240
uint32_t * LEON3_IFORCE =  (uint32_t *) (0x80000000 + 0x208);	//registro iforce ubicado en 0x80000208

//leon3_force_irq(int32_t irq_level) permite forzar el disparo de uno de los 15 niveles de interrupción externa poniendo a 1 en el registro
//IFORCE el bit correspondiente al nivel (este registro está ubicado en la dirección 0x80000208). El número de nivel debe suministrarse mediante
//el parámetro irq_level
uint8_t leon3_sparc_force_irq (int32_t irq_level) {
	uint8_t error=0;
	if(irq_level <16){	//en caso de ser una interpcion valida de 0 a 15
		*LEON3_IFORCE=(*LEON3_IFORCE | (0x1<<(irq_level)));	//<< significa desplazamiento
		//*LEON3_IFORCE=(1<<irq_level);
		// COMPLETAR Poniendo a 1 SOLO el bit correspondiente al irq_level de LEON3_IFORCE
		// irq_level=0 corresponde al bit de menor peso
		// mientras que irq_level=15 corresponde al de mayor peso.
	}else
		error=1;
	return error;
}

//leon3_unmask_irq(int32_t irq_level) permite desenmascarar uno de los 15 niveles de interrupción externa poniendo a 1 en el registro
//registro IMASK el bit correspondiente al nivel. El número de nivel debe suministrarse mediante el parámetro irq_level
uint8_t leon3_unmask_irq (int32_t irq_level){
	uint8_t error=0;
	if(irq_level<16){	//en caso de ser una interpcion valida de 0 a 15
		*LEON3_ICLEAR = (1 << irq_level);	// clear any pending irq of that level
		*LEON3_IMASK=(*LEON3_IMASK | (0x1<<(irq_level)));	//<< significa desplazamiento
		//*LEON3_IMASK=(1<<irq_level);
		// COMPLETAR Poniendo a 1 SOLO el bit correspondiente al irq_level de LEON3_IMASK
		// irq_level=0 corresponde al bit de menor peso
		// mientras que irq_level=15 corresponde al de mayor peso.
	}else
		error=1;
	return error;
}

//leon3_mask_irq(int32_t irq_level) permite enmascarar uno de los 15 niveles de interrupción externa poniendo a 0 en el registro registro
//IMASK el bit correspondiente al nivel (este registro está ubicado en la dirección 0x80000240). El número de nivel debe suministrarse mediante
//el parámetro irq_level.
uint8_t leon3_mask_irq (int32_t irq_level) {
	uint8_t error=0;
	if(irq_level <16){	//en caso de ser una interpcion valida de 0 a 15
		*LEON3_IMASK=~((~*LEON3_IMASK) | (0x1<<(irq_level))); //<< significa desplazamiento
		//*LEON3_IMASK=(0<<irq_level);
		// COMPLETAR Poniendo a 0 SOLO el bit correspondiente al irq_level de LEON3_IMASK
		// irq_level=0 corresponde al bit de menor peso
		// mientras que irq_level=15 corresponde al de mayor peso.
	}else
		error=1;
	return error;
}
