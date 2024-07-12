/* 
 * File:   dc_motor.c
 * Author: peter
 *
 * Created on July 11, 2024, 1:59 AM
 */

#include "dc_motor.h"

/**
 * 
 * @param _dc_motor_config
 * @return 
 */
STD_ReturnType ecu_dc_motor_initializ(const dc_motor_config *_dc_motor_config)
{
    STD_ReturnType ret = E_OK;
     

    if (NULL == _dc_motor_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config dc_motor_pin_1 = 
        {
            .port = _dc_motor_config->dc_motor[0].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[0].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[0].dc_motor_status
        };
        
        pin_config dc_motor_pin_2 = 
        {
            .port = _dc_motor_config->dc_motor[1].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[1].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[1].dc_motor_status,
        };

        ret = gpio_pin_Initialization(&dc_motor_pin_1);
        ret = gpio_pin_Initialization(&dc_motor_pin_2);
    }
    
    return ret;
}

/**
 * 
 * @param _dc_motor_config
 * @return 
 */
STD_ReturnType ecu_dc_motor_move_right(const dc_motor_config *_dc_motor_config)
{
    STD_ReturnType ret = E_OK;
     

    if (NULL == _dc_motor_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
         pin_config dc_motor_pin_1 = 
        {
            .port = _dc_motor_config->dc_motor[0].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[0].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[0].dc_motor_status
        };
        
        pin_config dc_motor_pin_2 = 
        {
            .port = _dc_motor_config->dc_motor[1].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[1].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[1].dc_motor_status,
        };
        
        ret = gpio_pin_write_logic(&dc_motor_pin_1 , GPIO_HIGH);
        ret = gpio_pin_write_logic(&dc_motor_pin_2 , GPIO_LOW);
    }
    
    return ret;
}

/**
 * 
 * @param _dc_motor_config
 * @return 
 */
STD_ReturnType ecu_dc_motor_move_left(const dc_motor_config *_dc_motor_config)
{
    STD_ReturnType ret = E_OK;
     

    if (NULL == _dc_motor_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config dc_motor_pin_1 = 
        {
            .port = _dc_motor_config->dc_motor[0].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[0].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[0].dc_motor_status
        };
        
        pin_config dc_motor_pin_2 = 
        {
            .port = _dc_motor_config->dc_motor[1].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[1].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[1].dc_motor_status,
        };
        
        ret = gpio_pin_write_logic(&dc_motor_pin_2 , GPIO_HIGH);
        ret = gpio_pin_write_logic(&dc_motor_pin_1 , GPIO_LOW);
    }
    
    return ret;
}

/**
 * 
 * @param _dc_motor_config
 * @return 
 */
STD_ReturnType ecu_dc_motor_stop(const dc_motor_config *_dc_motor_config)
{
    STD_ReturnType ret = E_OK;
     

    if (NULL == _dc_motor_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        pin_config dc_motor_pin_1 = 
        {
            .port = _dc_motor_config->dc_motor[0].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[0].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[0].dc_motor_status
        };
        
        pin_config dc_motor_pin_2 = 
        {
            .port = _dc_motor_config->dc_motor[1].dc_motor_port,
            .pin = _dc_motor_config->dc_motor[1].dc_motor_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _dc_motor_config->dc_motor[1].dc_motor_status,
        };
        
        ret = gpio_pin_write_logic(&dc_motor_pin_1 , GPIO_LOW);
        ret = gpio_pin_write_logic(&dc_motor_pin_2 , GPIO_LOW);
    }
    
    return ret;
}
