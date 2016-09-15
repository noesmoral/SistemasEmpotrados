/*
 * traps.h
 *
 *  Created on: Feb 28, 2013
 *      Author: user
 */

#ifndef TRAPS_H_
#define TRAPS_H_

#include "leon3_types.h"


// Public functions

int32_t leon3_install_handler(uint32_t trap_vector, void (* handl_routine) (void));


// Error list

#define LEON3_ERR_SUCCESS             0
#define LEON3_ERR_TRAP_HANDLER       -1
#define LEON3_ERR_INIT               -2


#define LEON3_SPARC_DIV_0_TRAPVECTOR   	 	0x82
#define LEON3_SPARC_ENABLE_IRQ_TRAPVECTOR   0x83
#define LEON3_SPARC_DISABLE_IRQ_TRAPVECTOR  0x84



#endif /* TRAPS_H_ */
