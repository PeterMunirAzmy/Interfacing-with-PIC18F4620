/* 
 * File:   keypad.c
 * Author: peter
 *
 * Created on July 13, 2024, 7:51 PM
 */

#include "keypad.h"

const uint8 keypad_sampels[KEYPAD_RAWS_NUMBER][KEYPAD_COLUMS_NUMBER] = {
    {'7' ,'8' ,'9' ,'/'},
    {'4' ,'5' ,'6' ,'*'},
    {'1' ,'2' ,'3' ,'-'},
    {'#' ,'0' ,'=' ,'+'}
};

/**
 * 
 * @param _keypad_config
 * @return 
 */
STD_ReturnType keypad_initialize(const keypad_config *_keypad_config)
{
    STD_ReturnType ret = E_OK;
 
    if (NULL == _keypad_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        for(int i = 0 ; i < KEYPAD_RAWS_NUMBER ; i++)
        {
        ret = gpio_pin_Initialization(&(_keypad_config->keypad_rows[i]));
        }
        
        for(int j = 0 ; j < KEYPAD_COLUMS_NUMBER ; j++)
        {
        ret = gpio_pin_Initialization(&(_keypad_config->keypad_colums[j]));
        }
        
    }
    return ret;
}

/**
 * 
 * @param _keypad_config
 * @param value
 * @return 
 */
STD_ReturnType keypad_get_value(const keypad_config *_keypad_config , uint8 *value)
{
    STD_ReturnType ret = E_OK;
    uint8 colum_logic = 0;
    
    if ((NULL == _keypad_config) || (NULL == value)) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        for(int i = 0 ; i < KEYPAD_RAWS_NUMBER ; i++)
        {
            for(int j = 0 ; j < KEYPAD_RAWS_NUMBER ; j++)
            {
                ret = gpio_pin_write_logic(&(_keypad_config->keypad_rows[j]) , GPIO_LOW);
            }
            
            ret = gpio_pin_write_logic(&(_keypad_config->keypad_rows[i]) , GPIO_HIGH);
            
            for(int k=0 ; k < KEYPAD_COLUMS_NUMBER ; k++)
            {
                ret = gpio_pin_read_logic(&(_keypad_config->keypad_colums[k]) , &colum_logic);
                
                if(GPIO_HIGH == colum_logic)
                {
                    *value = keypad_sampels[i][k];
                }
            }
        }
        
    }
    return ret;
}