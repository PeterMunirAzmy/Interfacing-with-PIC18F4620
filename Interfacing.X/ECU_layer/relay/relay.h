/* 
 * File:   relay.h
 * Author: peter
 *
 * Created on July 9, 2024, 11:40 PM
 */

#ifndef RELAY_H
#define	RELAY_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum
{
    RELAY_STATE_OFF = 0,
    RELAY_STATE_ON
}relay_status_t;

typedef struct
{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_config;

/*Section : Function Declaration*/
STD_ReturnType ecu_relay_initializ(const relay_config *_relay_config);
STD_ReturnType ecu_relay_turn_on(const relay_config *_relay_config); 
STD_ReturnType ecu_relay_turn_off(const relay_config *_relay_config);
STD_ReturnType ecu_relay_toggle(const relay_config *_relay_config);
#endif	/* RELAY_H */

