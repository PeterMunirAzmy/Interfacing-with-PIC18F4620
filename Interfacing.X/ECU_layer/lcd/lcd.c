/* 
 * File:   lcd.c
 * Author: peter
 *
 * Created on July 21, 2024, 1:40 AM
 */

#include "lcd.h"



/**
 * 
 * @param lcd
 * @return 
 */
STD_ReturnType lcd_4bit_init(const lcd_4bit *lcd)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_Initialization(&(lcd->lcd_rs));
        ret = gpio_pin_Initialization(&(lcd->lcd_en));
        for(int i=0 ; i<4 ; i++)
        {
            ret = gpio_pin_Initialization(&(lcd->lcd_data[i]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        
        ret = lcd_4bit_send_command(lcd , LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd , LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd , LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd , LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd , LCD_4BIT_MODE_2LINES);
        ret = lcd_4bit_send_command(lcd , 0x80);
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
STD_ReturnType lcd_4bit_send_command(const lcd_4bit *lcd , uint8 command)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        ret = lcd_send_4bits(lcd, command >> 4);
        ret = lcd_send_4bit_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_send_4bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_ReturnType lcd_4bit_send_data(const lcd_4bit *lcd , uint8 data)
{
    STD_ReturnType ret = E_OK;

    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        ret = lcd_send_4bits(lcd, data >> 4);
        ret = lcd_send_4bit_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_send_4bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param data
 * @return 
 */
STD_ReturnType lcd_4bit_send_data_pos(const lcd_4bit *lcd , uint8 row , uint8 colum , uint8 data)
{
    STD_ReturnType ret = E_OK;

    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = lcd_4bit_set_cursor(lcd, row, colum);
        ret = lcd_4bit_send_data(lcd, data);
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
STD_ReturnType lcd_4bit_send_string(const lcd_4bit *lcd , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    
    if ((NULL == lcd) || (NULL == str)) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        while(*str)
        {
            ret = lcd_4bit_send_data(lcd , *str++);
            
            if (ret != E_OK) // Check if there was an error and break if so
            {
                break;
            }
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param str
 * @return 
 */
STD_ReturnType lcd_4bit_send_string_pos(const lcd_4bit *lcd , uint8 row , uint8 colum , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    
    if ((NULL == lcd) || (NULL == str)) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = lcd_4bit_set_cursor(lcd , row , colum);
        while(*str)
        {
            ret = lcd_4bit_send_data(lcd , *str++);
            
            if (ret != E_OK) // Check if there was an error and break if so
            {
                break;
            }
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param _char
 * @param mem_pos
 * @return 
 */
STD_ReturnType lcd_4bit_send_custom_char(const lcd_4bit *lcd , uint8 row , uint8 colum , const uint8 _char[] , uint8 mem_pos)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = lcd_4bit_send_command(lcd , (LCD_CGRAM_START + (mem_pos * 8)));
        for(uint8 i=0 ; i<8 ; i++)
        {
            ret = lcd_4bit_send_data(lcd, _char[i]);
        }
        
        ret = lcd_4bit_send_data_pos(lcd, row, colum , mem_pos);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_ReturnType lcd_send_4bits(const lcd_4bit *lcd , uint8 data_command)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[i]) , (data_command >> i) & 0x01);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data_command
 * @return 
 */ 
STD_ReturnType lcd_send_4bit_enable_signal(const lcd_4bit *lcd)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH);
        __delay_ms(1);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW);
    }
    return ret;
}


STD_ReturnType lcd_4bit_set_cursor(const lcd_4bit *lcd , uint8 row , uint8 colum)
{
    STD_ReturnType ret = E_OK;
    colum--;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        switch(row)
        {
            case 1:
                ret = lcd_4bit_send_command(lcd , (0x80 + colum));
                break;
            case 2:
                ret = lcd_4bit_send_command(lcd , (0xC0 + colum));
                break; 
            case 3:
                ret = lcd_4bit_send_command(lcd , (0x94 + colum));
                break;
            case 4:
                ret = lcd_4bit_send_command(lcd , (0xD4 + colum));
                break;
            default:
                ret = lcd_4bit_send_command(lcd , LCD_RETURN_HOME);
                break;
        }
    }
    return ret;
}

/*------------------------------ 8 bit section ------------------------------*/

/**
 * 
 * @param lcd
 * @return 
 */
STD_ReturnType lcd_8bit_init(const lcd_8bit *lcd)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_Initialization(&(lcd->lcd_rs));
        ret = gpio_pin_Initialization(&(lcd->lcd_en));
        for(int i=0 ; i<8 ; i++)
        {
            ret = gpio_pin_Initialization(&(lcd->lcd_data[i]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        
        ret = lcd_8bit_send_command(lcd , LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd , LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd , LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd , LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_MODE_2LINES);
        ret = lcd_8bit_send_command(lcd , 0x80);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
STD_ReturnType lcd_8bit_send_command(const lcd_8bit *lcd , uint8 command)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        for(int i = 0 ; i < 8 ; i++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[i]) , (command >> i) & 0x01);
        }
        ret = lcd_send_8bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_ReturnType lcd_8bit_send_data(const lcd_8bit *lcd , uint8 data)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        for(int i = 0 ; i < 8 ; i++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[i]) , (data >> i) & 0x01);
        }
        ret = lcd_send_8bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param data
 * @return 
 */
STD_ReturnType lcd_8bit_send_data_pos(const lcd_8bit *lcd , uint8 row , uint8 colum , uint8 data)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = lcd_8bit_set_cursor(lcd , row, colum);
        ret = lcd_8bit_send_data(lcd , data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
STD_ReturnType lcd_8bit_send_string(const lcd_8bit *lcd , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    
    if ((NULL == lcd) || (NULL == str)) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        while(*str)
        {
            ret = lcd_8bit_send_data(lcd , *str++);
            
            if (ret != E_OK) // Check if there was an error and break if so
            {
                break;
            }
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param str
 * @return 
 */
STD_ReturnType lcd_8bit_send_string_pos(const lcd_8bit *lcd , uint8 row , uint8 colum , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    
    if ((NULL == lcd) || (NULL == str)) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = lcd_8bit_set_cursor(lcd , row, colum);
        while(*str)
        {
            ret = lcd_8bit_send_data(lcd , *str++);
            if (ret != E_OK) // Check if there was an error and break if so
            {
                break;
            }
        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @param _char
 * @param mem_pos
 * @return 
 */
STD_ReturnType lcd_8bit_send_custom_char(const lcd_8bit *lcd , uint8 row , uint8 colum , const uint8 _char[] , uint8 mem_pos)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = lcd_8bit_send_command(lcd , (LCD_CGRAM_START + (mem_pos * 8)));
        for(uint8 i=0 ; i<8 ; i++)
        {
            ret = lcd_8bit_send_data(lcd, _char[i]);
        }
        
        ret = lcd_8bit_send_data_pos(lcd, row, colum , mem_pos);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
STD_ReturnType lcd_send_8bit_enable_signal(const lcd_8bit *lcd)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH);
        __delay_us(1);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colum
 * @return 
 */
STD_ReturnType lcd_8bit_set_cursor(const lcd_8bit *lcd , uint8 row , uint8 colum)
{
    STD_ReturnType ret = E_OK;
    colum--;

    
    if (NULL == lcd) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        switch(row)
        {
            case 1:
                ret = lcd_8bit_send_command(lcd , (0x80 + colum));
                break;
            case 2:
                ret = lcd_8bit_send_command(lcd , (0xC0 + colum));
                break; 
            case 3:
                ret = lcd_8bit_send_command(lcd , (0x94 + colum));
                break;
            case 4:
                ret = lcd_8bit_send_command(lcd , (0xD4 + colum));
                break;
            default:
                ret = lcd_8bit_send_command(lcd , LCD_RETURN_HOME);
                break;
        }
    }
    return ret;
}

/*----------------------- numbers to string functions -----------------------*/

/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_uint8_to_string(uint8 value , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    uint8 temp_string[4]={0};
    uint8 counter = 0;
    
    if (NULL == str) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        memset(str, ' ' , 3);
        str[3]='\0';
        sprintf((char *)temp_string , "%i" ,value);
        while(temp_string[counter] != '\0')
        {
            str[counter] = temp_string[counter];
            counter++;
        }
    }
    return ret; 
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_uint16_to_string(uint16 value , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    uint8 temp_string[6]={0};
    uint8 counter = 0;
    
    if (NULL == str) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        memset(str, ' ' , 5);
        str[5]='\0';
        sprintf((char *)temp_string , "%i" ,value);
        while(temp_string[counter] != '\0')
        {
            str[counter] = temp_string[counter];
            counter++;
        }
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_uint32_to_string(uint32 value , uint8 *str)
{
    STD_ReturnType ret = E_OK;
    uint8 temp_string[11]={0};
    uint8 counter = 0;
    
    if (NULL == str) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        memset(str, ' ' , 10);
        str[10]='\0';
        sprintf((char *)temp_string , "%i" ,value);
        while(temp_string[counter] != '\0')
        {
            str[counter] = temp_string[counter];
            counter++;
        }
    }
    return ret;
}



