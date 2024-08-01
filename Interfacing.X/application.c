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
void ISR_3(void);

interrupt_RBx RB4_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_0,.interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN4,
    .interrupt_pin.direction = GPIO_DIRECTION_INPUT,.priority = INTERRUPT_HIGH_PRIORITY
};

interrupt_RBx RB5_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_1,.interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN5,
    .interrupt_pin.direction = GPIO_DIRECTION_INPUT,.priority = INTERRUPT_LOW_PRIORITY
};

interrupt_RBx RB6_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_2,.interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN6,
    .interrupt_pin.direction = GPIO_DIRECTION_INPUT,.priority = INTERRUPT_LOW_PRIORITY
};

interrupt_RBx RB7_obj =
{
    .EXTERNAL_INTERRUPT_CALLBACK = ISR_3,.interrupt_pin.port = PORTB_INDEX, .interrupt_pin.pin = GPIO_PIN7,
    .interrupt_pin.direction = GPIO_DIRECTION_INPUT,.priority = INTERRUPT_HIGH_PRIORITY
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

pin_config led4 =
{
    .port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW
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
    ret = Interrupt_RBx_init(&RB4_obj);
    ret = Interrupt_RBx_init(&RB5_obj);
    ret = Interrupt_RBx_init(&RB6_obj);
    ret = Interrupt_RBx_init(&RB7_obj);
    
    ret = gpio_pin_Initialization(&led1);
    ret = gpio_pin_Initialization(&led2);
    ret = gpio_pin_Initialization(&led3);
    ret = gpio_pin_Initialization(&led4);

}

void ISR_0(void)
{
    ret = gpio_pin_toggle_logic(&led1);
    //__delay_ms(250);
}

void ISR_1(void)
{
    ret = gpio_pin_toggle_logic(&led2);
    //__delay_ms(250);
}

void ISR_2(void)
{
    ret = gpio_pin_toggle_logic(&led3);
    //__delay_ms(250);
}
void ISR_3(void)
{
    ret = gpio_pin_toggle_logic(&led4);
    //__delay_ms(250);
}