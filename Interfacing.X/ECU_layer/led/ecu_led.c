/* 
 * File:   ecu_led.c
 * Author: peter
 *
 * Created on July 1, 2024, 4:02 AM
 */

#include "ecu_led.h"
/**
 * 
 * @param _led_config
 * @return 
 */
STD_ReturnType ecu_led_initialize(const led_config *_led_config)
{
    STD_ReturnType ret = E_OK;

    if (NULL == _led_config) {
        ret = E_NOT_OK;
    } else {
        pin_config _pin_config ={
            .port = _led_config->port_name,
            .pin = _led_config->pin_number,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _led_config->led_status
        };

        ret = gpio_pin_Initialization(&_pin_config);
    }
    
    return ret;
}

/**
 * 
 * @param _led_config
 * @return 
 */
STD_ReturnType ecu_led_turn_on(const led_config *_led_config)
{
    STD_ReturnType ret = E_OK;

    if (NULL == _led_config) {
        ret = E_NOT_OK;
    } else {
        pin_config _pin_config ={
            .port = _led_config->port_name,
            .pin = _led_config->pin_number,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _led_config->led_status
        };
        ret = gpio_pin_write_logic(&_pin_config, GPIO_HIGH);
    }
    
    return ret;
}

/**
 * 
 * @param _led_config
 * @return 
 */
STD_ReturnType ecu_led_turn_off(const led_config *_led_config)
{
    STD_ReturnType ret = E_OK;

    if (NULL == _led_config) {
        ret = E_NOT_OK;
    } else {
        pin_config _pin_config ={
            .port = _led_config->port_name,
            .pin = _led_config->pin_number,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _led_config->led_status
        };
        ret = gpio_pin_write_logic(&_pin_config, GPIO_LOW);
    }
    
    return ret;
}

/**
 * 
 * @param _led_config
 * @return 
 */
STD_ReturnType ecu_led_toggle(const led_config *_led_config)
{
    STD_ReturnType ret = E_OK;

    if (NULL == _led_config) {
        ret = E_NOT_OK;
    } else {
        pin_config _pin_config ={
            .port = _led_config->port_name,
            .pin = _led_config->pin_number,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _led_config->led_status
        };
        ret = gpio_pin_toggle_logic(&_pin_config);
    }
    
    return ret;
}

