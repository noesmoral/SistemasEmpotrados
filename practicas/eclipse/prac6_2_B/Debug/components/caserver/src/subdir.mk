################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/caserver/src/CAServerC.cpp \
../components/caserver/src/CAServerE.cpp 

OBJS += \
./components/caserver/src/CAServerC.o \
./components/caserver/src/CAServerE.o 

CPP_DEPS += \
./components/caserver/src/CAServerC.d \
./components/caserver/src/CAServerE.d 


# Each subdirectory must supply rules for building sources it contributes
components/caserver/src/%.o: ../components/caserver/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/pedro/workspace/prac6_2_B/components/caclient/include" -I"/home/pedro/workspace/prac6_2_B/components/caserver/include" -I"/home/pedro/workspace/prac6_2_B/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2_B/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2_B/config/include" -I"/home/pedro/workspace/prac6_2_B/edroom_glue/include" -I"/home/pedro/workspace/prac6_2_B/edroombp_swr/include" -I"/home/pedro/workspace/prac6_2_B/edroomsl_swr/include" -I"/home/pedro/workspace/prac6_2_B/edroomsl_types_swr/include" -I"/home/pedro/workspace/prac6_2_B/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


