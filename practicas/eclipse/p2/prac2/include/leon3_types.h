/*
 * leon3_types.h
 *
 *  Created on: Feb 5, 2016
 *      Author: pedro
 */

//Declaracion de los tipos de datos con sus formatos concretos y sus tamaños
//Estas definiciones son las usadas por el programa y los formatos han de ser los
//correctos para evitar errores

#ifndef LEON3_TYPES_H
#define LEON3_TYPES_H

typedef unsigned char byte_t;			//8bits  1 byte
typedef unsigned short int word12_t;	//16bits 1 words
typedef unsigned int word32_t;			//32bits 2 words
typedef unsigned long int word64_t;		//64bits 4 words

typedef signed char int8_t;				//8bits  1 byte
typedef signed short int int16_t;		//16bits 1 words
typedef signed int int32_t;				//32bits 2 words
typedef signed long int int64_t;		//64bits 4 words

typedef unsigned char uint8_t;			//8bits  1 byte
typedef unsigned short int uint16_t;	//16bits 1 words
typedef unsigned int uint32_t;			//32bits 2 words
typedef unsigned long int uint64_t;		//64bits 4 words

#endif
