################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 16
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Lib/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
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
EXECUTABLES += \
Stepper_Serial_Interfacev2.abs \

EXECUTABLES_QUOTED += \
"Stepper_Serial_Interfacev2.abs" \

EXECUTABLES_OS_FORMAT += \
Stepper_Serial_Interfacev2.abs \

BURNER_OUTPUT_OUTPUTS += \
Stepper_Serial_Interfacev2.abs.s19 \

BURNER_OUTPUT_OUTPUTS_QUOTED += \
"Stepper_Serial_Interfacev2.abs.s19" \

BURNER_OUTPUT_OUTPUTS_OS_FORMAT += \
Stepper_Serial_Interfacev2.abs.s19 \


# All Target
call-burner := 0
ifneq ($(strip $(EXECUTABLES)),)
ifneq ($(strip $(BBL_SRCS_QUOTED)),)
call-burner := 1
endif
endif
ifeq ($(call-burner),1)
all: Stepper_Serial_Interfacev2.abs Stepper_Serial_Interfacev2.abs.s19
else
all: Stepper_Serial_Interfacev2.abs
endif

# Tool invocations
Stepper_Serial_Interfacev2.abs: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/Project.prm
	@echo 'Building target: $@'
	@echo 'Executing target #17 $@'
	@echo 'Invoking: S08 Linker'
	"$(HC08ToolsEnv)/linker" -ArgFile"Stepper_Serial_Interfacev2.args" -O"Stepper_Serial_Interfacev2.abs"
	@echo 'Finished building target: $@'
	@echo ' '

Stepper_Serial_Interfacev2.abs.s19: $(BBL_SRCS) $(EXECUTABLES)
	@echo 'Executing target #18 $@'
	@echo 'Invoking: S08 Burner'
	"$(HC08ToolsEnv)/burner" -ArgFile"Stepper_Serial_Interfacev2.abs.args" -f="$<" -env"ABS_FILE=$(strip $(EXECUTABLES_OS_FORMAT))"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*.obj" "./*/*/*.obj"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(BURNER_OUTPUT_OUTPUTS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d"  $(ProjDirPath)/FLASH/Stepper_Serial_Interfacev2.abs $(ProjDirPath)/FLASH/Stepper_Serial_Interfacev2.abs.args $(ProjDirPath)/FLASH/Stepper_Serial_Interfacev2.abs.s19 $(ProjDirPath)/FLASH/Stepper_Serial_Interfacev2.args $(ProjDirPath)/FLASH/Stepper_Serial_Interfacev2.map
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/Project.prm 

warning-messages: 

