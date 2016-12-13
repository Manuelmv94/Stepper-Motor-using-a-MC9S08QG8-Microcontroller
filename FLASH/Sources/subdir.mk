################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/LCD_Manager.c" \
"../Sources/MTIM.c" \
"../Sources/MessageManager.c" \
"../Sources/ModeManager.c" \
"../Sources/PowerManager.c" \
"../Sources/SCI.c" \
"../Sources/SPI.c" \
"../Sources/SpeedManager.c" \
"../Sources/StepManager.c" \
"../Sources/StringUtils.c" \
"../Sources/TemperatureManager.c" \
"../Sources/TimersManager.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/LCD_Manager.c \
../Sources/MTIM.c \
../Sources/MessageManager.c \
../Sources/ModeManager.c \
../Sources/PowerManager.c \
../Sources/SCI.c \
../Sources/SPI.c \
../Sources/SpeedManager.c \
../Sources/StepManager.c \
../Sources/StringUtils.c \
../Sources/TemperatureManager.c \
../Sources/TimersManager.c \
../Sources/main.c \

OBJS += \
./Sources/ADC_c.obj \
./Sources/LCD_Manager_c.obj \
./Sources/MTIM_c.obj \
./Sources/MessageManager_c.obj \
./Sources/ModeManager_c.obj \
./Sources/PowerManager_c.obj \
./Sources/SCI_c.obj \
./Sources/SPI_c.obj \
./Sources/SpeedManager_c.obj \
./Sources/StepManager_c.obj \
./Sources/StringUtils_c.obj \
./Sources/TemperatureManager_c.obj \
./Sources/TimersManager_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/ADC_c.obj" \
"./Sources/LCD_Manager_c.obj" \
"./Sources/MTIM_c.obj" \
"./Sources/MessageManager_c.obj" \
"./Sources/ModeManager_c.obj" \
"./Sources/PowerManager_c.obj" \
"./Sources/SCI_c.obj" \
"./Sources/SPI_c.obj" \
"./Sources/SpeedManager_c.obj" \
"./Sources/StepManager_c.obj" \
"./Sources/StringUtils_c.obj" \
"./Sources/TemperatureManager_c.obj" \
"./Sources/TimersManager_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/ADC_c.d \
./Sources/LCD_Manager_c.d \
./Sources/MTIM_c.d \
./Sources/MessageManager_c.d \
./Sources/ModeManager_c.d \
./Sources/PowerManager_c.d \
./Sources/SCI_c.d \
./Sources/SPI_c.d \
./Sources/SpeedManager_c.d \
./Sources/StepManager_c.d \
./Sources/StringUtils_c.d \
./Sources/TemperatureManager_c.d \
./Sources/TimersManager_c.d \
./Sources/main_c.d \

C_DEPS_QUOTED += \
"./Sources/ADC_c.d" \
"./Sources/LCD_Manager_c.d" \
"./Sources/MTIM_c.d" \
"./Sources/MessageManager_c.d" \
"./Sources/ModeManager_c.d" \
"./Sources/PowerManager_c.d" \
"./Sources/SCI_c.d" \
"./Sources/SPI_c.d" \
"./Sources/SpeedManager_c.d" \
"./Sources/StepManager_c.d" \
"./Sources/StringUtils_c.d" \
"./Sources/TemperatureManager_c.d" \
"./Sources/TimersManager_c.d" \
"./Sources/main_c.d" \

OBJS_OS_FORMAT += \
./Sources/ADC_c.obj \
./Sources/LCD_Manager_c.obj \
./Sources/MTIM_c.obj \
./Sources/MessageManager_c.obj \
./Sources/ModeManager_c.obj \
./Sources/PowerManager_c.obj \
./Sources/SCI_c.obj \
./Sources/SPI_c.obj \
./Sources/SpeedManager_c.obj \
./Sources/StepManager_c.obj \
./Sources/StringUtils_c.obj \
./Sources/TemperatureManager_c.obj \
./Sources/TimersManager_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC_c.obj: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/ADC.args" -ObjN="Sources/ADC_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/LCD_Manager_c.obj: ../Sources/LCD_Manager.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/LCD_Manager.args" -ObjN="Sources/LCD_Manager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/MTIM_c.obj: ../Sources/MTIM.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MTIM.args" -ObjN="Sources/MTIM_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/MessageManager_c.obj: ../Sources/MessageManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MessageManager.args" -ObjN="Sources/MessageManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/ModeManager_c.obj: ../Sources/ModeManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/ModeManager.args" -ObjN="Sources/ModeManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/PowerManager_c.obj: ../Sources/PowerManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/PowerManager.args" -ObjN="Sources/PowerManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SCI_c.obj: ../Sources/SCI.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SCI.args" -ObjN="Sources/SCI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SPI_c.obj: ../Sources/SPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SPI.args" -ObjN="Sources/SPI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SpeedManager_c.obj: ../Sources/SpeedManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SpeedManager.args" -ObjN="Sources/SpeedManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/StepManager_c.obj: ../Sources/StepManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/StepManager.args" -ObjN="Sources/StepManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/StringUtils_c.obj: ../Sources/StringUtils.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/StringUtils.args" -ObjN="Sources/StringUtils_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TemperatureManager_c.obj: ../Sources/TemperatureManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TemperatureManager.args" -ObjN="Sources/TemperatureManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TimersManager_c.obj: ../Sources/TimersManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TimersManager.args" -ObjN="Sources/TimersManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


