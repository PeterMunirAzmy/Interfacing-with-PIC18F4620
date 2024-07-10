/* 
 * File:   button.h
 * Author: peter
 *
 * Created on July 8, 2024, 12:58 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum
{
    BUTTON_RELEASED,
    BUTTON_PRESSED
}button_status;

typedef enum
{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGHT
}button_activ;

typedef struct
{
    pin_config button_pin;
    button_status _button_status;
    button_activ _button_activ;
    
}button_config;

/*Section : Function Declaration*/
STD_ReturnType ecu_button_init(button_config *_button_config);
STD_ReturnType ecu_button_read_state(button_config *_button_config ,button_status *_button_status);

#endif	/* BUTTON_H */

