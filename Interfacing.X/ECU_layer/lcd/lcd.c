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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
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
        
    }
}

/*----------------------- numbers to string functions -----------------------*/

/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_byte_to_string(uint8 value , uint8 *str)
{
    
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_short_to_string(uint16 value , uint16 *str)
{
    
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_int_to_string(uint32 value , uint32 *str)
{
    
}

