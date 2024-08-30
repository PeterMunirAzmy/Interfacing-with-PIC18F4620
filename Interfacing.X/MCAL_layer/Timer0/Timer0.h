/* 
 * File:   Timer0.h
 * Author: peter
 *
 * Created on August 25, 2024, 6:03 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"


/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

#define TIMER0_PRESCALER_ENABLE()               (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()              (T0CONbits.PSA = 1)

#define TIMER0_FALLING_EDGE_SELECT()            (T0CONbits.T0SE = 1)
#define TIMER0_RISING_EDGE_SELECT()             (T0CONbits.T0SE = 0)

#define TIMER0_TIMER_MODE()                     (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE()                   (T0CONbits.T0CS = 1)

#define TIMER0_REGISTER_8BIT()                  (T0CONbits.T08BIT = 1)
#define TIMER0_REGISTER_16BIT()                 (T0CONbits.T08BIT = 0)

#define Timer0_Enable()                         (T0CONbits.TMR0ON = 1)
#define Timer0_Disable()                        (T0CONbits.TMR0ON = 0)

/*Section : Data Type Declaration*/
typedef enum 
{
    Timer0_Prescaler_Dev_2,
    Timer0_Prescaler_Dev_4,
    Timer0_Prescaler_Dev_8,
    Timer0_Prescaler_Dev_16,
    Timer0_Prescaler_Dev_32,
    Timer0_Prescaler_Dev_64,    
    Timer0_Prescaler_Dev_128,
    Timer0_Prescaler_Dev_256
}timer0_prescaler_t;

typedef enum 
{
    Timer0_Prescaler_Enable,
    Timer0_Prescaler_Disable
}timer0_prescaler_status_t;

typedef enum 
{
    Timer0_FALLING_EDGE_SELECT,
    Timer0_RISING_EDGE_SELECT
}timer0_edge_select_t;

typedef enum 
{
    Timer0_Counter_Mode,
    Timer0_Timer_Mode
}timer0_mode_t;

typedef enum 
{
    Timer0_8Bit_Register,
    Timer0_16Bit_Register
}timer0_register_size_t;

typedef struct
{
    void(*Timer0_Interrupt_Handlar)(void);
    interrupt_priority          priority;
    timer0_prescaler_t          prescaler_value;
    timer0_prescaler_status_t   prescaler_status;
    timer0_edge_select_t        edge_select;
    timer0_mode_t               mode;
    timer0_register_size_t      register_size;
    uint16 preloaded_value;
    
}timer0_t;

/*Section : Function Declaration*/
STD_ReturnType Timer0_Init(const timer0_t *timer0_confg);
STD_ReturnType Timer0_Deinit(const timer0_t *timer0_confg);
STD_ReturnType Timer0_Write_Value(const timer0_t *timer0_confg , uint16 value);
STD_ReturnType Timer0_Read_Value(const timer0_t *timer0_confg , uint16 *value);

#endif	/* TIMER0_H */

