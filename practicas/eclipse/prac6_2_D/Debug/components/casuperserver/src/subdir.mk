################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/casuperserver/src/CASuperServerC.cpp \
../components/casuperserver/src/CASuperServerE.cpp 

OBJS += \
./components/casuperserver/src/CASuperServerC.o \
./components/casuperserver/src/CASuperServerE.o 

CPP_DEPS += \
./components/casuperserver/src/CASuperServerC.d \
./components/casuperserver/src/CASuperServerE.d 


# Each subdirectory must supply rules for building sources it contributes
components/casuperserver/src/%.o: ../components/casuperserver/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/pedro/workspace/prac6_2_D/components/caclient/include" -I"/home/pedro/workspace/prac6_2_D/components/caserver/include" -I"/home/pedro/workspace/prac6_2_D/components/casuperserver/include" -I"/home/pedro/workspace/prac6_2_D/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2_D/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2_D/config/include" -I"/home/pedro/workspace/prac6_2_D/edroom_glue/include" -I"/home/pedro/workspace/prac6_2_D/edroombp_swr/include" -I"/home/pedro/workspace/prac6_2_D/edroomsl_swr/include" -I"/home/pedro/workspace/prac6_2_D/edroomsl_types_swr/include" -I"/home/pedro/workspace/prac6_2_D/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


