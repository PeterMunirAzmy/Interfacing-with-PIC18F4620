/* 
 * File:   dc_motor.h
 * Author: peter
 *
 * Created on July 11, 2024, 1:59 AM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/gpio.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum
{
    DC_MOTOR_STATE_OFF = 0,
    DC_MOTOR_STATE_ON
}dc_motor_status_t;

typedef struct
{
    uint8 dc_motor_port : 4;
    uint8 dc_motor_pin : 3;
    uint8 dc_motor_status : 1;
}dc_motor_pin_config;

typedef struct
{
    dc_motor_pin_config dc_motor[2];
}dc_motor_config;

/*Section : Function Declaration*/
STD_ReturnType ecu_dc_motor_initializ(const dc_motor_config *_dc_motor_config);
STD_ReturnType ecu_dc_motor_move_right(const dc_motor_config *_dc_motor_config);
STD_ReturnType ecu_dc_motor_move_left(const dc_motor_config *_dc_motor_config);
STD_ReturnType ecu_dc_motor_stop(const dc_motor_config *_dc_motor_config);

#endif	/* DC_MOTOR_H */

