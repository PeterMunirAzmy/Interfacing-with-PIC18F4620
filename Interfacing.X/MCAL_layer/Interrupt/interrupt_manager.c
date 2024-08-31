/* 
 * File:   interrupt_manager.c
 * Author: peter
 *
 * Created on July 29, 2024, 4:46 AM
 */

#include "interrupt_manager.h"


#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable
void __interrupt() Interrupt_Manager_High(void)
{
    /* ------------------------------ INT0 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF ))
    {
        INT0_ISR();
    }
    /* ------------------------------ INT2 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF ))
    {
        INT2_ISR();
    }
    /* ------------------------------ RB4 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        RB4_ISR();
    }
}


void __interrupt(low_priority) Interrupt_Manager_Low(void)
{
    /* ------------------------------ INT1 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF ))
    {
        INT1_ISR();
    }
    /* ------------------------------ RB5 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        RB5_ISR();
    }
    /* ------------------------------ RB6 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        RB6_ISR();
    }
}

#else
void __interrupt() Interrupt_Manager(void)
{
    /* ------------------------------ ADC interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == PIE1bits.ADIE ) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    
    /* ------------------------------ RB5 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        if(PORTBbits.RB5 == GPIO_HIGH)
        RB5_ISR();
        if(PORTBbits.RB5 == GPIO_LOW)
        RB5_ISR();
    }
    /* ------------------------------ RB4 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        if(PORTBbits.RB4 == GPIO_HIGH)
        RB4_ISR();
        if(PORTBbits.RB4 == GPIO_LOW)
        RB4_ISR();
    }
    
    /* ------------------------------ RB6 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        if(PORTBbits.RB6 == GPIO_HIGH)
        RB6_ISR();
        if(PORTBbits.RB6== GPIO_LOW)
        RB6_ISR();
    }
    /* ------------------------------ RB7 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ))
    {
        if(PORTBbits.RB7 == GPIO_HIGH)
        RB7_ISR();
        if(PORTBbits.RB7 == GPIO_LOW)
        RB7_ISR();
    }
    /* ------------------------------ INT0 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF ))
    {
        INT0_ISR();
    }
    /* ------------------------------ INT1 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF ))
    {
        INT1_ISR();
    }
    /* ------------------------------ INT2 Interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF ))
    {
        INT2_ISR();
    }
    
    /* ------------------------------ TIMER0 interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TMR0_ISR();
    }
    /* ------------------------------ TIMER1 interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
    /* ------------------------------ TIMER2 interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TMR2_ISR();
    }
    /* ------------------------------ TIMER3 interrupt ------------------------------ */
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
}

#endif

