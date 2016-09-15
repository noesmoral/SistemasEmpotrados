################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/example2/src/Example2C.cpp \
../components/example2/src/Example2E.cpp 

OBJS += \
./components/example2/src/Example2C.o \
./components/example2/src/Example2E.o 

CPP_DEPS += \
./components/example2/src/Example2C.d \
./components/example2/src/Example2E.d 


# Each subdirectory must supply rules for building sources it contributes
components/example2/src/%.o: ../components/example2/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/user/workspace/edroom_example2/components/ccserver/include" -I"/home/user/workspace/edroom_example2/components/ccclient/include" -I"/home/user/workspace/edroom_example2/components/example2/include" -I"/home/user/workspace/edroom_example2/config/include" -I"/home/user/workspace/edroom_example2/edroom_glue/include" -I"/home/user/workspace/edroom_example2/edroombp_swr/include" -I"/home/user/workspace/edroom_example2/edroomsl_swr/include" -I"/home/user/workspace/edroom_example2/edroomsl_types_swr/include" -I"/home/user/workspace/edroom_example2/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


