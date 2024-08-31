/* 
 * File:   Timer3.h
 * Author: peter
 *
 * Created on August 31, 2024, 9:17 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"


/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/
#define TIMER3_TIMER_MODE()                     (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE()                   (T3CONbits.TMR3CS = 1)

#define Timer3_Enable()                         (T3CONbits.TMR3ON = 1)
#define Timer3_Disable()                        (T3CONbits.TMR3ON = 0)

#define TIMER3_CLOCK_SYNCHRONOUS()              (T3CONbits.T3SYNC = 0)
#define TIMER3_CLOCK_ASYNCHRONOUS()             (T3CONbits.T3SYNC = 1)

#define TIMER3_16_BIT_R_W_MODE_ENABLE()         (T3CONbits.RD16 = 1)
#define TIMER3_8_BIT_R_W_MODE_ENABLE()          (T3CONbits.RD16 = 0)

/*Section : Data Type Declaration*/
typedef enum 
{
    Timer3_Prescaler_Dev_1,
    Timer3_Prescaler_Dev_2,
    Timer3_Prescaler_Dev_4,
    Timer3_Prescaler_Dev_8
}timer3_prescaler_t;

typedef enum 
{
    Timer3_Timer_Mode,
    Timer3_Counter_Mode
    
}timer3_mode_t;

typedef enum 
{
    Timer3_8Bit_Register,
    Timer3_16Bit_Register
}timer3_register_size_t;

typedef enum 
{
    Timer3_Clock_Synchronous,
    Timer3_Clock_Asynchronous
} timer3_clock_synchronization;

typedef struct
{
    void(*Timer3_Interrupt_Handlar)(void);
    interrupt_priority              priority;
    timer3_prescaler_t              prescaler_value;
    timer3_mode_t                   mode;
    timer3_register_size_t          register_size;
    timer3_clock_synchronization    clock_status;
    uint16 preloaded_value;
}timer3_t;

/*Section : Function Declaration*/
STD_ReturnType Timer3_Init(const timer3_t *timer3_confg);
STD_ReturnType Timer3_Deinit(const timer3_t *timer3_confg);
STD_ReturnType Timer3_Write_Value(const timer3_t *timer3_confg , uint16 value);
STD_ReturnType Timer3_Read_Value(const timer3_t *timer3_confg , uint16 *value);

#endif	/* TIMER3_H */

