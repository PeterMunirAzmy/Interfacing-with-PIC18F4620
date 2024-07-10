/* 
 * File:   gpio.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

/*Section : includes*/
#include "gpio.h"

volatile uint8 *tris_registers[]={&TRISA ,&TRISB ,&TRISC ,&TRISD ,&TRISE};//data direction register
volatile uint8 *lat_registers[]={&LATA ,&LATB ,&LATC ,&LATD ,&LATE};       //write value to the port
volatile uint8 *port_registers[]={&PORTA ,&PORTB ,&PORTC ,&PORTD ,&PORTE}; //read status of port

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_pin_direction_init(const pin_config *_pin_config)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (_pin_config->direction) {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_pin_get_direction_status(const pin_config *_pin_config , direction_t *direction_status)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_pin_write_logic(const pin_config *_pin_config, logic_t logic)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW :
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin); 
                break;
            case GPIO_HIGH :
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
    
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_pin_read_logic(const pin_config *_pin_config, logic_t *logic)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_pin_toggle_logic(const pin_config *_pin_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_pin_Initialization(const pin_config *_pin_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_init(_pin_config);
        ret = gpio_pin_write_logic(_pin_config , _pin_config->logic);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_port_direction_init(port_index_t port , uint8 direction)
{
    STD_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        *tris_registers[port] = direction;

    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status)
{
    STD_ReturnType ret = E_OK;
    if(NULL == direction_status || port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_port_wrirte_logic(port_index_t port, uint8 logic)
{
    STD_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic)
{
    STD_ReturnType ret = E_OK;
    if(NULL == logic || port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *lat_registers[port];
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == ENABLE_CONFIG
STD_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    STD_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] ^= PORT_MASK;
    }
    return ret;
}
#endif
