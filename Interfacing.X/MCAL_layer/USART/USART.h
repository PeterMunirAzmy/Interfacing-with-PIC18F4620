/* 
 * File:   USART.h
 * Author: peter
 *
 * Created on September 20, 2024, 10:48 PM
 */

#ifndef USART_H
#define	USART_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum
{
    USART_Asynchronous_Mode,
    USART_Synchronous_Mode
}usart_mode;

typedef enum
{
    USART_DISABLE,
    USART_ENABLE
}usart_status;

typedef enum
{
    USART_Asynchronous_Low_Speed,
    USART_Asynchronous_High_Speed
}usart_asynchronous_speed;

typedef enum
{
    USART_8Bit_BaudRate_Gen,
    USART_16Bit_BaudRate_Gen
}usart_baud_rate_gen;

typedef enum
{
    USART_Asynchronous_TX_Disable,
    USART_Asynchronous_TX_Enable
}usart_asynchronous_tx;

typedef enum
{
    USART_Asynchronous_TX_Interrupt_Disable,
    USART_Asynchronous_TX_Interrupt_Enable
}usart_asynchronous_tx_interrupt;

typedef enum
{
    USART_Asynchronous_TX_9bit_Disable,
    USART_Asynchronous_TX_9bit_Enable
}usart_asynchronous_tx_9bits;

typedef enum
{
    USART_Asynchronous_RX_Disable,
    USART_Asynchronous_RX_Enable
}usart_asynchronous_rx;

typedef enum
{
    USART_Asynchronous_RX_Interrupt_Disable,
    USART_Asynchronous_RX_Interrupt_Enable
}usart_asynchronous_rx_interrupt;

typedef enum
{
    USART_Asynchronous_RX_9bit_Disable,
    USART_Asynchronous_RX_9bit_Enable
}usart_asynchronous_rx_9bits;

typedef enum
{
    USART_Fraiming_Error_Cleared,
    USART_Fraiming_Error_Detected
}usart_fraiming_error;

typedef enum
{
    USART_OverRun_Error_Cleared,
    USART_OverRun_Error_Detected
}usart_over_run_error;

typedef enum
{
    USART_Asyn_8bit_Low_Speed,
    USART_Asyn_8bit_High_Speed,
    USART_Asyn_16bit_Low_Speed,
    USART_Asyn_16bit_High_Speed,
    USART_Syn_8bit,
    USART_Syn_16bit
}usart_baudrate_gen;

typedef union
{
    struct
    {
        usart_fraiming_error     fraiming_error;
        usart_over_run_error     over_run_error;
    };
    uint8 status;
}usart_error_status;

typedef struct
{
    usart_asynchronous_tx               asynchronous_tx;
    usart_asynchronous_tx_interrupt     tx_interrupt;
    usart_asynchronous_tx_9bits         tx_9bits;
    
}usart_tx_conf;

typedef struct
{
    usart_asynchronous_rx               asynchronous_rx;
    usart_asynchronous_rx_interrupt     rx_interrupt;
    usart_asynchronous_rx_9bits         rx_9bits;
    
}usart_rx_conf;

typedef struct
{
    usart_tx_conf                   tx_conf;
    usart_rx_conf                   rx_conf;
    usart_baud_rate_gen             baud_rate_gen;
    usart_error_status              error_status;
    uint16                          baudrate;
    interrupt_priority              priority;
    void (*USART_TX_INTERRUPT_HANDLER)(void);
    void (*USART_RX_INTERRUPT_HANDLER)(void);
    void (*USART_FRAMING_ERROR_HANDLER)(void);
    void (*USART_OVERRUN_ERROR_HANDLER)(void);
}usart_t;

/*Section : Function Declaration*/
STD_ReturnType USART_Async_Init(const usart_t *usart);
STD_ReturnType USART_Async_Deinit(const usart_t *usart);

STD_ReturnType USART_Async_Write_Byte(uint8 value);
STD_ReturnType USART_Async_Write_String(uint16 *value , uint16 length);

STD_ReturnType USART_Async_Read_Byte( uint8 *value);

STD_ReturnType USART_RX_Restart(void);

#endif	/* USART_H */

