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
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF ))
    {
        INT0_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF ))
    {
        INT2_ISR();
    }
}


void __interrupt(low_priority) Interrupt_Manager_Low(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF ))
    {
        INT1_ISR();
    }
}

#else
void __interrupt() Interrupt_Manager(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF ))
    {
        INT0_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF ))
    {
        INT1_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF ))
    {
        INT2_ISR();
    }
}

#endif

