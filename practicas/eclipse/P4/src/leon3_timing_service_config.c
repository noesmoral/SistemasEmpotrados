#include "leon3_types.h"

#include "leon3_timer_unit_drv.h"
#include "leon3_traps.h"
#include "leon3_irqs.h"

#include "leon3_timing_service_config.h"


void InitTimingService(	void (* IRQHandler) (void)){

	//frecuencia_base_timers = frecuencia_clk / (prescaler reload + 1)

	leon3_TimerUnit_SetConfiguration( 19, true , true );//prescaler reload 19

	leon3_TimerEnable(0);

	//frecuencia_base_timer 1MHz = 1000000 intervalo (tiempo entre interupciones)  TIMING_SERVICE_TICKS_PER_SECOND=10
	leon3_TimerConfig(0, 1000000UL/TIMING_SERVICE_TICKS_PER_SECOND, false, true);

	leon3_install_handler(0x18, IRQHandler);

	leon3_TimerEnableIRQ(0);

	leon3_sys_call_enable_irqs();

	leon3_unmask_irq(8);

}
