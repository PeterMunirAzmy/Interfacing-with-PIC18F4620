/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"

lcd_8bit lcd1 =
{
    .lcd_en.port=PORTC_INDEX ,.lcd_en.pin=GPIO_PIN0 ,.lcd_en.direction=GPIO_DIRECTION_OUTPUT ,.lcd_en.logic=GPIO_LOW,
    .lcd_rs.port=PORTC_INDEX ,.lcd_rs.pin=GPIO_PIN1 ,.lcd_rs.direction=GPIO_DIRECTION_OUTPUT ,.lcd_rs.logic=GPIO_LOW,
    
    .lcd_data[0].port=PORTD_INDEX ,.lcd_data[0].pin=GPIO_PIN0 ,.lcd_data[0].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[0].logic=GPIO_LOW,
    .lcd_data[1].port=PORTD_INDEX ,.lcd_data[1].pin=GPIO_PIN1 ,.lcd_data[1].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[1].logic=GPIO_LOW,
    .lcd_data[2].port=PORTD_INDEX ,.lcd_data[2].pin=GPIO_PIN2 ,.lcd_data[2].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[2].logic=GPIO_LOW,
    .lcd_data[3].port=PORTD_INDEX ,.lcd_data[3].pin=GPIO_PIN3 ,.lcd_data[3].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[3].logic=GPIO_LOW,
    .lcd_data[4].port=PORTD_INDEX ,.lcd_data[4].pin=GPIO_PIN4 ,.lcd_data[4].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[4].logic=GPIO_LOW,
    .lcd_data[5].port=PORTD_INDEX ,.lcd_data[5].pin=GPIO_PIN5 ,.lcd_data[5].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[5].logic=GPIO_LOW,
    .lcd_data[6].port=PORTD_INDEX ,.lcd_data[6].pin=GPIO_PIN6 ,.lcd_data[6].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[6].logic=GPIO_LOW,
    .lcd_data[7].port=PORTD_INDEX ,.lcd_data[7].pin=GPIO_PIN7 ,.lcd_data[7].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[7].logic=GPIO_LOW
};

lcd_4bit lcd2 =
{
    .lcd_en.port=PORTC_INDEX ,.lcd_en.pin=GPIO_PIN2 ,.lcd_en.direction=GPIO_DIRECTION_OUTPUT ,.lcd_en.logic=GPIO_LOW,
    .lcd_rs.port=PORTC_INDEX ,.lcd_rs.pin=GPIO_PIN3 ,.lcd_rs.direction=GPIO_DIRECTION_OUTPUT ,.lcd_rs.logic=GPIO_LOW,
    
    .lcd_data[0].port=PORTC_INDEX ,.lcd_data[0].pin=GPIO_PIN4 ,.lcd_data[0].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[0].logic=GPIO_LOW,
    .lcd_data[1].port=PORTC_INDEX ,.lcd_data[1].pin=GPIO_PIN5 ,.lcd_data[1].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[1].logic=GPIO_LOW,
    .lcd_data[2].port=PORTC_INDEX ,.lcd_data[2].pin=GPIO_PIN6 ,.lcd_data[2].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[2].logic=GPIO_LOW,
    .lcd_data[3].port=PORTC_INDEX ,.lcd_data[3].pin=GPIO_PIN7 ,.lcd_data[3].direction=GPIO_DIRECTION_OUTPUT ,.lcd_data[3].logic=GPIO_LOW
    
};

uint8 customChar[] = {
  0x00,
  0x1B,
  0x15,
  0x11,
  0x0A,
  0x04,
  0x00,
  0x00
};

STD_ReturnType ret = E_NOT_OK;

int main() 
{
    application_initializ();
    
    ret = lcd_8bit_send_custom_char(&lcd1 , 1 , 1 , &customChar , 1);

    while(1)
    {
        
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = lcd_4bit_init(&lcd2);
    ret = lcd_8bit_init(&lcd1);
}