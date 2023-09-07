/*
 * DC_Motor.c
 *
 *  Created on: Sep 2, 2023
 *      Author: Mostafa Hisham
 *      Layer : HAL
 *      SWC   : DC- MOTOR - IMPLEMENTATION
 */
#include<Std_Types.h>
#include<Macros.h>
#include<Registers.h>
#include<DIO.h>
#include<DC_Motor.h>
#include<DC_Motor_cfg.h>

/*H-Bridge Connection */

static void DC_Motor_Init(void);
static void DC_Motor_Init(void)
{
	DIO_SetPinDirection(MOTOR_PORT,MOTOR1_PIN1,PIN_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT,MOTOR1_PIN2,PIN_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT,MOTOR2_PIN1,PIN_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT,MOTOR2_PIN2,PIN_OUTPUT);
}
void DCMOTOR_RotateCounterClockWise(Motor_Number motor)
{
	DC_Motor_Init();
	switch (motor)
	{
	case 0:
	DIO_SetPinLevel(MOTOR_PORT,MOTOR1_PIN1,PIN_HIGH);
	DIO_SetPinLevel(MOTOR_PORT,MOTOR1_PIN2,PIN_LOW);
	break;
	case 1:
	DIO_SetPinLevel(MOTOR_PORT,MOTOR2_PIN1,PIN_HIGH);
	DIO_SetPinLevel(MOTOR_PORT,MOTOR2_PIN2,PIN_LOW);
	break;
	default:
		break;
	}
}
void DCMOTOR_RotateClockwise(Motor_Number motor)
{
	DC_Motor_Init();
	switch (motor)
	{
	case 0:
	DIO_SetPinLevel(MOTOR_PORT,MOTOR1_PIN1,PIN_LOW);
	DIO_SetPinLevel(MOTOR_PORT,MOTOR1_PIN2,PIN_HIGH);
	break;
	case 1:
	DIO_SetPinLevel(MOTOR_PORT,MOTOR2_PIN1,PIN_LOW);
	DIO_SetPinLevel(MOTOR_PORT,MOTOR2_PIN2,PIN_HIGH);
	break;
	default:
		break;
	}
}
void DCMOTOR_Stop(Motor_Number motor)
{
	DC_Motor_Init();
	switch(motor)
	{
	case 0:
	DIO_SetPinLevel(MOTOR_PORT,MOTOR1_PIN1,PIN_LOW);
	DIO_SetPinLevel(MOTOR_PORT,MOTOR1_PIN2,PIN_LOW);
	break;
	case 1:
	DIO_SetPinLevel(MOTOR_PORT,MOTOR2_PIN1,PIN_LOW);
	DIO_SetPinLevel(MOTOR_PORT,MOTOR2_PIN2,PIN_LOW);
	break;
	default:
		break;
	}
}
