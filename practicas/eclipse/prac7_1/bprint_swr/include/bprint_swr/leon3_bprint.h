#ifndef LEON3_BPRINT_H_
#define LEON3_BPRINT_H_


	#include <public/basic_types.h>

#ifdef __cplusplus

extern "C" {

#endif
	int8_t leon3_print_uint32(uint32_t i);
	int8_t leon3_print_int32(uint32_t i);
	int8_t leon3_print_uint8(uint8_t i);
	int8_t leon3_print_string(const char* str);


#ifdef __cplusplus

}

#endif

	#include <bprint_swr/leon3_uart.h>

	
#endif /*LEON3_BPRINT_H_*/
