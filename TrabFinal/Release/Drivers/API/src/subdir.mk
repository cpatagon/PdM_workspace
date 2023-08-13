################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/API_debounce.c \
../Drivers/API/src/API_delay.c \
../Drivers/API/src/API_led.c \
../Drivers/API/src/API_spi.c \
../Drivers/API/src/App_MEF.c 

OBJS += \
./Drivers/API/src/API_debounce.o \
./Drivers/API/src/API_delay.o \
./Drivers/API/src/API_led.o \
./Drivers/API/src/API_spi.o \
./Drivers/API/src/App_MEF.o 

C_DEPS += \
./Drivers/API/src/API_debounce.d \
./Drivers/API/src/API_delay.d \
./Drivers/API/src/API_led.d \
./Drivers/API/src/API_spi.d \
./Drivers/API/src/App_MEF.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o Drivers/API/src/%.su Drivers/API/src/%.cyclo: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/lgomez/maestriauba/SMT32/PdM_workspace/TrabFinal/Core/Src" -I"/home/lgomez/maestriauba/SMT32/PdM_workspace/TrabFinal/Drivers/API/inc" -I"/home/lgomez/maestriauba/SMT32/PdM_workspace/TrabFinal/Drivers/API/src" -I"/home/lgomez/maestriauba/SMT32/PdM_workspace/TrabFinal/Drivers/API" -I"/home/lgomez/maestriauba/SMT32/PdM_workspace/TrabFinal/Drivers/BSP" -I"/home/lgomez/maestriauba/SMT32/PdM_workspace/TrabFinal/Drivers/BSP/STM32F4xx_Nucleo_144" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-src

clean-Drivers-2f-API-2f-src:
	-$(RM) ./Drivers/API/src/API_debounce.cyclo ./Drivers/API/src/API_debounce.d ./Drivers/API/src/API_debounce.o ./Drivers/API/src/API_debounce.su ./Drivers/API/src/API_delay.cyclo ./Drivers/API/src/API_delay.d ./Drivers/API/src/API_delay.o ./Drivers/API/src/API_delay.su ./Drivers/API/src/API_led.cyclo ./Drivers/API/src/API_led.d ./Drivers/API/src/API_led.o ./Drivers/API/src/API_led.su ./Drivers/API/src/API_spi.cyclo ./Drivers/API/src/API_spi.d ./Drivers/API/src/API_spi.o ./Drivers/API/src/API_spi.su ./Drivers/API/src/App_MEF.cyclo ./Drivers/API/src/App_MEF.d ./Drivers/API/src/App_MEF.o ./Drivers/API/src/App_MEF.su

.PHONY: clean-Drivers-2f-API-2f-src

