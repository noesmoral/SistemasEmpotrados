################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/ccproducer/src/CCProducerC.cpp \
../components/ccproducer/src/CCProducerE.cpp 

OBJS += \
./components/ccproducer/src/CCProducerC.o \
./components/ccproducer/src/CCProducerE.o 

CPP_DEPS += \
./components/ccproducer/src/CCProducerC.d \
./components/ccproducer/src/CCProducerE.d 


# Each subdirectory must supply rules for building sources it contributes
components/ccproducer/src/%.o: ../components/ccproducer/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/user/workspace/edroom_project/components/ccconsumer/include" -I"/home/user/workspace/edroom_project/components/ccproducer/include" -I"/home/user/workspace/edroom_project/config/include" -I"/home/user/workspace/edroom_project/edroom_glue/include" -I"/home/user/workspace/edroom_project/edroombp_swr/include" -I"/home/user/workspace/edroom_project/edroomsl_swr/include" -I"/home/user/workspace/edroom_project/edroomsl_types_swr/include" -I"/home/user/workspace/edroom_project/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


