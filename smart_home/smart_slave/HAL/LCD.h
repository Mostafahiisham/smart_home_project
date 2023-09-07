/*
 * LCD.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Mostafa Hisham
 *      Layer : HAL
 *      SWC   : LCD - PROTOTYPE
 *
 */

#ifndef LCD_H_
#define LCD_H_


                               /********DATA PORT********/
#define  DATA_PORT		DIO_PORTC

                                /********CONTROL PORT********/
#define CTRL_PORT       DIO_PORTB

                                /********CONTROL PIN********/
#define CTRL_RS			DIO_PIN0
#define CTRL_RW			DIO_PIN1
#define CTRL_E			DIO_PIN2
                                /********LCD DISPLAY CONFIGURATION CONTROL********/
#define LCD_DISPLAY_MODE LCD_DISPLAY_ON
#define LCD_CURSOR_MODE  LCD_CURSOR_OFF
#define LCD_LINES_NUMBER LCD_TWO_LINES
#define LCD_FONT_MODE 	 FONT_SIZE_5X7

typedef enum{
    LCD_DISPLAY_OFF,
	LCD_DISPLAY_ON
}LCD_DISPLAY_Status;
typedef enum{
    LCD_CURSOR_OFF,
    LCD_CURSOR_ON_BLINK,
	LCD_CURSOR_ON_NOT_BLINK,
}LCD_CURSOR_Status;

typedef enum{
    LCD_ONE_LINE,
    LCD_TWO_LINES
}LCD_LINES_Status;
typedef enum{
	FONT_SIZE_5X7,
    FONT_SIZE_5X10
}LCD_FONT_Status;

typedef struct
{
	LCD_DISPLAY_Status Display_status;
	LCD_CURSOR_Status Cursor_status;
	LCD_LINES_Status Line_status;
	LCD_FONT_Status Font_status;
}LCD_ControlDisplay;

void LCD_Init(void);
void LCD_DisplayStatus(LCD_ControlDisplay display);
void LCD_DisplayClear();
void LCD_DisplayReturnHome();
void LCD_ShiftCursorRight(u8 counter);
void LCD_ShiftCursorLeft(u8 counter);
void LCD_ShiftDisplayRight(u8 counter);
void LCD_ShiftDisplayLeft(u8 counter);
void LCD_SendString(const u8* Send_string);
void LCD_DisplayNumber(s64 s_number);
void LCD_SaveCustomCharacter(u8 CGRAM_Index,u8* Custom);
void LCD_DisplayCustomCharacter(u8 CGRAM_Index);
void LCD_CursorPosition(u8 line_no,u8 line_Position);

#endif /* INCLUDE_LCD_H_ */
