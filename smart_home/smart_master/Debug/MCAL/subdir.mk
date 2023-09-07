################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DIO.c \
../MCAL/GIE.c \
../MCAL/SPI.c \
../MCAL/TIMER.c 

OBJS += \
./MCAL/DIO.o \
./MCAL/GIE.o \
./MCAL/SPI.o \
./MCAL/TIMER.o 

C_DEPS += \
./MCAL/DIO.d \
./MCAL/GIE.d \
./MCAL/SPI.d \
./MCAL/TIMER.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\embedded_tasks\smart_master\APP" -I"E:\embedded_tasks\smart_master\HAL" -I"E:\embedded_tasks\smart_master\LIB" -I"E:\embedded_tasks\smart_master\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


