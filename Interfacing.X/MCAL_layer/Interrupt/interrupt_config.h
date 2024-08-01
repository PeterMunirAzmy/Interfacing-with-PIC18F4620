/* 
 * File:   interrupt_config.h
 * Author: peter
 *
 * Created on July 29, 2024, 4:47 AM
 */

#ifndef INTERRUPT_CONFIG_H
#define	INTERRUPT_CONFIG_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"

/*Section : Macro Declaration*/

#define INTERRUPT_ENABLE                    1
#define INTERRUPT_DISABLE                   0

#define INTERRUPT_OCCUR                     1
#define INTERRUPT_NOT_OCCUR                 0

#define INTERRUPT_PRIORITY_ENABLE           1
#define INTERRUPT_PRIORITY_DISABLE          0

#define Interrupt_Feature_Enable 1U
//#define Interrupt_Priority_level_Enable  Interrupt_Feature_Enable
#define Interrupt_INTx_Feature_Enable   Interrupt_Feature_Enable
#define Interrupt_OnChange_Feature_Enable   Interrupt_Feature_Enable

/*Section : Macro Function Declaration*/

#define INTERRUPT_ENABLE_BRIORITY_INTERRUPT()                   (RCONbits.IPEN = 1)
#define INTERRUPT_DISABLE_BRIORITY_INTERRUPT()                  (RCONbits.IPEN = 0)

#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable
    #define INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT()      (INTCONbits.GIEH = 1)
    #define INTERRUPT_DISABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT()     (INTCONbits.GIEH = 0)

    #define INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT()        (INTCONbits.GIEL = 1)
    #define INTERRUPT_DISABLE_GLOBLE_LOW_BRIORITY_INTERRUPT()       (INTCONbits.GIEL = 0)
#else
    #define INTERRUPT_ENABLE_GLOBLE_INTERRUPT()                     (INTCONbits.GIE = 1)
    #define INTERRUPT_DISABLE_GLOBLE_INTERRUPT()                    (INTCONbits.GIE = 0)

    #define INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT()                 (INTCONbits.PEIE = 1)
    #define INTERRUPT_DISABLE_PERIPHERAL_INTERRUPT()                (INTCONbits.PEIE = 0)
#endif

/*Section : Data Type Declaration*/
typedef enum
{
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority;

/*Section : Function Declaration*/


#endif	/* INTERRUPT_CONFIG_H */

