/* 
 * File:   keypad.h
 * Author: peter
 *
 * Created on July 13, 2024, 7:51 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"

/*Section : Macro Declaration*/
#define KEYPAD_RAWS_NUMBER 4
#define KEYPAD_COLUMS_NUMBER 4

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct
{
    pin_config keypad_rows[KEYPAD_RAWS_NUMBER];
    pin_config keypad_colums[KEYPAD_COLUMS_NUMBER];
}keypad_config;

/*Section : Function Declaration*/
STD_ReturnType keypad_initialize(const keypad_config *_keypad_config);
STD_ReturnType keypad_get_value(const keypad_config *_keypad_config , uint8 *value);

#endif	/* KEYPAD_H */

