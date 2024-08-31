/* 
 * File:   Timer2.h
 * Author: peter
 *
 * Created on August 31, 2024, 5:25 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/
#define Timer2_Enable()                         (T2CONbits.TMR2ON = 1)
#define Timer2_Disable()                        (T2CONbits.TMR2ON = 0)

/*Section : Data Type Declaration*/
typedef enum 
{
    Timer2_Prescaler_Dev_1,
    Timer2_Prescaler_Dev_4,
    Timer2_Prescaler_Dev_16
}timer2_prescaler_t;

typedef enum 
{
    Timer2_Disable,
    Timer2_Enable
}timer2_Status_t;

typedef enum 
{
    Timer2_Postscaler_Dev_1,
    Timer2_Postscaler_Dev_2,
    Timer2_Postscaler_Dev_3,
    Timer2_Postscaler_Dev_4,
    Timer2_Postscaler_Dev_5,
    Timer2_Postscaler_Dev_6,
    Timer2_Postscaler_Dev_7,
    Timer2_Postscaler_Dev_8,
    Timer2_Postscaler_Dev_9,
    Timer2_Postscaler_Dev_10,
    Timer2_Postscaler_Dev_11,
    Timer2_Postscaler_Dev_12,
    Timer2_Postscaler_Dev_13,
    Timer2_Postscaler_Dev_14,
    Timer2_Postscaler_Dev_15,
    Timer2_Postscaler_Dev_16
            
}timer2_postscaler_t;

typedef struct
{
    void(*Timer2_Interrupt_Handlar)(void);
    interrupt_priority              priority;
    timer2_prescaler_t              prescaler_value;
    timer2_postscaler_t             postscaler_value;
    uint8 preloaded_value;
    
}timer2_t;

/*Section : Function Declaration*/
STD_ReturnType Timer2_Init(const timer2_t *timer2_confg);
STD_ReturnType Timer2_Deinit(const timer2_t *timer2_confg);
STD_ReturnType Timer2_Write_Value(const timer2_t *timer2_confg , uint8 value);
STD_ReturnType Timer2_Read_Value(const timer2_t *timer2_confg , uint8 *value);

#endif	/* TIMER2_H */

