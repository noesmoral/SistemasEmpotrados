################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bprint_swr/src/bprint.c \
../bprint_swr/src/leon3_bprint.c \
../bprint_swr/src/leon3_uart.c 

OBJS += \
./bprint_swr/src/bprint.o \
./bprint_swr/src/leon3_bprint.o \
./bprint_swr/src/leon3_uart.o 

C_DEPS += \
./bprint_swr/src/bprint.d \
./bprint_swr/src/leon3_bprint.d \
./bprint_swr/src/leon3_uart.d 


# Each subdirectory must supply rules for building sources it contributes
bprint_swr/src/%.o: ../bprint_swr/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C Compiler'
	sparc-rtems-gcc -I"/home/pedro/workspace/prac7_1/rtems_osswr/include" -I"/home/pedro/workspace/prac7_1/bprint_swr/include" -I"/home/pedro/workspace/prac7_1/edroomsl_types_swr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


