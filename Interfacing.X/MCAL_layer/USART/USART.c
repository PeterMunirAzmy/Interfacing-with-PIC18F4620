/* 
 * File:   USART.c
 * Author: peter
 *
 * Created on September 20, 2024, 10:48 PM
 */

#include "USART.h"

static void USART_Baudrate_Calculation(const usart_t *usart);
static void USART_Enable(void);
static void USART_Disable(void);
static void USART_TX_Init(const usart_t *usart);
static void USART_RX_Init(const usart_t *usart);

static void (*USART_TX_INTERRUPT_HANDLER)(void);
static void (*USART_RX_INTERRUPT_HANDLER)(void);
static void (*USART_FRAMING_ERROR_HANDLER)(void);
static void (*USART_OVERRUN_ERROR_HANDLER)(void);


/**
 * 
 * @param usart
 * @return 
 */
STD_ReturnType USART_Async_Init(const usart_t *usart)
{
    STD_ReturnType ret = E_OK;
    if(NULL == usart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        USART_Disable();
        
        TRISCbits.RC7 = GPIO_DIRECTION_INPUT;
        TRISCbits.RC6 = GPIO_DIRECTION_INPUT;
        
        USART_Baudrate_Calculation(usart);
        
        USART_TX_Init(usart);
        USART_RX_Init(usart);
        
        USART_Enable();
    }
    return ret;
}

/**
 * 
 * @param usart
 * @return 
 */
STD_ReturnType USART_Async_Deinit(const usart_t *usart)
{
    STD_ReturnType ret = E_OK;
    if(NULL == usart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        USART_Disable();
    }
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
STD_ReturnType USART_Async_Write_Byte(uint8 value)
{
    STD_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
    USART_TX_INTERRUPT_ENABLE();
    TXREG = value;
    
    return ret;
}

/**
 * 
 * @param value
 * @param length
 * @return 
 */
STD_ReturnType USART_Async_Write_String(uint16 *value , uint16 length)
{
    STD_ReturnType ret = E_OK;
    
    for(int i =0 ; i < length ; i++)
    {
        ret = USART_Async_Write_Byte(value[i]);
    }
    
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
STD_ReturnType USART_Async_Read_Byte(uint8 *value)
{
    STD_ReturnType ret = E_OK;
    
    if(1 == PIR1bits.RCIF)
    {
        *value = RCREG;
    }
    else
    {
        ret = E_NOT_OK;
    }
    
    return ret;
}

/* --------------- Called in over run error --------------- */
STD_ReturnType USART_RX_Restart(void)
{
    STD_ReturnType ret = E_OK;
    RCSTAbits.CREN = USART_Asynchronous_RX_Disable;
    RCSTAbits.CREN = USART_Asynchronous_RX_Enable;
    return ret;
}

/* -------------------------- Helper Functions -------------------------- */

static void USART_Baudrate_Calculation(const usart_t *usart)
{
    float Baudrate = 0;
    switch(usart->baud_rate_gen)
    {
        case USART_Asyn_8bit_Low_Speed:
            TXSTAbits.SYNC = USART_Asynchronous_Mode;
            TXSTAbits.BRGH = USART_Asynchronous_Low_Speed;
            BAUDCONbits.BRG16 = USART_8Bit_BaudRate_Gen;
            Baudrate = ((_XTAL_FREQ / usart->baudrate )/ 64) - 1;
            break;
            
        case USART_Asyn_8bit_High_Speed:
            TXSTAbits.SYNC = USART_Asynchronous_Mode;
            TXSTAbits.BRGH = USART_Asynchronous_High_Speed;
            BAUDCONbits.BRG16 = USART_8Bit_BaudRate_Gen;
            Baudrate = ((_XTAL_FREQ / usart->baudrate )/ 16) - 1;
            break;
            
        case USART_Asyn_16bit_Low_Speed:
            TXSTAbits.SYNC = USART_Asynchronous_Mode;
            TXSTAbits.BRGH = USART_Asynchronous_Low_Speed;
            BAUDCONbits.BRG16 = USART_16Bit_BaudRate_Gen;
            Baudrate = ((_XTAL_FREQ / usart->baudrate )/ 16) - 1;
            break;
            
        case USART_Asyn_16bit_High_Speed:
            TXSTAbits.SYNC = USART_Asynchronous_Mode;
            TXSTAbits.BRGH = USART_Asynchronous_High_Speed;
            BAUDCONbits.BRG16 = USART_16Bit_BaudRate_Gen;
            Baudrate = ((_XTAL_FREQ / usart->baudrate )/ 4) - 1;
            break;
            
        case USART_Syn_8bit:
            TXSTAbits.SYNC = USART_Synchronous_Mode;
            BAUDCONbits.BRG16 = USART_8Bit_BaudRate_Gen;
            Baudrate = ((_XTAL_FREQ / usart->baudrate )/ 4) - 1;
            break;
            
        case USART_Syn_16bit:
            TXSTAbits.SYNC = USART_Synchronous_Mode;
            BAUDCONbits.BRG16 = USART_16Bit_BaudRate_Gen;
            Baudrate = ((_XTAL_FREQ / usart->baudrate )/ 4) - 1;
            break;
    }
    SPBRG = (uint8)((uint32)Baudrate);
    SPBRGH = (uint8)(((uint32)Baudrate) >> 8);
}

static void USART_Enable(void)
{
    RCSTAbits.SPEN = USART_ENABLE;
}
static void USART_Disable(void)
{
        RCSTAbits.SPEN = USART_DISABLE;
}

static void USART_TX_Init(const usart_t *usart)
{
    if (usart->tx_conf.asynchronous_tx == USART_Asynchronous_TX_Enable) 
    {
        TXSTAbits.TXEN = USART_Asynchronous_TX_Enable;
        switch (usart -> tx_conf.tx_interrupt) 
        {
            case USART_Asynchronous_TX_Interrupt_Enable:
                PIE1bits.TXIE = USART_Asynchronous_TX_Interrupt_Enable;
                USART_TX_INTERRUPT_HANDLER = usart->USART_TX_INTERRUPT_HANDLER;
                USART_TX_INTERRUPT_ENABLE();
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable   
                INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
                switch (usart->priority) 
                {
                    case INTERRUPT_HIGH_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
                        USART_TX_HIGHT_BRIORITY_SET();
                        break;
                    case INTERRUPT_LOW_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
                        USART_TX_LOW_BRIORITY_SET();
                        break; 
                }
#else
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
                INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
#endif
                break;
            case USART_Asynchronous_TX_Interrupt_Disable:
                PIE1bits.TXIE = USART_Asynchronous_TX_Interrupt_Disable;
                break;
        }

        switch (usart -> tx_conf.tx_9bits) 
        {
            case USART_Asynchronous_TX_9bit_Enable:
                TXSTAbits.TX9 = USART_Asynchronous_TX_9bit_Enable;
                break;
            case USART_Asynchronous_TX_9bit_Disable:
                TXSTAbits.TX9 = USART_Asynchronous_TX_9bit_Disable;
                break;
        }
    }
    else
    {/*NoThing*/}
    
}
static void USART_RX_Init(const usart_t *usart)
{
    if (usart->rx_conf.asynchronous_rx == USART_Asynchronous_RX_Enable) 
    {
        RCSTAbits.CREN = USART_Asynchronous_RX_Enable;
        switch (usart -> rx_conf.rx_interrupt) 
        {
            case USART_Asynchronous_RX_Interrupt_Enable:
                PIE1bits.RCIE = USART_Asynchronous_RX_Interrupt_Enable;
                USART_RX_INTERRUPT_ENABLE();
                USART_RX_INTERRUPT_HANDLER = usart->USART_RX_INTERRUPT_HANDLER;
                USART_FRAMING_ERROR_HANDLER = usart->USART_FRAMING_ERROR_HANDLER;
                USART_OVERRUN_ERROR_HANDLER = usart->USART_OVERRUN_ERROR_HANDLER;
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable   
                INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
                switch (usart->priority) 
                {
                    case INTERRUPT_HIGH_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
                        USART_RX_HIGHT_BRIORITY_SET();
                        break;
                    case INTERRUPT_LOW_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
                        USART_RX_LOW_BRIORITY_SET();
                        break; 
                }
#else
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
                INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
#endif
                break;
            case USART_Asynchronous_RX_Interrupt_Disable:
                PIE1bits.RCIE = USART_Asynchronous_RX_Interrupt_Disable;
                break;
        }

        switch (usart -> rx_conf.rx_9bits) 
        {
            case USART_Asynchronous_RX_9bit_Enable:
                RCSTAbits.RX9 = USART_Asynchronous_RX_9bit_Enable;
                break;
            case USART_Asynchronous_RX_9bit_Disable:
                RCSTAbits.RX9 = USART_Asynchronous_RX_9bit_Disable;
                break;
        }
    }
    else
    {/*NoThing*/}
}

void USART_TX_ISR(void)
{
    USART_TX_INTERRUPT_DISABLE();
    if(USART_TX_INTERRUPT_HANDLER)
    {
        USART_TX_INTERRUPT_HANDLER();
    }
}

void USART_RX_ISR(void)
{
    
    if(USART_RX_INTERRUPT_HANDLER)
    {
        USART_RX_INTERRUPT_HANDLER();
    }
    if(USART_FRAMING_ERROR_HANDLER)
    {
        USART_FRAMING_ERROR_HANDLER();
    }
    if(USART_OVERRUN_ERROR_HANDLER)
    {
        USART_OVERRUN_ERROR_HANDLER();
    }
}