#ifndef LEON3_UART_H_
#define LEON3_UART_H_

#include <public/basic_types.h>

/** \brief put a char in the UART FIFO buffer for sending it.
 *
 *	\param c char to send
 *
 *	\return 0 if there is no error, 1 if char cannot be inserted in the FIFO buffer
 */

#ifdef __cplusplus

extern "C" {

#endif

	int8_t leon3_putchar(char c);

#ifdef __cplusplus

}

#endif

/** \brief set the UART baudrate.
 *
 *	\param baudrate UART baudrate
 *
 *	\return 1 if baudrate is out of range, 0 if not.
 */

int8_t leon3_setbaudrate(word16_t baudrate);


#endif /* LEON3_UART_H_ */
