################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/inc/Core/Src/main.c \
../Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.c \
../Drivers/API/inc/Core/Src/stm32f4xx_it.c \
../Drivers/API/inc/Core/Src/syscalls.c \
../Drivers/API/inc/Core/Src/sysmem.c \
../Drivers/API/inc/Core/Src/system_stm32f4xx.c 

OBJS += \
./Drivers/API/inc/Core/Src/main.o \
./Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.o \
./Drivers/API/inc/Core/Src/stm32f4xx_it.o \
./Drivers/API/inc/Core/Src/syscalls.o \
./Drivers/API/inc/Core/Src/sysmem.o \
./Drivers/API/inc/Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Drivers/API/inc/Core/Src/main.d \
./Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.d \
./Drivers/API/inc/Core/Src/stm32f4xx_it.d \
./Drivers/API/inc/Core/Src/syscalls.d \
./Drivers/API/inc/Core/Src/sysmem.d \
./Drivers/API/inc/Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/inc/Core/Src/%.o Drivers/API/inc/Core/Src/%.su Drivers/API/inc/Core/Src/%.cyclo: ../Drivers/API/inc/Core/Src/%.c Drivers/API/inc/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/API/inc" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/API/src" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/API" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/BSP" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/BSP/STM32F4xx_Nucleo_144" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-inc-2f-Core-2f-Src

clean-Drivers-2f-API-2f-inc-2f-Core-2f-Src:
	-$(RM) ./Drivers/API/inc/Core/Src/main.cyclo ./Drivers/API/inc/Core/Src/main.d ./Drivers/API/inc/Core/Src/main.o ./Drivers/API/inc/Core/Src/main.su ./Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.cyclo ./Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.d ./Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.o ./Drivers/API/inc/Core/Src/stm32f4xx_hal_msp.su ./Drivers/API/inc/Core/Src/stm32f4xx_it.cyclo ./Drivers/API/inc/Core/Src/stm32f4xx_it.d ./Drivers/API/inc/Core/Src/stm32f4xx_it.o ./Drivers/API/inc/Core/Src/stm32f4xx_it.su ./Drivers/API/inc/Core/Src/syscalls.cyclo ./Drivers/API/inc/Core/Src/syscalls.d ./Drivers/API/inc/Core/Src/syscalls.o ./Drivers/API/inc/Core/Src/syscalls.su ./Drivers/API/inc/Core/Src/sysmem.cyclo ./Drivers/API/inc/Core/Src/sysmem.d ./Drivers/API/inc/Core/Src/sysmem.o ./Drivers/API/inc/Core/Src/sysmem.su ./Drivers/API/inc/Core/Src/system_stm32f4xx.cyclo ./Drivers/API/inc/Core/Src/system_stm32f4xx.d ./Drivers/API/inc/Core/Src/system_stm32f4xx.o ./Drivers/API/inc/Core/Src/system_stm32f4xx.su

.PHONY: clean-Drivers-2f-API-2f-inc-2f-Core-2f-Src

