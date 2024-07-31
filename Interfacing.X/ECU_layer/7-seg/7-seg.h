/* 
 * File:   newfile.h
 * Author: peter
 *
 * Created on July 12, 2024, 3:17 PM
 */

#ifndef NEWFILE_H
#define	NEWFILE_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum
{
    seg_pin0,
    seg_pin1,
    seg_pin2,
    seg_pin3      
            
}seg_pins;

typedef struct
{
    pin_config _seg_pin[4];
}seg_config;

/*Section : Function Declaration*/
STD_ReturnType seg_initialization(const seg_config *_seg_config);
STD_ReturnType seg_write_number(const seg_config *_seg_config , uint8 number);

#endif	/* NEWFILE_H */

