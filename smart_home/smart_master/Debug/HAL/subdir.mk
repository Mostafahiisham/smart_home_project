################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad.c \
../HAL/LCD.c 

OBJS += \
./HAL/KeyPad.o \
./HAL/LCD.o 

C_DEPS += \
./HAL/KeyPad.d \
./HAL/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\embedded_tasks\smart_master\APP" -I"E:\embedded_tasks\smart_master\HAL" -I"E:\embedded_tasks\smart_master\LIB" -I"E:\embedded_tasks\smart_master\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


