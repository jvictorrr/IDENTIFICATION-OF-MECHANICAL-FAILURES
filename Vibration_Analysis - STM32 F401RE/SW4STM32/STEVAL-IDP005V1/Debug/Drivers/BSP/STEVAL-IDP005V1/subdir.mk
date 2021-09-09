################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/ST/Drivers/BSP/STEVAL-IDP005/idp005.c \
C:/ST/Drivers/BSP/STEVAL-IDP005/idp005_flash.c \
C:/ST/Drivers/BSP/STEVAL-IDP005/idp005_motion_sensors.c \
C:/ST/Drivers/BSP/STEVAL-IDP005/idp005_motion_sensors_ex.c 

OBJS += \
./Drivers/BSP/STEVAL-IDP005V1/idp005.o \
./Drivers/BSP/STEVAL-IDP005V1/idp005_flash.o \
./Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors.o \
./Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors_ex.o 

C_DEPS += \
./Drivers/BSP/STEVAL-IDP005V1/idp005.d \
./Drivers/BSP/STEVAL-IDP005V1/idp005_flash.d \
./Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors.d \
./Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STEVAL-IDP005V1/idp005.o: C:/ST/Drivers/BSP/STEVAL-IDP005/idp005.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STEVAL-IDP005V1/idp005.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STEVAL-IDP005V1/idp005_flash.o: C:/ST/Drivers/BSP/STEVAL-IDP005/idp005_flash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STEVAL-IDP005V1/idp005_flash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors.o: C:/ST/Drivers/BSP/STEVAL-IDP005/idp005_motion_sensors.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors_ex.o: C:/ST/Drivers/BSP/STEVAL-IDP005/idp005_motion_sensors_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DARM_MATH_CM4 -c -I../../../Inc -I../../../Patch -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../Drivers/BSP/STEVAL-IDP005 -I../../../../../../../Middlewares/ST/STM32_MotionSP_Library/Inc -I../../../../../../../Drivers/BSP/Components/ism330dlc -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STEVAL-IDP005V1/idp005_motion_sensors_ex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

