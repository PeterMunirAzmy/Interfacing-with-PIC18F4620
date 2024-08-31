/* 
 * File:   Timer3.c
 * Author: peter
 *
 * Created on August 31, 2024, 9:17 PM
 */

#include "Timer3.h"

static inline void Timer3_Prescaler_config(const timer3_t *timer3_confg);
static inline void Timer3_Mode(const timer3_t *timer3_confg);
static inline void Timer3_Register_Size(const timer3_t *timer3_confg);
static inline void Timer3_Interrupt_init(const timer3_t *timer3_confg);
static inline void Timer3_preloaded_value(const timer3_t *timer3_confg);
static inline void Timer3_Clock_Synchronous_Status(const timer3_t *timer3_confg);


static void(*TMR3_Interrupt_Handler)(void) = NULL;

volatile static uint16 preloaded_value = 0;

/**
 * 
 * @param timer1_confg
 * @return 
 */
STD_ReturnType Timer3_Init(const timer3_t *timer3_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer3_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer3_Disable();
        
        Timer3_Prescaler_config(timer3_confg);
        Timer3_Mode(timer3_confg);
        Timer3_Register_Size(timer3_confg);
        Timer3_Clock_Synchronous_Status(timer3_confg);
        Timer3_preloaded_value(timer3_confg);
        Timer3_Interrupt_init(timer3_confg);
        TMR3_Interrupt_Handler = timer3_confg->Timer3_Interrupt_Handlar;

        Timer3_Enable();
        
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @return 
 */
STD_ReturnType Timer3_Deinit(const timer3_t *timer3_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer3_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer3_Disable();
        TIMER3_INTERRUPT_DISABLE();
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer3_Write_Value(const timer3_t *timer3_confg , uint16 value)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer3_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (value >> 8);
        TMR3L = (uint8)(value);
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer3_Read_Value(const timer3_t *timer3_confg , uint16 *value)
{
    STD_ReturnType ret = E_OK;
    uint8 Tmr3_L = 0 , Tmr3_H = 0; 
    if((NULL == timer3_confg) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        Tmr3_L = TMR3L;
        Tmr3_H = TMR3H;
        *value = (uint16)((Tmr3_H << 8) + Tmr3_L);
    }
    return ret;
}

void TMR3_ISR(void)
{
    TIMER3_INTERRUPT_FLAG_CLEAR();
    TMR3H = (preloaded_value >> 8);
    TMR3L = (uint8)(preloaded_value);
    if(TMR3_Interrupt_Handler)
    {
        TMR3_Interrupt_Handler();
    }
}

/* --------------------------- Helper Function --------------------------- */

static inline void Timer3_Prescaler_config(const timer3_t *timer3_confg) 
{
    T3CONbits.T3CKPS = timer3_confg->prescaler_value;
}

static inline void Timer3_Mode(const timer3_t *timer3_confg) 
{
    switch (timer3_confg->mode) 
    {
        case Timer3_Counter_Mode:
            TIMER3_COUNTER_MODE();
            break;
        case Timer3_Timer_Mode:
            TIMER3_TIMER_MODE();
            break;
        default:
            TIMER3_TIMER_MODE();
            break;
    }
}


static inline void Timer3_Register_Size(const timer3_t *timer3_confg)
{
    switch (timer3_confg->register_size) 
    {
        case Timer3_8Bit_Register:
            TIMER3_8_BIT_R_W_MODE_ENABLE();
            break;
        case Timer3_16Bit_Register:
            TIMER3_16_BIT_R_W_MODE_ENABLE();
            break;
        default:
            TIMER3_16_BIT_R_W_MODE_ENABLE(); 
            break;
    }
}

static inline void Timer3_Interrupt_init(const timer3_t *timer3_confg) 
{
    
    TIMER3_INTERRUPT_ENABLE();
    TIMER3_INTERRUPT_FLAG_CLEAR();
    
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable   
    INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
    switch (timer3_confg->priority) {
        case INTERRUPT_HIGH_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
            TIMER3_HIGHT_BRIORITY_SET();
            break;
        case INTERRUPT_LOW_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
            TIMER3_LOW_BRIORITY_SET();
            break; 
    }
#else
    INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
    INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
#endif
    
}

static inline void Timer3_preloaded_value(const timer3_t *timer3_confg)
{
    TMR3H = ((timer3_confg->preloaded_value) >> 8);
    TMR3L = (uint8)(timer3_confg->preloaded_value);
    preloaded_value = timer3_confg->preloaded_value;
}

static inline void Timer3_Clock_Synchronous_Status(const timer3_t *timer3_confg)
{
    switch (timer3_confg->clock_status) 
    {
        case Timer3_Clock_Synchronous:
            TIMER3_CLOCK_SYNCHRONOUS();
            break;
        case Timer3_Clock_Asynchronous:
            TIMER3_CLOCK_ASYNCHRONOUS();
            break;
        default:
            TIMER3_CLOCK_ASYNCHRONOUS();
            break;
    }
}