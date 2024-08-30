/* 
 * File:   internal_interrupt.h
 * Author: peter
 *
 * Created on July 29, 2024, 4:44 AM
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H

/*Section : Includes*/
#include "interrupt_config.h"


/*Section : Macro Declaration*/


/*Section : Macro Function Declaration*/
#define ADC_INTERRUPT_ENABLE()                (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()               (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_FLAG_CLEAR()            (PIR1bits.ADIF = 0)
#define ADC_HIGHT_BRIORITY_SET()              (IPR1bits.ADIP = 1)
#define ADC_LOW_BRIORITY_SET()                (IPR1bits.ADIP = 0)

#define TIMER0_INTERRUPT_ENABLE()             (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()            (INTCONbits.TMR0IE = 0)
#define TIMER0_INTERRUPT_FLAG_CLEAR()         (INTCONbits.TMR0IF = 0)
#define TIMER0_HIGHT_BRIORITY_SET()           (INTCON2bits.TMR0IP = 1)
#define TIMER0_LOW_BRIORITY_SET()             (INTCON2bits.TMR0IP = 0)

/*Section : Data Type Declaration*/


/*Section : Function Declaration*/


#endif	/* INTERNAL_INTERRUPT_H */

