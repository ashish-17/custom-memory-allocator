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
all: thread-test-Normal thread-test-WaitFreePool thread-test-Hoard thread-test-Streamflow

thread-test-Normal: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -L../../../allocators/WaitFreeMemAlloc/staticLib/ -o "thread-test-Normal" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

thread-test-WaitFreePool: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -L../../../allocators/WaitFreeMemAlloc/staticLib/ -o "thread-test-WaitFreePool" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

thread-test-Hoard: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -o "thread-test-Hoard" -Xlinker -rpath=../../../allocators/Hoard/src -L../../../allocators/Hoard/src -lhoard -L../../../allocators/WaitFreeMemAlloc/staticLib/  $(OBJS) $(USER_OBJS) $(LIBS) 
	@echo 'Finished building target: $@'
	@echo ' '

thread-test-Streamflow: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	g++ -o "thread-test-Streamflow" -Xlinker -rpath=../../../allocators/streamflow -L../../../allocators/streamflow -lstreamflow -L../../../allocators/WaitFreeMemAlloc/staticLib/  $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) thread-test-Normal thread-test-WaitFreePool thread-test-Hoard thread-test-Streamflow
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
