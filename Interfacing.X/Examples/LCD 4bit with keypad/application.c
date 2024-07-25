/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"


keypad_config keypad =
{
    .keypad_rows[0].port=PORTD_INDEX ,.keypad_rows[0].pin=GPIO_PIN0,.keypad_rows[0].direction=GPIO_DIRECTION_OUTPUT,.keypad_rows[0].logic=GPIO_LOW,
    .keypad_rows[1].port=PORTD_INDEX ,.keypad_rows[1].pin=GPIO_PIN1,.keypad_rows[1].direction=GPIO_DIRECTION_OUTPUT,.keypad_rows[1].logic=GPIO_LOW,
    .keypad_rows[2].port=PORTD_INDEX ,.keypad_rows[2].pin=GPIO_PIN2,.keypad_rows[2].direction=GPIO_DIRECTION_OUTPUT,.keypad_rows[2].logic=GPIO_LOW,
    .keypad_rows[3].port=PORTD_INDEX ,.keypad_rows[3].pin=GPIO_PIN3,.keypad_rows[3].direction=GPIO_DIRECTION_OUTPUT,.keypad_rows[3].logic=GPIO_LOW,
    
    .keypad_colums[0].port=PORTD_INDEX ,.keypad_colums[0].pin=GPIO_PIN4,.keypad_colums[0].direction=GPIO_DIRECTION_INPUT,.keypad_colums[0].logic=GPIO_LOW,
    .keypad_colums[1].port=PORTD_INDEX ,.keypad_colums[1].pin=GPIO_PIN5,.keypad_colums[1].direction=GPIO_DIRECTION_INPUT,.keypad_colums[1].logic=GPIO_LOW,
    .keypad_colums[2].port=PORTD_INDEX ,.keypad_colums[2].pin=GPIO_PIN6,.keypad_colums[2].direction=GPIO_DIRECTION_INPUT,.keypad_colums[2].logic=GPIO_LOW,
    .keypad_colums[3].port=PORTD_INDEX ,.keypad_colums[3].pin=GPIO_PIN7,.keypad_colums[3].direction=GPIO_DIRECTION_INPUT,.keypad_colums[3].logic=GPIO_LOW
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
        
STD_ReturnType ret = E_NOT_OK;
uint8 value;

int main() 
{
    application_initializ();
    keypad_get_value(&keypad , &value);
    
    ret = lcd_4bit_send_string_pos(&lcd2 , 1 , 1 , "Reading");
    ret = lcd_4bit_send_string_pos(&lcd2 , 2 , 1 , &value);
    while(1)
    {
        ret = keypad_get_value(&keypad , &value);
    
        ret = lcd_4bit_send_string_pos(&lcd2 , 1 , 1 , "Reading");
        ret = lcd_4bit_send_string_pos(&lcd2 , 2 , 1 , &value);
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = keypad_initialize(&keypad);
    ret = lcd_4bit_init(&lcd2);
}