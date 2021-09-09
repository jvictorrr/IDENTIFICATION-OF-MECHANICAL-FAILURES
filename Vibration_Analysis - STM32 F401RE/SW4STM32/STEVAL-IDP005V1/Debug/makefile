################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include VibrationAnalysis/User/Patch/subdir.mk
-include VibrationAnalysis/User/subdir.mk
-include VibrationAnalysis/SW4STM32/subdir.mk
-include Middlewares/STM32_MotionSP_Library/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STEVAL-IDP005V1/subdir.mk
-include Drivers/BSP/Components/lps22hb/subdir.mk
-include Drivers/BSP/Components/ism330dlc/subdir.mk
-include Drivers/BSP/Components/hts221/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STEVAL-IDP005V1_VibrationAnalysis.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STEVAL-IDP005V1_VibrationAnalysis.list \

OBJCOPY_BIN += \
STEVAL-IDP005V1_VibrationAnalysis.bin \


# All Target
all:
	+@make --no-print-directory main-build && make --no-print-directory post-build

# Main-build Target
main-build: STEVAL-IDP005V1_VibrationAnalysis.elf secondary-outputs

# Tool invocations
STEVAL-IDP005V1_VibrationAnalysis.elf: $(OBJS) $(USER_OBJS) ../STM32F469AIYx_FLASH.ld
	arm-none-eabi-gcc -o "STEVAL-IDP005V1_VibrationAnalysis.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../STM32F469AIYx_FLASH.ld" --specs=nosys.specs -Wl,-Map="STEVAL-IDP005V1_VibAna.map" -Wl,--gc-sections -static -L../../../../../../../Drivers/CMSIS/Lib/GCC --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STEVAL-IDP005V1_VibrationAnalysis.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STEVAL-IDP005V1_VibrationAnalysis.list"
	@echo 'Finished building: $@'
	@echo ' '

STEVAL-IDP005V1_VibrationAnalysis.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STEVAL-IDP005V1_VibrationAnalysis.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O binary "STEVAL-IDP005V1_VibrationAnalysis.elf" "../../../Binary/STEVAL-IDP005V1_VibrationAnalysis.bin"
	arm-none-eabi-size "STEVAL-IDP005V1_VibrationAnalysis.elf"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
