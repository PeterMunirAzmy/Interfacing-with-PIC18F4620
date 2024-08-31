/* 
 * File:   Timer1.h
 * Author: peter
 *
 * Created on August 30, 2024, 10:00 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"


/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/
#define TIMER1_TIMER_MODE()                     (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE()                   (T1CONbits.TMR1CS = 1)

#define Timer1_Enable()                         (T1CONbits.TMR1ON = 1)
#define Timer1_Disable()                        (T1CONbits.TMR1ON = 0)

#define TIMER1_CLOCK_SYNCHRONOUS()              (T1CONbits.T1SYNC = 0)
#define TIMER1_CLOCK_ASYNCHRONOUS()             (T1CONbits.T1SYNC = 1)

#define  TIMER1_OSCILLATOR_ENABLE()             (T1CONbits.T1OSCEN = 1)
#define  TIMER1_OSCILLATOR_DISABLE()            (T1CONbits.T1OSCEN = 0)
    
#define TIMER1_16_BIT_R_W_MODE_ENABLE()         (T1CONbits.RD16 = 1)
#define TIMER1_8_BIT_R_W_MODE_ENABLE()          (T1CONbits.RD16 = 0)

#define TIMER1_SYSTEM_CLOCK_STATUS()            (T1CONbits.T1RUN)

/*Section : Data Type Declaration*/
typedef enum 
{
    Timer1_Prescaler_Dev_1,
    Timer1_Prescaler_Dev_2,
    Timer1_Prescaler_Dev_4,
    Timer1_Prescaler_Dev_8
}timer1_prescaler_t;

typedef enum 
{
    Timer1_Timer_Mode,
    Timer1_Counter_Mode
    
}timer1_mode_t;

typedef enum 
{
    Timer1_OSC_Enable,
    Timer1_OSC_Disable
    
}timer1_OSC_t;

typedef enum 
{
    Timer1_8Bit_Register,
    Timer1_16Bit_Register
}timer1_register_size_t;

typedef enum 
{
    Timer1_Clock_Synchronous,
    Timer1_Clock_Asynchronous
} timer1_clock_synchronization;

typedef struct
{
    void(*Timer1_Interrupt_Handlar)(void);
    interrupt_priority              priority;
    timer1_prescaler_t              prescaler_value;
    timer1_mode_t                   mode;
    timer1_OSC_t                    timer1_OSC;
    timer1_register_size_t          register_size;
    timer1_clock_synchronization    clock_status;
    uint16 preloaded_value;
    
}timer1_t;

/*Section : Function Declaration*/
STD_ReturnType Timer1_Init(const timer1_t *timer1_confg);
STD_ReturnType Timer1_Deinit(const timer1_t *timer1_confg);
STD_ReturnType Timer1_Write_Value(const timer1_t *timer1_confg , uint16 value);
STD_ReturnType Timer1_Read_Value(const timer1_t *timer1_confg , uint16 *value);

#endif	/* TIMER1_H */

