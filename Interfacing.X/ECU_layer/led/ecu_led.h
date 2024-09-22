/* 
 * File:   ecu_led.h
 * Author: peter
 *
 * Created on July 1, 2024, 4:02 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"
#include "ecu_led_cfg.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum
{
    LED_OFF,
    LED_ON
           
}led_status;

typedef struct
{
    port_index_t port_name;
    pin_index_t pin_number;
    uint8 led_status;
}led_config;

/*Section : Function Declaration*/
STD_ReturnType ecu_led_initialize(const led_config *_led_config);
STD_ReturnType ecu_led_turn_on(const led_config *_led_config);
STD_ReturnType ecu_led_turn_off(const led_config *_led_config);
STD_ReturnType ecu_led_toggle(const led_config *_led_config);

#endif	/* ECU_LED_H */

