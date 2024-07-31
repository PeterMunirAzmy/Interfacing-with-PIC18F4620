/* 
 * File:   button.c
 * Author: peter
 *
 * Created on July 8, 2024, 12:58 PM
 */

#include "button.h"

/**
 * 
 * @param _button_config
 * @return 
 */
STD_ReturnType ecu_button_init(button_config *_button_config)
{
    STD_ReturnType ret = E_OK;

    if (NULL == _button_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_direction_init(&(_button_config->button_pin));
    }
    
    return ret;
}

/**
 * 
 * @param _button_config
 * @param _button_status
 * @return 
 */
STD_ReturnType ecu_button_read_state(button_config *btn_config ,button_status *_button_status)
{
    logic_t pin_logic_status = GPIO_LOW;
    STD_ReturnType ret = E_NOT_OK;

    if (NULL == btn_config || NULL == _button_status) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        gpio_pin_read_logic(&(btn_config->button_pin) , &pin_logic_status);
        
        if(BUTTON_ACTIVE_HIGHT == btn_config->_button_activ)
        {
            if(pin_logic_status == GPIO_HIGH)
            {
                *_button_status = BUTTON_PRESSED;
            }
            else
            {
                *_button_status = BUTTON_RELEASED;
            }
           
        }
        else if(BUTTON_ACTIVE_LOW == btn_config->_button_activ)
        {
            if(pin_logic_status == GPIO_HIGH)
            {
                *_button_status = BUTTON_RELEASED;
            }
            else
            {
                *_button_status = BUTTON_PRESSED;
            }
        }
        else
        {
            /*DO NOTHING*/
        }
        ret = E_OK;
    }
    
    return ret;
}
