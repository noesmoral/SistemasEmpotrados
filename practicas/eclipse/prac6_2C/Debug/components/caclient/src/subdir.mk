################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/caclient/src/CAClientC.cpp \
../components/caclient/src/CAClientE.cpp 

OBJS += \
./components/caclient/src/CAClientC.o \
./components/caclient/src/CAClientE.o 

CPP_DEPS += \
./components/caclient/src/CAClientC.d \
./components/caclient/src/CAClientE.d 


# Each subdirectory must supply rules for building sources it contributes
components/caclient/src/%.o: ../components/caclient/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/pedro/workspace/prac6_2/components/caclient/include" -I"/home/pedro/workspace/prac6_2/components/caserver/include" -I"/home/pedro/workspace/prac6_2/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2/config/include" -I"/home/pedro/workspace/prac6_2/edroom_glue/include" -I"/home/pedro/workspace/prac6_2/edroombp_swr/include" -I"/home/pedro/workspace/prac6_2/edroomsl_swr/include" -I"/home/pedro/workspace/prac6_2/edroomsl_types_swr/include" -I"/home/pedro/workspace/prac6_2/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


