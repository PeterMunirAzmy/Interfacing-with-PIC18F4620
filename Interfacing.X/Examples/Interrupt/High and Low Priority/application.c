/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"
#include "MCAL_layer/Interrupt/external_interrupt.h"

void ISR_0(void);
void ISR_1(void);
void ISR_2(void);

interrupt_INTx into_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_0, .INTx = INTERRUPT_EXTERNAL_INT0, .edge = INTERRUPT_RISING_EDGE,
    .interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN0, .interrupt_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_INTx int1_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_1, .INTx = INTERRUPT_EXTERNAL_INT1, .edge = INTERRUPT_RISING_EDGE,.priority = INTERRUPT_LOW_PRIORITY,
    .interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN1, .interrupt_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_INTx int2_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_2, .INTx = INTERRUPT_EXTERNAL_INT2, .edge = INTERRUPT_RISING_EDGE,.priority = INTERRUPT_HIGH_PRIORITY,
    .interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN2, .interrupt_pin.direction = GPIO_DIRECTION_INPUT
};

pin_config led1 =
{
    .port = PORTC_INDEX, .pin = GPIO_PIN0, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW
};

pin_config led2 =
{
    .port = PORTC_INDEX, .pin = GPIO_PIN1, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW
};

pin_config led3 =
{
    .port = PORTC_INDEX, .pin = GPIO_PIN2, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW
};

STD_ReturnType ret = E_NOT_OK;

int main() 
{
    application_initializ();
    
    while(1)
    {
        
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = Interrupt_INTx_init(&into_obj);
    ret = Interrupt_INTx_init(&int1_obj);
    ret = Interrupt_INTx_init(&int2_obj);
    
    ret = gpio_pin_Initialization(&led1);
    ret = gpio_pin_Initialization(&led2);
    ret = gpio_pin_Initialization(&led3);
}

void ISR_0(void)
{
    ret = gpio_pin_toggle_logic(&led1);
    __delay_ms(250);
}

void ISR_1(void)
{
    ret = gpio_pin_toggle_logic(&led2);
    __delay_ms(250);
}

void ISR_2(void)
{
    ret = gpio_pin_toggle_logic(&led3);
    __delay_ms(250);
}