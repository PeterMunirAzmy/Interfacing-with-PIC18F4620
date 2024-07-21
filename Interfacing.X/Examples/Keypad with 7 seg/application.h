/* 
 * File:   application.h
 * Author: peter
 *
 * Created on July 1, 2024, 3:54 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/*Section : Includes*/
#include "ECU_layer/led/ecu_led.h"
#include "ECU_layer/button/button.h"
#include "ECU_layer/relay/relay.h"
#include "ECU_layer/dc_motor/dc_motor.h"
#include "ECU_layer/7-seg/7-seg.h"
#include "ECU_layer/lcd/lcd.h"



/*Section : Macro Declaration*/
#define _XTAL_FREQ 8000000UL
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/

/*Section : Function Declaration*/
void application_initializ(void);


#endif	/* APPLICATION_H */

