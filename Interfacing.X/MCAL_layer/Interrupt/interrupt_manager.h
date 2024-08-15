/* 
 * File:   interrupt_manager.h
 * Author: peter
 *
 * Created on July 29, 2024, 4:46 AM
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H

/*Section : Includes*/
#include "interrupt_config.h"


/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/

/*Section : Function Declaration*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);

void ADC_ISR(void);

#endif	/* INTERRUPT_MANAGER_H */

