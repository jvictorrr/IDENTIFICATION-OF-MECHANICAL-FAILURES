################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/ST/Middlewares/ST/STM32_MotionSP_Library/Src/MotionSP.c 

OBJS += \
./Middlewares/STM32_MotionSP_Library/MotionSP.o 

C_DEPS += \
./Middlewares/STM32_MotionSP_Library/MotionSP.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_MotionSP_Library/MotionSP.o: C:/ST/Middlewares/ST/STM32_MotionSP_Library/Src/MotionSP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/STM32_MotionSP_Library/MotionSP.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

