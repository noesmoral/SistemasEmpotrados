################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/exampl1/src/Exampl1C.cpp \
../components/exampl1/src/Exampl1E.cpp 

OBJS += \
./components/exampl1/src/Exampl1C.o \
./components/exampl1/src/Exampl1E.o 

CPP_DEPS += \
./components/exampl1/src/Exampl1C.d \
./components/exampl1/src/Exampl1E.d 


# Each subdirectory must supply rules for building sources it contributes
components/exampl1/src/%.o: ../components/exampl1/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/user/workspace/edroom_project/components/ccconsumer/include" -I"/home/user/workspace/edroom_project/components/ccproducer/include" -I"/home/user/workspace/edroom_project/config/include" -I"/home/user/workspace/edroom_project/edroom_glue/include" -I"/home/user/workspace/edroom_project/edroombp_swr/include" -I"/home/user/workspace/edroom_project/edroomsl_swr/include" -I"/home/user/workspace/edroom_project/edroomsl_types_swr/include" -I"/home/user/workspace/edroom_project/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


