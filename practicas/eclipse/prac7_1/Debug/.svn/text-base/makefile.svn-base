################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include sensors_drv/src/subdir.mk
-include random_swr/src/subdir.mk
-include planner_swr/src/subdir.mk
-include edroomsl_types_swr/src/subdir.mk
-include edroomsl_swr/src/subdir.mk
-include edroombp_swr/src/rtemsapi_4_6/rtems_4_6/subdir.mk
-include edroom_glue/src/subdir.mk
-include components/vehicle/src/subdir.mk
-include components/capathtracker/src/subdir.mk
-include components/capathplanner/src/subdir.mk
-include components/caavoidobstacles/src/subdir.mk
-include bprint_swr/src/subdir.mk
-include actuators_drv/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: prac7_1

# Tool invocations
prac7_1: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: SPARC RTEMS C++ Linker'
	sparc-rtems-g++ -msoft-float -o "prac7_1" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(S_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) prac7_1
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
