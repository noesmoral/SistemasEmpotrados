/*
 * leon3_irqs.h
 *
 *  Created on: Feb 28, 2013
 *      Author: user
 */

#ifndef IRQS_H_
#define IRQS_H_

#include "leon3_types.h"

void leon3_trap_handler_enable_irqs(void);

void leon3_trap_handler_disable_irqs(void);

uint8_t leon3_mask_irq (int32_t irq_level);

uint8_t leon3_unmask_irq (int32_t irq_level);

uint8_t leon3_clear_irq (int32_t irq_level);


void leon3_sys_call_enable_irqs(void);

void leon3_sys_call_disable_irqs(void);

uint8_t leon3_sparc_force_irq (int32_t irq_level);

void leon3_sparc_isr(void);




#endif
