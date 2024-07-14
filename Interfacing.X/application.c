/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"
#include "ECU_layer/Keypad/keypad.h"

uint8 keypad_value = 0;

keypad_config keypad_1 =
{
    .keypad_rows[0].port=PORTC_INDEX, .keypad_rows[0].pin=GPIO_PIN0,.keypad_rows[0].direction=GPIO_DIRECTION_OUTPUT, .keypad_rows[0].logic=GPIO_LOW ,
    .keypad_rows[1].port=PORTC_INDEX, .keypad_rows[1].pin=GPIO_PIN1,.keypad_rows[1].direction=GPIO_DIRECTION_OUTPUT, .keypad_rows[1].logic=GPIO_LOW ,
    .keypad_rows[2].port=PORTC_INDEX, .keypad_rows[2].pin=GPIO_PIN2,.keypad_rows[2].direction=GPIO_DIRECTION_OUTPUT, .keypad_rows[2].logic=GPIO_LOW ,
    .keypad_rows[3].port=PORTC_INDEX, .keypad_rows[3].pin=GPIO_PIN3,.keypad_rows[3].direction=GPIO_DIRECTION_OUTPUT, .keypad_rows[3].logic=GPIO_LOW ,
    
    .keypad_colums[0].port=PORTC_INDEX, .keypad_colums[0].pin=GPIO_PIN4,.keypad_colums[0].direction=GPIO_DIRECTION_INPUT, .keypad_colums[0].logic=GPIO_LOW,
    .keypad_colums[1].port=PORTC_INDEX, .keypad_colums[1].pin=GPIO_PIN5,.keypad_colums[1].direction=GPIO_DIRECTION_INPUT, .keypad_colums[1].logic=GPIO_LOW,
    .keypad_colums[2].port=PORTC_INDEX, .keypad_colums[2].pin=GPIO_PIN6,.keypad_colums[2].direction=GPIO_DIRECTION_INPUT, .keypad_colums[2].logic=GPIO_LOW,
    .keypad_colums[3].port=PORTC_INDEX, .keypad_colums[3].pin=GPIO_PIN7,.keypad_colums[3].direction=GPIO_DIRECTION_INPUT, .keypad_colums[3].logic=GPIO_LOW  
};
STD_ReturnType ret = E_NOT_OK;

int main() 
{
    application_initializ();

    while(1)
    {
        ret = keypad_get_value(&keypad_1 , &keypad_value);
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = keypad_initialize(&keypad_1);
    
}