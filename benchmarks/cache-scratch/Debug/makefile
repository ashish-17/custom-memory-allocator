################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cache-scratch-Normal cache-scratch-WaitFreePool cache-scratch-Hoard cache-scratch-Streamflow

# Tool invocations
cache-scratch-Normal: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -L../../../allocators/WaitFreeMemAlloc/staticLib/ -o "cache-scratch-Normal" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
cache-scratch-WaitFreePool: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -L../../../allocators/WaitFreeMemAlloc/staticLib/ -o "cache-scratch-WaitFreePool" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

cache-scratch-Hoard: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -o "cache-scratch-Hoard" -Xlinker -rpath=../../../allocators/Hoard/src -L../../../allocators/Hoard/src -lhoard -L../../../allocators/WaitFreeMemAlloc/staticLib/  $(OBJS) $(USER_OBJS) $(LIBS) 
	@echo 'Finished building target: $@'
	@echo ' '

cache-scratch-Streamflow: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -o "cache-scratch-Streamflow" -Xlinker -rpath=../../../allocators/streamflow -L../../../allocators/streamflow -lstreamflow -L../../../allocators/WaitFreeMemAlloc/staticLib/  $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) cache-scratch-Normal cache-scratch-WaitFreePool cache-scratch-Hoard cache-scratch-Streamflow
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
