/*
 * leon3_timing_service_config.h
 *
 *  Created on: Apr 2, 2013
 *      Author: user
 */

#include "leon3_types.h"

#ifndef LEON3_TIMING_SERVICE_CONFIG_H_
#define LEON3_TIMING_SERVICE_CONFIG_H_
#define TIMING_SERVICE_HYPER_PERIOD_IN_TICKS 4

	//! \brief TICS PER SECOND
	#define TIMING_SERVICE_TICKS_PER_SECOND 		10


	/** \brief Init Timing Service
	 *
	 *  \param IRQHandler timer irq handler to install
	 *
	 */

	void InitTimingService(	void (* IRQHandler) (void));

#endif /* LEON3_TIMING_SERVICE_CONFIG_H_ */
