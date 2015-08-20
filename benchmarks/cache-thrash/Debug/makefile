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
all: cache-thrash-Normal cache-thrash-WaitFreePool cache-thrash-Hoard cache-thrash-Streamflow

# Tool invocations
cache-thrash-Normal: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -L../../../allocators/WaitFreeMemAlloc/staticLib/ -o "cache-thrash-Normal" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
cache-thrash-WaitFreePool: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -L../../../allocators/WaitFreeMemAlloc/staticLib/ -o "cache-thrash-WaitFreePool" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

cache-thrash-Hoard: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -o "cache-thrash-Hoard" -Xlinker -rpath=../../../allocators/Hoard/src -L../../../allocators/Hoard/src -lhoard -L../../../allocators/WaitFreeMemAlloc/staticLib/  $(OBJS) $(USER_OBJS) $(LIBS) 
	@echo 'Finished building target: $@'
	@echo ' '

cache-thrash-Streamflow: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -o "cache-thrash-Streamflow" -Xlinker -rpath=../../../allocators/streamflow -L../../../allocators/streamflow -lstreamflow -L../../../allocators/WaitFreeMemAlloc/staticLib/  $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) cache-thrash-Normal cache-thrash-WaitFreePool cache-thrash-Hoard cache-thrash-Streamflow
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
