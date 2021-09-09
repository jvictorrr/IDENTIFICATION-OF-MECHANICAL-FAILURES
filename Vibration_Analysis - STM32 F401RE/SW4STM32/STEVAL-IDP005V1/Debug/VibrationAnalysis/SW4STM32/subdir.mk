################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/test_workspace/Vibration_Analysis/SW4STM32/startup_stm32f469xx.s 

C_SRCS += \
C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/test_workspace/Vibration_Analysis/SW4STM32/syscalls.c 

OBJS += \
./VibrationAnalysis/SW4STM32/startup_stm32f469xx.o \
./VibrationAnalysis/SW4STM32/syscalls.o 

C_DEPS += \
./VibrationAnalysis/SW4STM32/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
VibrationAnalysis/SW4STM32/startup_stm32f469xx.o: C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/test_workspace/Vibration_Analysis/SW4STM32/startup_stm32f469xx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
VibrationAnalysis/SW4STM32/syscalls.o: C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/test_workspace/Vibration_Analysis/SW4STM32/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"VibrationAnalysis/SW4STM32/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

