################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../edroomsl_swr/src/edroomsl.cpp \
../edroomsl_swr/src/edroomtc.cpp 

OBJS += \
./edroomsl_swr/src/edroomsl.o \
./edroomsl_swr/src/edroomtc.o 

CPP_DEPS += \
./edroomsl_swr/src/edroomsl.d \
./edroomsl_swr/src/edroomtc.d 


# Each subdirectory must supply rules for building sources it contributes
edroomsl_swr/src/%.o: ../edroomsl_swr/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I"/home/pedro/workspace/prac7_1/components/caavoidobstacles/include" -I"/home/pedro/workspace/prac7_1/bprint_swr/include" -I"/home/pedro/workspace/prac7_1/dataclasses/CDLocation/include" -I"/home/pedro/workspace/prac7_1/dataclasses/CDPath/include" -I"/home/pedro/workspace/prac7_1/actuators_drv/include" -I"/home/pedro/workspace/prac7_1/components/capathplanner/include" -I"/home/pedro/workspace/prac7_1/components/vehicle/include" -I"/home/pedro/workspace/prac7_1/planner_swr/include" -I"/home/pedro/workspace/prac7_1/random_swr/include" -I"/home/pedro/workspace/prac7_1/components/capathtracker/include" -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/pedro/workspace/prac7_1/config/include" -I"/home/pedro/workspace/prac7_1/sensors_drv/include" -I"/home/pedro/workspace/prac7_1/edroom_glue/include" -I"/home/pedro/workspace/prac7_1/edroombp_swr/include" -I"/home/pedro/workspace/prac7_1/edroomsl_swr/include" -I"/home/pedro/workspace/prac7_1/edroomsl_types_swr/include" -I"/home/pedro/workspace/prac7_1/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


