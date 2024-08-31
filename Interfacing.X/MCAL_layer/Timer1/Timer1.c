/* 
 * File:   Timer1.c
 * Author: peter
 *
 * Created on August 30, 2024, 10:00 AM
 */

#include "Timer1.h"

static inline void Timer1_Prescaler_config(const timer1_t *timer1_confg);
static inline void Timer1_Mode(const timer1_t *timer1_confg);
static inline void Timer1_Register_Size(const timer1_t *timer1_confg);
static inline void Timer1_Interrupt_init(const timer1_t *timer1_confg);
static inline void Timer1_preloaded_value(const timer1_t *timer1_confg);
static inline void Timer1_OSC_Status(const timer1_t *timer1_confg);
static inline void Timer1_Clock_Synchronous_Status(const timer1_t *timer1_confg);


static void(*TMR1_Interrupt_Handler)(void) = NULL;

static uint16 preloaded_value = 0;

/**
 * 
 * @param timer1_confg
 * @return 
 */
STD_ReturnType Timer1_Init(const timer1_t *timer1_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer1_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer1_Disable();
        
        Timer1_Prescaler_config(timer1_confg);
        Timer1_Mode(timer1_confg);
        Timer1_Register_Size(timer1_confg);
        Timer1_OSC_Status(timer1_confg);
        Timer1_Clock_Synchronous_Status(timer1_confg);
        Timer1_preloaded_value(timer1_confg);
        Timer1_Interrupt_init(timer1_confg);
        TMR1_Interrupt_Handler = timer1_confg->Timer1_Interrupt_Handlar;

        Timer1_Enable();
        
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @return 
 */
STD_ReturnType Timer1_Deinit(const timer1_t *timer1_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer1_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer1_Disable();
        TIMER1_INTERRUPT_DISABLE();
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer1_Write_Value(const timer1_t *timer1_confg , uint16 value)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer1_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (value >> 8);
        TMR1L = (uint8)(value);
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer1_Read_Value(const timer1_t *timer1_confg , uint16 *value)
{
    STD_ReturnType ret = E_OK;
    uint8 Tmr1_L = 0 , Tmr1_H = 0; 
    if((NULL == timer1_confg) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        Tmr1_L = TMR1L;
        Tmr1_H = TMR1H;
        *value = (uint16)((Tmr1_H << 8) + Tmr1_L);
    }
    return ret;
}

void TMR1_ISR(void)
{
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TMR1H = (preloaded_value >> 8);
    TMR1L = (uint8)(preloaded_value);
    if(TMR1_Interrupt_Handler)
    {
        TMR1_Interrupt_Handler();
    }
}

/* --------------------------- Helper Function --------------------------- */

static inline void Timer1_Prescaler_config(const timer1_t *timer1_confg) 
{
    T1CONbits.T1CKPS = timer1_confg->prescaler_value;
}

static inline void Timer1_Mode(const timer1_t *timer1_confg) 
{
    switch (timer1_confg->mode) 
    {
        case Timer1_Counter_Mode:
            TIMER1_COUNTER_MODE();
            break;
        case Timer1_Timer_Mode:
            TIMER1_TIMER_MODE();
            break;
        default:
            TIMER1_TIMER_MODE();
            break;
    }
}


static inline void Timer1_Register_Size(const timer1_t *timer1_confg)
{
    switch (timer1_confg->register_size) 
    {
        case Timer1_8Bit_Register:
            TIMER1_8_BIT_R_W_MODE_ENABLE();
            break;
        case Timer1_16Bit_Register:
            TIMER1_16_BIT_R_W_MODE_ENABLE();
            break;
        default:
            TIMER1_16_BIT_R_W_MODE_ENABLE(); 
            break;
    }
}

static inline void Timer1_Interrupt_init(const timer1_t *timer1_confg) 
{
    
    TIMER1_INTERRUPT_ENABLE();
    TIMER1_INTERRUPT_FLAG_CLEAR();
    
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable   
    INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
    switch (timer1_confg->priority) {
        case INTERRUPT_HIGH_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
            TIMER1_HIGHT_BRIORITY_SET();
            break;
        case INTERRUPT_LOW_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
            TIMER1_LOW_BRIORITY_SET();
            break; 
    }
#else
    INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
    INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
#endif
    
}

static inline void Timer1_preloaded_value(const timer1_t *timer1_confg)
{
    TMR1H = ((timer1_confg->preloaded_value) >> 8);
    TMR1L = (uint8)(timer1_confg->preloaded_value);
    preloaded_value = timer1_confg->preloaded_value;
}

static inline void Timer1_OSC_Status(const timer1_t *timer1_confg)
{
    switch (timer1_confg->timer1_OSC) 
    {
        case Timer1_OSC_Enable:
            TIMER1_OSCILLATOR_ENABLE();
            break;
        case Timer1_OSC_Disable:
            TIMER1_OSCILLATOR_DISABLE();
            break;
        default:
            TIMER1_OSCILLATOR_DISABLE();   
            break;
    }
}

static inline void Timer1_Clock_Synchronous_Status(const timer1_t *timer1_confg)
{
    switch (timer1_confg->clock_status) 
    {
        case Timer1_Clock_Synchronous:
            TIMER1_CLOCK_SYNCHRONOUS();
            break;
        case Timer1_Clock_Asynchronous:
            TIMER1_CLOCK_ASYNCHRONOUS();
            break;
        default:
            TIMER1_CLOCK_ASYNCHRONOUS();
            break;
    }
}

