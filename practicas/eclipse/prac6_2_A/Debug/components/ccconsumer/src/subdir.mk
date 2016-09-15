################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/ccconsumer/src/CCConsumerC.cpp \
../components/ccconsumer/src/CCConsumerE.cpp 

OBJS += \
./components/ccconsumer/src/CCConsumerC.o \
./components/ccconsumer/src/CCConsumerE.o 

CPP_DEPS += \
./components/ccconsumer/src/CCConsumerC.d \
./components/ccconsumer/src/CCConsumerE.d 


# Each subdirectory must supply rules for building sources it contributes
components/ccconsumer/src/%.o: ../components/ccconsumer/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/user/workspace/edroom_project/components/ccconsumer/include" -I"/home/user/workspace/edroom_project/components/ccproducer/include" -I"/home/user/workspace/edroom_project/config/include" -I"/home/user/workspace/edroom_project/edroom_glue/include" -I"/home/user/workspace/edroom_project/edroombp_swr/include" -I"/home/user/workspace/edroom_project/edroomsl_swr/include" -I"/home/user/workspace/edroom_project/edroomsl_types_swr/include" -I"/home/user/workspace/edroom_project/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


