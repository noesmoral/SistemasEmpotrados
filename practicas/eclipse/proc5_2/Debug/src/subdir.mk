################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/leon3_uart.c \
../src/leon_bprint.c \
../src/prac5_2.c 

OBJS += \
./src/leon3_uart.o \
./src/leon_bprint.o \
./src/prac5_2.o 

C_DEPS += \
./src/leon3_uart.d \
./src/leon_bprint.d \
./src/prac5_2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C Compiler'
	sparc-rtems-gcc -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/pedro/workspace/proc5_2/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


