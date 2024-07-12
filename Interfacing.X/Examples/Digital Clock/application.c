/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"


STD_ReturnType ret = E_NOT_OK;
uint8 hours = 12 , minuits = 59 ,seconds = 50;
uint8 counter=0;
int main() 
{
    application_initializ();

    while(1)
    {
        for (counter = 0; counter < 50; counter++) 
        {
            ret = gpio_port_wrirte_logic(PORTD_INDEX, 0b11111110);
            ret = gpio_port_wrirte_logic(PORTC_INDEX, (uint8) (hours / 10));
            __delay_us(3333);
            ret = gpio_port_wrirte_logic(PORTD_INDEX, 0b11111101);
            ret = gpio_port_wrirte_logic(PORTC_INDEX, (uint8) (hours % 10));
            __delay_us(3333);
            ret = gpio_port_wrirte_logic(PORTD_INDEX, 0b11111011);
            ret = gpio_port_wrirte_logic(PORTC_INDEX, (uint8) (minuits / 10));
            __delay_us(3333);;
            ret = gpio_port_wrirte_logic(PORTD_INDEX, 0b11110111);
            ret = gpio_port_wrirte_logic(PORTC_INDEX, (uint8) (minuits % 10));
            __delay_us(3333);
            ret = gpio_port_wrirte_logic(PORTD_INDEX, 0b11101111);
            ret = gpio_port_wrirte_logic(PORTC_INDEX, (uint8) (seconds / 10));
            __delay_us(3333);
            ret = gpio_port_wrirte_logic(PORTD_INDEX, 0b11011111);
            ret = gpio_port_wrirte_logic(PORTC_INDEX, (uint8) (seconds % 10));
            __delay_us(3333);
        }
        
        seconds++;
        
        if(seconds == 60)
        {
            seconds=0;
            minuits++;
        }
        if(minuits == 60)
        {
            minuits=0;
            hours++;
        }
        if(hours == 13)
        {
            hours=0;
        }
        
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = gpio_port_direction_init(PORTC_INDEX , GPIO_DIRECTION_OUTPUT);
    ret = gpio_port_direction_init(PORTD_INDEX , GPIO_DIRECTION_OUTPUT);
    
}