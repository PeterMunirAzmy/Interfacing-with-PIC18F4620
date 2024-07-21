/* 
 * File:   lcd.h
 * Author: peter
 *
 * Created on July 21, 2024, 1:40 AM
 */

#ifndef LCD_H
#define	LCD_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"

/*Section : Macro Declaration*/
#define LCD_CLEAR                       0X01
#define LCD_RETURN_HOME                 0X02
#define LCD_ENTRY_MODE                  0X06
#define LCD_CURSOR_OFF_DISPLAY_ON       0X0C
#define LCD_CURSOR_OFF_DISPLAY_OFF      0X08
#define LCD_CURSOR_ON_BLINK_ON          0X0F
#define LCD_CURSOR_ON_BLINK_OFF         0X0E
#define LCD_DISPLAY_SHIFT_RIGHT         0X1C
#define LCD_DISPLAY_SHIFT_LEFT          0X18
#define LCD_8BIT_MODE_2LINES            0X38
#define LCD_4BIT_MODE_2LINES            0X28
#define LCD_CGRAM_START                 0X40
#define LCD_DDRAM_START                 0X80

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct
{
    pin_config lcd_rs;
    pin_config lcd_en;
    pin_config lcd_data[4];
}lcd_4bit;

typedef struct
{
    pin_config lcd_rs;
    pin_config lcd_en;
    pin_config lcd_data[8];
}lcd_8bit;

/*Section : Function Declaration*/
STD_ReturnType lcd_4bit_init(const lcd_4bit *lcd);
STD_ReturnType lcd_4bit_send_command(const lcd_4bit *lcd , uint8 command);
STD_ReturnType lcd_4bit_send_data(const lcd_4bit *lcd , uint8 data);
STD_ReturnType lcd_4bit_send_data_pos(const lcd_4bit *lcd , uint8 row , uint8 colum , uint8 data);
STD_ReturnType lcd_4bit_send_string(const lcd_4bit *lcd , uint8 *str);
STD_ReturnType lcd_4bit_send_string_pos(const lcd_4bit *lcd , uint8 row , uint8 colum , uint8 *str);
STD_ReturnType lcd_4bit_send_custom_char(const lcd_4bit *lcd , uint8 row , uint8 colum , const uint8 _char[] , uint8 mem_pos);


STD_ReturnType lcd_8bit_init(const lcd_8bit *lcd);
STD_ReturnType lcd_8bit_send_command(const lcd_8bit *lcd , uint8 command);
STD_ReturnType lcd_8bit_send_data(const lcd_8bit *lcd , uint8 data);
STD_ReturnType lcd_8bit_send_data_pos(const lcd_8bit *lcd , uint8 row , uint8 colum , uint8 data);
STD_ReturnType lcd_8bit_send_string(const lcd_8bit *lcd , uint8 *str);
STD_ReturnType lcd_8bit_send_string_pos(const lcd_8bit *lcd , uint8 row , uint8 colum , uint8 *str);
STD_ReturnType lcd_8bit_send_custom_char(const lcd_8bit *lcd , uint8 row , uint8 colum , const uint8 _char[] , uint8 mem_pos);

STD_ReturnType convert_byte_to_string(uint8 value , uint8 *str);
STD_ReturnType convert_short_to_string(uint16 value , uint16 *str);
STD_ReturnType convert_int_to_string(uint32 value , uint32 *str);

#endif	/* LCD_H */

