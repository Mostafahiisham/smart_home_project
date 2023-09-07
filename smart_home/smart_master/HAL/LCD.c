/*
 * LCD.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Mostafa Hisham
 *      Layer : HAL
 *      SWC   : LCD - IMPLEMENTATION
 */
#include<Std_Types.h>
#include<Macros.h>
#include<DIO.h>
#include<LCD.h>
#include<util/delay.h>

static void LCD_InitPort(void);
static void LCD_SendCommand(u8 Command);
static void LCD_SendData(u8 Data);

//1
static void LCD_InitPort(void)
{
	/*data pins all are output*/
	DIO_SetPortDirection(DATA_PORT,PORT_MODE_OUTPUT);
	DIO_SetPinDirection(CTRL_PORT,CTRL_RS,PIN_OUTPUT);
	DIO_SetPinDirection(CTRL_PORT,CTRL_RW,PIN_OUTPUT);
	DIO_SetPinDirection(CTRL_PORT,CTRL_E,PIN_OUTPUT);

}
//2
static void LCD_SendCommand(u8 Command)
{
	//SET RS(REGISTER SELECT) PIN lOW TO SEND COMMAND
	 DIO_SetPinLevel(CTRL_PORT,CTRL_RS,PIN_LOW);
	//SET RW (READ | WRITE)PIN LOW TO SEND WRITE COMMAND
	DIO_SetPinLevel(CTRL_PORT,CTRL_RW,PIN_LOW);
	//SET COMMAND TO DATA PINS
	DIO_SetPortLevel(DATA_PORT,Command);
	//SET E (ENABLE PULSE) TO SEND COMMAND
	DIO_SetPinLevel(CTRL_PORT,CTRL_E,PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinLevel(CTRL_PORT,CTRL_E,PIN_LOW);
}
//3
static void LCD_SendData(u8 Data)
{
	//SET RS(REGISTER SELECT) PIN lOW TO SEND DATA
	 DIO_SetPinLevel(CTRL_PORT,CTRL_RS,PIN_HIGH);
		//SET RW (READ WRITE)PIN LOW TO SEND WRITE COMMAND
		DIO_SetPinLevel(CTRL_PORT,CTRL_RW,PIN_LOW);
		//SET COMMAND TO DATA PINS
		DIO_SetPortLevel(DATA_PORT,Data);
		//SET E (ENABLE PULSE) TO SEND COMMAND
		DIO_SetPinLevel(CTRL_PORT,CTRL_E,PIN_HIGH);
		_delay_ms(2);
		DIO_SetPinLevel(CTRL_PORT,CTRL_E,PIN_LOW);
}

//LOOK DATASHEET PAGE (13)
//4
void LCD_Init(void)
{
	LCD_InitPort();
	/*WAIT FOR MORETHAN 30ms*/
	_delay_ms(30);

	// CONTROL LCD DISPLAY
	LCD_ControlDisplay display = {
		LCD_DISPLAY_MODE,
    	LCD_CURSOR_MODE,
		LCD_LINES_NUMBER,
		LCD_FONT_MODE};
	LCD_DisplayStatus(display);
	LCD_DisplayClear();
}
//5
void LCD_DisplayStatus(LCD_ControlDisplay display)
{
	//we have to set in this the DDRAM AND CGRAM address first
	//             76543210
	u8 Command = 0b00110000;

	//TO SET THE FONT IN TO 5X10 TYPE
	if(display.Font_status == FONT_SIZE_5X10)
	{
	SET_BIT(Command,2);
	}
	//TO SET THE LINE IN TOTWO LINES
	if(display.Line_status == LCD_TWO_LINES)
	{
	SET_BIT(Command,3);
	}
	LCD_SendCommand(Command);
	//SET THE DISPLAY MODE
	if  (display.Display_status == LCD_DISPLAY_OFF)
		{
		LCD_SendCommand(0b00001000);
		}
	else if (display.Display_status == LCD_DISPLAY_ON)
	{

	//SWITCH ON THE CURSOR MODE
		switch( display.Cursor_status )
		{
	case  LCD_CURSOR_OFF :

	LCD_SendCommand(0b00001100);

	break;
	case LCD_CURSOR_ON_BLINK :
	LCD_SendCommand(0b00001111);
	break;
	case LCD_CURSOR_ON_NOT_BLINK :
	LCD_SendCommand(0b00001110);
	break;

	default:
	break;
		}
	}
}

// TO CLEAR DISPLAY SCREEN
void LCD_DisplayClear()
{
	LCD_SendCommand(1);
}

// TO RETURN THE DISPLAY TO IT'S ORIGINAL POSITION ALSO THE SHIFTED DISPLAY
void LCD_DisplayReturnHome()
{
	LCD_SendCommand(2);
}

// A FUNCTION TO DISPLAY A SINGLE CHARACTER
void LCD_SendCharacter( u8 character)
{
	LCD_SendData(character);
}

// A FUNCTION TO DISPLAY A STRING
void LCD_SendString(const u8* Send_String)
{
	u8 i;
	/*ARRAY OF CHARACTER*/
	while( Send_String[i] != '\0')
	{
		LCD_SendData(*Send_String);
		Send_String++;
	}
}
							/******** A FUNCTION TO SHIFT THE CURSOR RIGHT ********/
void LCD_ShiftCursorRight(u8 counter)
{
	for(u8 i = 0 ; i < counter ; i++  )
	LCD_SendCommand(0b00010100);
}

														/******** A FUNCTION TO SHIFT THE CURSOR LEFT ********/
void LCD_ShiftCursorLeft(u8 counter)
{
	for(u8 i = 0 ; i < counter ; i++  )
	LCD_SendCommand(0b00010000);
}

														/******** A FUNCTION TO SHIFT THE DISPLAY RIGHT ********/
void LCD_ShiftDisplayRight(u8 counter)
{
	for(u8 i = 0 ; i < counter ; i++  )
	LCD_SendCommand(0b00011100);
}
//13
														/******** A FUNCTION TO SHIFT THE DISPLAY LEFT ********/
void LCD_ShiftDisplayLeft(u8 counter)
{
	for(u8 i = 0 ; i < counter ; i++  )
	LCD_SendCommand(0b00011000);
}

void LCD_SaveCustomCharacter(u8 CGRAM_Index,u8* Custom)
{
	//set the CGram to the address counter to read /write data then give address
	LCD_SendCommand(0b01000000+(CGRAM_Index*8));
	for(u8 index = 0 ; index < 8; index ++)
	{
		//SEND DATA to the CG ram
		LCD_SendData(Custom[index]);
	}
	//set the DDram to the address counter to take the data
	LCD_SendCommand(0x80);
}
void LCD_DisplayCustomCharacter(u8 CGRAM_Index)
{
	if(CGRAM_Index < 8)
	{
		LCD_SendData(CGRAM_Index);
	}
}
void LCD_DisplayNumber(s64 s_number)
{
	u64 u_number = 1;
	if(s_number == 0 )
	{
		LCD_SendData('0');
	}
	if(s_number < 0)
	{
		LCD_SendData('-');
		s_number *= -1;
	}
	while(s_number != 0)
	{
		u_number = ((u_number*10)+(s_number % 10));
		s_number = s_number / 10;
	}
	while(u_number != 1)
	{
		LCD_SendData((u_number%10)+48);
		u_number = u_number /10;
	}
}
void LCD_CursorPosition(u8 line_no,u8 line_position)
{
	switch (line_no)
	{
	case 0 : LCD_SendCommand(0x80+ 0 + line_position);
	break;
	case 1:	LCD_SendCommand(0x80 + 64 + line_position);
	break;
	}
}


