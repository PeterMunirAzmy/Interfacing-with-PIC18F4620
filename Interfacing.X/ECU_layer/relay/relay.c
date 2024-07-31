/* 
 * File:   relay.c
 * Author: peter
 *
 * Created on July 9, 2024, 11:40 PM
 */


#include "relay.h"

/**
 * 
 * @param _relay_config
 * @return 
 */
STD_ReturnType ecu_relay_initializ(const relay_config *_relay_config)
{
     STD_ReturnType ret = E_OK;
     

    if (NULL == _relay_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config relay_init = 
        {
            .port = _relay_config->relay_port,
            .pin = _relay_config->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay_config->relay_status
        };
        
        ret = gpio_pin_Initialization(&relay_init);
    }
    
    return ret;
}

/**
 * 
 * @param _button_config
 * @return 
 */
STD_ReturnType ecu_relay_turn_on(const relay_config *_relay_config)
{
    STD_ReturnType ret = E_OK;

    if (NULL == _relay_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config relay_init = 
        {
            .port = _relay_config->relay_port,
            .pin = _relay_config->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay_config->relay_status
        };
        
        ret = gpio_pin_write_logic(&relay_init , GPIO_HIGH);
        
    }
    
    return ret;
}

/**
 * 
 * @param _button_config
 * @return 
 */
STD_ReturnType ecu_relay_turn_off(const relay_config *_relay_config)
{
    STD_ReturnType ret = E_OK;
    
    
    if (NULL == _relay_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config relay_init = 
        {
            .port = _relay_config->relay_port,
            .pin = _relay_config->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay_config->relay_status
        };
        ret = gpio_pin_write_logic(&relay_init , GPIO_LOW);
    }
    
    return ret;
}

/**
 * 
 * @param _button_config
 * @return 
 */
STD_ReturnType ecu_relay_toggle(const relay_config *_relay_config)
{
    STD_ReturnType ret = E_OK;
    
    if (NULL == _relay_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config relay_init = 
        {
            .port = _relay_config->relay_port,
            .pin = _relay_config->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay_config->relay_status
        };
        ret = gpio_pin_toggle_logic(&relay_init);
    }
    
    return ret;
}
