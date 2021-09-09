################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/test_workspace/Vibration_Analysis/Patch/ism330dlc_Patch.c 

OBJS += \
./VibrationAnalysis/User/Patch/ism330dlc_Patch.o 

C_DEPS += \
./VibrationAnalysis/User/Patch/ism330dlc_Patch.d 


# Each subdirectory must supply rules for building sources it contributes
VibrationAnalysis/User/Patch/ism330dlc_Patch.o: C:/ST/STM32CubeIDE_1.3.0/STM32CubeIDE/test_workspace/Vibration_Analysis/Patch/ism330dlc_Patch.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"VibrationAnalysis/User/Patch/ism330dlc_Patch.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

