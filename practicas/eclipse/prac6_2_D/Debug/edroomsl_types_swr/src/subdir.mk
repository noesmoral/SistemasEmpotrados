################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../edroomsl_types_swr/src/edroomsl_types.cpp 

OBJS += \
./edroomsl_types_swr/src/edroomsl_types.o 

CPP_DEPS += \
./edroomsl_types_swr/src/edroomsl_types.d 


# Each subdirectory must supply rules for building sources it contributes
edroomsl_types_swr/src/%.o: ../edroomsl_types_swr/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/pedro/workspace/prac6_2_D/components/caclient/include" -I"/home/pedro/workspace/prac6_2_D/components/caserver/include" -I"/home/pedro/workspace/prac6_2_D/components/casuperserver/include" -I"/home/pedro/workspace/prac6_2_D/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2_D/components/prac6_2/include" -I"/home/pedro/workspace/prac6_2_D/config/include" -I"/home/pedro/workspace/prac6_2_D/edroom_glue/include" -I"/home/pedro/workspace/prac6_2_D/edroombp_swr/include" -I"/home/pedro/workspace/prac6_2_D/edroomsl_swr/include" -I"/home/pedro/workspace/prac6_2_D/edroomsl_types_swr/include" -I"/home/pedro/workspace/prac6_2_D/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


