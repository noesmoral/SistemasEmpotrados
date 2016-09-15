
#include "leon3_types.h"

/** \brief UART register map */
struct UART_regmap
{
	/** \brief UART 1 Data Register */
	volatile uint32_t uart_data;                       /* 70 */
	/** \brief UART 1 Status Register */
	volatile uint32_t uart_status;                     /* 74 */
	/** \brief UART 1 Control Register */
	volatile uint32_t uart_control;                    /* 78 */
	/** \brief UART 1 Scaler Register */
	volatile uint32_t uart_scaler;                     /* 7C */
	
};

//!LEON3 UART A ready for transmit data
#define LEON3_UART_THEA (0x200)


struct   UART_regmap * pLEON3_UART_REGMAP= (struct   UART_regmap *)0x80000100;

int8_t leon3_putchar(char c)
{
	
	uint32_t write_timeout=0;
			
	while(
			((pLEON3_UART_REGMAP->uart_status & LEON3_UART_THEA))
			&&(write_timeout < 0xAAAAA)
		){
			write_timeout++;
			
	}
	if(write_timeout <  0xAAAAA)
		pLEON3_UART_REGMAP->uart_data=c;
	
	return (write_timeout ==  0xAAAAA);
}


int8_t leon3_setbaudrate(word16_t baudrate){
	
	pLEON3_UART_REGMAP->uart_scaler=baudrate&0x0FFF;
	return 0;
}
