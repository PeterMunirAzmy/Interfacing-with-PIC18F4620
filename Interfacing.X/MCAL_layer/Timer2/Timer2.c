/* 
 * File:   Timer2.c
 * Author: peter
 *
 * Created on August 31, 2024, 5:25 PM
 */

#include "Timer2.h"

static inline void Timer2_Prescaler_config(const timer2_t *timer2_confg);
static inline void Timer2_Postscaler_config(const timer2_t *timer2_confg);
static inline void Timer2_Interrupt_init(const timer2_t *timer2_confg);
static inline void Timer2_preloaded_value(const timer2_t *timer2_confg);



static void(*TMR2_Interrupt_Handler)(void) = NULL;

volatile static uint8 preloaded_value = 0;

/**
 * 
 * @param timer1_confg
 * @return 
 */
STD_ReturnType Timer2_Init(const timer2_t *timer2_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer2_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer2_Disable();
        
        Timer2_Prescaler_config(timer2_confg);
        Timer2_preloaded_value(timer2_confg);
        Timer2_Interrupt_init(timer2_confg);
        TMR2_Interrupt_Handler = timer2_confg->Timer2_Interrupt_Handlar;

        Timer2_Enable();
        
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @return 
 */
STD_ReturnType Timer2_Deinit(const timer2_t *timer2_confg)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer2_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer2_Disable();
        TIMER2_INTERRUPT_DISABLE();
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer2_Write_Value(const timer2_t *timer2_confg , uint8 value)
{
    STD_ReturnType ret = E_OK;
    if(NULL == timer2_confg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR2 = value;
    }
    return ret;
}

/**
 * 
 * @param timer1_confg
 * @param value
 * @return 
 */
STD_ReturnType Timer2_Read_Value(const timer2_t *timer2_confg , uint8 *value)
{
    STD_ReturnType ret = E_OK;
     
    if((NULL == timer2_confg) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *value = TMR2;
    }
    return ret;
}

void TMR2_ISR(void)
{
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TMR2 = preloaded_value;
    if(TMR2_Interrupt_Handler)
    {
        TMR2_Interrupt_Handler();
    }
}

/* --------------------------- Helper Function --------------------------- */

static inline void Timer2_Prescaler_config(const timer2_t *timer2_confg) 
{
    T2CONbits.T2CKPS = timer2_confg->prescaler_value;
}

static inline void Timer2_Postscaler_config(const timer2_t *timer2_confg) 
{
    T2CONbits.TOUTPS = timer2_confg->postscaler_value;
}

static inline void Timer2_Interrupt_init(const timer2_t *timer2_confg) 
{
    TIMER2_INTERRUPT_ENABLE();
    TIMER2_INTERRUPT_FLAG_CLEAR();
    
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable   
    INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
    switch (timer2_confg->priority) {
        case INTERRUPT_HIGH_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
            TIMER2_HIGHT_BRIORITY_SET();
            break;
        case INTERRUPT_LOW_PRIORITY:
            INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
            TIMER2_LOW_BRIORITY_SET();
            break; 
    }
#else
    INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
    INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
#endif
    
}

static inline void Timer2_preloaded_value(const timer2_t *timer2_confg)
{
    preloaded_value = timer2_confg->preloaded_value;
}
