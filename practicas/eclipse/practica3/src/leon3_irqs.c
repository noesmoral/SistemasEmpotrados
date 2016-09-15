/*
 * leon_irqs.c
 *
 *  Created on: Feb 28, 2013
 *      Author: user
 */
#include "leon3_types.h"

uint32_t * LEON3_ICLEAR =  (uint32_t *) (0x80000000 + 0x20c);
uint32_t * LEON3_IMASK =  (uint32_t *) (0x80000000 + 0x240);
uint32_t * LEON3_IFORCE =  (uint32_t *) (0x80000000 + 0x208);

#define mascara (0x1);

uint8_t leon3_sparc_force_irq (int32_t irq_level) {
	uint8_t error=0;
	if(irq_level <16){
		*LEON3_IFORCE=(*LEON3_IFORCE | (0x1<<(irq_level)));
		//*LEON3_IFORCE=(1<<irq_level);
		// COMPLETAR Poniendo a 1 SOLO el bit correspondiente al irq_level de LEON3_IFORCE
		// irq_level=0 corresponde al bit de menor peso
		// mientras que irq_level=15 corresponde al de mayor peso.
	}else
		error=1;

	return error;

}

uint8_t leon3_unmask_irq (int32_t irq_level)
{
	uint8_t error=0;
	if(irq_level<16){
		*LEON3_ICLEAR = (1 << irq_level);	// clear any pending irq of that level
		*LEON3_IMASK=(*LEON3_IMASK | (0x1<<(irq_level)));
		//*LEON3_IMASK=(1<<irq_level);
		// COMPLETAR Poniendo a 1 SOLO el bit correspondiente al irq_level de LEON3_IMASK
		// irq_level=0 corresponde al bit de menor peso
		// mientras que irq_level=15 corresponde al de mayor peso.
	}else
		error=1;
	return error;



}

uint8_t leon3_mask_irq (int32_t irq_level) {
	uint8_t error=0;
	if(irq_level <16){
		*LEON3_IMASK=~((~*LEON3_IMASK) | (0x1<<(irq_level)));
		//*LEON3_IMASK=(0<<irq_level);
		// COMPLETAR Poniendo a 0 SOLO el bit correspondiente al irq_level de LEON3_IMASK
		// irq_level=0 corresponde al bit de menor peso
		// mientras que irq_level=15 corresponde al de mayor peso.
	}else
		error=1;
	return error;

}	// mask irq
