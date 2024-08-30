/* 
 * File:   gpio.h
 * Author: peter
 *
 * Created on July 1, 2024, 3:26 AM
 */



#ifndef gpio_H
#define	gpio_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"

/*Section : Macro Declaration*/
#define BIT_MASK                        (uint8)1

#define PIN_MAX_NUMBER                  8
#define PORT_MAX_NUMBER                 5

#define PORT_MASK                       0xFF

#define GPIO_PORT_PIN_CONFIGURATION      ENABLE_CONFIG
#define GPIO_PORT_CONFIGURATION          ENABLE_CONFIG

/*Section : Macro Function Declaration*/
#define HWREG8(_x)                      (*((volatile uint8 *)(_x)))

/*
 REG -> lat[portX] , tris[portX] , port[portX]
 POS -> pin number
 */

#define SET_BIT(REG,BIT_POS)        (REG |= (BIT_MASK << BIT_POS))      
#define CLEAR_BIT(REG,BIT_POS)      (REG &= ~(BIT_MASK << BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS)     (REG ^= (BIT_MASK << BIT_POS))


#define READ_BIT(REG,BIT_POS)           ((REG >> BIT_POS)& BIT_MASK)

/*Section : Data Type Declaration*/
typedef enum 
{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum 
{
    GPIO_DIRECTION_OUTPUT,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum 
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

typedef enum 
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
    
}port_index_t;

typedef struct
{
    port_index_t port;
    pin_index_t pin;
    direction_t direction;
    logic_t logic; 
    
}pin_config;

/*Section : Function Declaration*/
STD_ReturnType gpio_pin_direction_init(const pin_config *_pin_config);
STD_ReturnType gpio_pin_get_direction_status(const pin_config *_pin_config , direction_t *direction_status);
STD_ReturnType gpio_pin_write_logic(const pin_config *_pin_config, logic_t logic);
STD_ReturnType gpio_pin_read_logic(const pin_config *_pin_config, logic_t *logic);
STD_ReturnType gpio_pin_toggle_logic(const pin_config *_pin_config);
STD_ReturnType gpio_pin_Initialization(const pin_config *_pin_config);

STD_ReturnType gpio_port_direction_init(port_index_t port , uint8 direction);
STD_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);
STD_ReturnType gpio_port_wrirte_logic(port_index_t port, uint8 logic);
STD_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
STD_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* gpio_H */
