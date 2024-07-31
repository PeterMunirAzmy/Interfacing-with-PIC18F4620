/* 
 * File:   external_interrupt.h
 * Author: peter
 *
 * Created on July 29, 2024, 4:44 AM
 */

#ifndef EXTERNAL_INTERRUPT_H
#define	EXTERNAL_INTERRUPT_H

/*Section : Includes*/
#include "interrupt_config.h" 

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/
/*-------------- For INT0 --------------*/
#define EXTERNAL_INT0_INTERRUPT_ENABLE()                (INTCONbits.INT0IE = 1)
#define EXTERNAL_INT0_INTERRUPT_DISABLE()               (INTCONbits.INT0IE = 0)

#define EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR()            (INTCONbits.INT0IF = 0)

#define EXTERNAL_INT0_RISING_EDGE_SET()                 (INTCON2bits.INTEDG0 = 1)
#define EXTERNAL_INT0_FALLING_EDGE_SET()                (INTCON2bits.INTEDG0 = 0)

/*-------------- For INT1 --------------*/
#define EXTERNAL_INT1_INTERRUPT_ENABLE()                (INTCON3bits.INT1IE = 1)
#define EXTERNAL_INT1_INTERRUPT_DISABLE()               (INTCON3bits.INT1IE = 0)

#define EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR()            (INTCON3bits.INT1IF = 0)

#define EXTERNAL_INT1_RISING_EDGE_SET()                 (INTCON2bits.INTEDG1 = 1)
#define EXTERNAL_INT1_FALLING_EDGE_SET()                (INTCON2bits.INTEDG1 = 0)

#define EXTERNAL_INT1_HIGHT_BRIORITY_SET()              (INTCON3bits.INT1IP = 1)
#define EXTERNAL_INT1_LOW_BRIORITY_SET()                (INTCON3bits.INT1IP = 0)

/*-------------- For INT2 --------------*/
#define EXTERNAL_INT2_INTERRUPT_ENABLE()                (INTCON3bits.INT2IE = 1)
#define EXTERNAL_INT2_INTERRUPT_DISABLE()               (INTCON3bits.INT2IE = 0)

#define EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR()            (INTCON3bits.INT2IF = 0)

#define EXTERNAL_INT2_RISING_EDGE_SET()                 (INTCON2bits.INTEDG2 = 1)
#define EXTERNAL_INT2_FALLING_EDGE_SET()                (INTCON2bits.INTEDG2 = 0)

#define EXTERNAL_INT2_HIGHT_BRIORITY_SET()              (INTCON3bits.INT2IP = 1)
#define EXTERNAL_INT2_LOW_BRIORITY_SET()                (INTCON3bits.INT2IP = 0)

/*-------------- For RBX --------------*/
#define EXTERNAL_RBX_INTERRUPT_ENABLE()                (INTCONbits.RBIE = 1)
#define EXTERNAL_RBX_INTERRUPT_DISABLE()               (INTCONbits.RBIE = 0)

#define EXTERNAL_RBX_INTERRUPT_FLAG_CLEAR()            (INTCONbits.RBIF = 0)

#define EXTERNAL_RBX_HIGHT_BRIORITY_SET()              (INTCON2bits.RBIP = 1)
#define EXTERNAL_RBX_LOW_BRIORITY_SET()                (INTCON2bits.RBIP = 0)

/*Section : Data Type Declaration*/

typedef enum
{
    INTERRUPT_EXTERNAL_INT0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_source;

typedef enum
{
    INTERRUPT_FALLING_EDGE,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef struct
{
    void (* EXTERNAL_INTERRUPT_CALLBACK)(void);
    pin_config interrupt_pin;
    interrupt_INTx_source INTx;
    interrupt_INTx_edge edge;
    interrupt_priority priority;
}interrupt_INTx;

typedef struct
{
    void (* EXTERNAL_INTERRUPT_CALLBACK)(void);
    pin_config interrupt_pin;
    interrupt_priority priority;
}interrupt_RBx;

/*Section : Function Declaration*/
STD_ReturnType Interrupt_INTx_init(const interrupt_INTx *_interrupt_INTx);
/*-------------- disable INTx --------------*/
STD_ReturnType Interrupt_INTx_deinit(const interrupt_INTx *_interrupt_INTx);

STD_ReturnType Interrupt_RBx_init(const interrupt_RBx *_interrupt_RBx);
/*-------------- disable RBx --------------*/
STD_ReturnType Interrupt_RBx_deinit(const interrupt_RBx *_interrupt_RBx); 

#endif	/* EXTERNAL_INTERRUPT_H */

