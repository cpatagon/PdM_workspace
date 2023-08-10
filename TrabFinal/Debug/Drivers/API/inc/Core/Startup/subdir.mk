################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/API/inc/Core/Startup/startup_stm32f429zitx.s 

OBJS += \
./Drivers/API/inc/Core/Startup/startup_stm32f429zitx.o 

S_DEPS += \
./Drivers/API/inc/Core/Startup/startup_stm32f429zitx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/inc/Core/Startup/%.o: ../Drivers/API/inc/Core/Startup/%.s Drivers/API/inc/Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/API/inc" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/API/src" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/API" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/BSP" -I"/home/lgomez/maestriauba/SMT32/TP/Drivers/BSP/STM32F4xx_Nucleo_144" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-API-2f-inc-2f-Core-2f-Startup

clean-Drivers-2f-API-2f-inc-2f-Core-2f-Startup:
	-$(RM) ./Drivers/API/inc/Core/Startup/startup_stm32f429zitx.d ./Drivers/API/inc/Core/Startup/startup_stm32f429zitx.o

.PHONY: clean-Drivers-2f-API-2f-inc-2f-Core-2f-Startup

