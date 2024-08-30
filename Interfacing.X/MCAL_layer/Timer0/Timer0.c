/* 
 * File:   Timer0.c
 * Author: peter
 *
 * Created on August 25, 2024, 6:03 PM
 */

#include "Timer0.h"

static inline void Timer0_Prescaler_config(const timer0_t *timer0_confg);
static inline void Timer0_Select_Edge(const timer0_t *timer0_confg);
static inline void Timer0_Mode(const timer0_t *timer0_confg);
static inline void Timer0_Register_Size(const timer0_t *timer0_confg);
static inline void Timer0_Interrupt_init(const timer0_t *timer0_confg);
static inline void Timer0_preloaded_value(const timer0_t *timer0_confg);

static void(*TMR_Interrupt_Handler)(void) = NULL;

static uint16 preloaded_value = 0;

/**
 * 
 * @param timer0_confg
 * @return 
 */
STD_ReturnType Timer0_Init(const timer0_t *timer0_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer0_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer0_Disable();
        
        Timer0_Prescaler_config(timer0_confg);
        Timer0_Register_Size(timer0_confg);
        Timer0_Mode(timer0_confg);
        Timer0_Interrupt_init(timer0_confg);
        TMR_Interrupt_Handler = timer0_confg->Timer0_Interrupt_Handlar;
        Timer0_preloaded_value(timer0_confg);
        
        Timer0_Enable();
        
    }
    return ret;
}

/**
 * 
 * @param timer0_confg
 * @return 
 */
STD_ReturnType Timer0_Deinit(const timer0_t *timer0_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer0_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer0_Disable();
        TIMER0_INTERRUPT_DISABLE();
    }
    return ret;
}

/**
 * 
 * @param timer0_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer0_Write_Value(const timer0_t *timer0_confg , uint16 value)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer0_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR0H = (value >> 8);
        TMR0L = (uint8)(value);
    }
    return ret;
}

/**
 * 
 * @param timer0_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer0_Read_Value(const timer0_t *timer0_confg , uint16 *value)
{
    STD_ReturnType ret = E_OK;
    uint8 Tmr0_L = 0 , Tmr0_H = 0; 
    if((NULL == timer0_confg) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        Tmr0_L = TMR0L;
        Tmr0_H = TMR0H;
        *value = (uint16)((Tmr0_H << 8) + Tmr0_L);
    }
    return ret;
}

void TMR0_ISR(void)
{
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H = (preloaded_value >> 8);
    TMR0L = (uint8)(preloaded_value);
    if(TMR_Interrupt_Handler)
    {
        TMR_Interrupt_Handler();
    }
}

/* --------------------------- Helper Function --------------------------- */

static inline void Timer0_Prescaler_config(const timer0_t *timer0_confg) 
{
    switch (timer0_confg->prescaler_status) 
    {
        case Timer0_Prescaler_Enable:
            TIMER0_PRESCALER_ENABLE();
        case Timer0_Prescaler_Disable:
            TIMER0_PRESCALER_DISABLE();
        default:
            TIMER0_PRESCALER_DISABLE();
    }
    T0CONbits.T0PS = timer0_confg->prescaler_value;
}

static inline void Timer0_Select_Edge(const timer0_t *timer0_confg)
{
    switch (timer0_confg->edge_select) 
    {
        case Timer0_FALLING_EDGE_SELECT:
            TIMER0_FALLING_EDGE_SELECT();
        case Timer0_RISING_EDGE_SELECT:
            TIMER0_RISING_EDGE_SELECT();
        default:
            TIMER0_RISING_EDGE_SELECT();            
    }
}

static inline void Timer0_Mode(const timer0_t *timer0_confg)
{
    switch (timer0_confg->mode) 
    {
        case Timer0_Counter_Mode:
            TIMER0_COUNTER_MODE();
            Timer0_Select_Edge(timer0_confg);
        case Timer0_Timer_Mode:
            TIMER0_TIMER_MODE();
        default:
            TIMER0_TIMER_MODE();            
    }
}

static inline void Timer0_Register_Size(const timer0_t *timer0_confg)
{
    switch (timer0_confg->register_size) 
    {
        case Timer0_8Bit_Register:
            TIMER0_REGISTER_8BIT();
        case Timer0_16Bit_Register:
            TIMER0_REGISTER_16BIT();
        default:
            TIMER0_REGISTER_16BIT();        
    }
}

static inline void Timer0_Interrupt_init(const timer0_t *timer0_confg) 
{
    
    TIMER0_INTERRUPT_ENABLE();
    TIMER0_INTERRUPT_FLAG_CLEAR();
    
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable   
    INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
    switch (timer0_confg->priority) {
        case INTERRUPT_HIGH_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
            TIMER0_HIGHT_BRIORITY_SET();
            break;
        case INTERRUPT_LOW_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
            TIMER0_LOW_BRIORITY_SET();
            break; 
    }
#else
    INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
    INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
#endif
    
}

static inline void Timer0_preloaded_value(const timer0_t *timer0_confg)
{
    TMR0H = ((timer0_confg->preloaded_value) >> 8);
    TMR0L = (uint8)(timer0_confg->preloaded_value);
    preloaded_value = timer0_confg->preloaded_value;
}