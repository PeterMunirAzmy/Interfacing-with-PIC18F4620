/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"
#include "ECU_layer/Keypad/keypad.h"

keypad_config keypad =
{
    .keypad_rows[0].port = PORTC_INDEX ,.keypad_rows[0].pin = GPIO_PIN0,.keypad_rows[0].direction = GPIO_DIRECTION_OUTPUT,.keypad_rows[0].logic=GPIO_LOW,
    .keypad_rows[1].port = PORTC_INDEX ,.keypad_rows[1].pin = GPIO_PIN1,.keypad_rows[1].direction = GPIO_DIRECTION_OUTPUT,.keypad_rows[1].logic=GPIO_LOW,
    .keypad_rows[2].port = PORTC_INDEX ,.keypad_rows[2].pin = GPIO_PIN2,.keypad_rows[2].direction = GPIO_DIRECTION_OUTPUT,.keypad_rows[2].logic=GPIO_LOW,
    .keypad_rows[3].port = PORTC_INDEX ,.keypad_rows[3].pin = GPIO_PIN3,.keypad_rows[3].direction = GPIO_DIRECTION_OUTPUT,.keypad_rows[3].logic=GPIO_LOW,
    
    .keypad_colums[0].port = PORTC_INDEX ,.keypad_colums[0].pin = GPIO_PIN4,.keypad_colums[0].direction = GPIO_DIRECTION_INPUT,.keypad_colums[0].logic=GPIO_LOW,
    .keypad_colums[1].port = PORTC_INDEX ,.keypad_colums[1].pin = GPIO_PIN5,.keypad_colums[1].direction = GPIO_DIRECTION_INPUT,.keypad_colums[1].logic=GPIO_LOW,
    .keypad_colums[2].port = PORTC_INDEX ,.keypad_colums[2].pin = GPIO_PIN6,.keypad_colums[2].direction = GPIO_DIRECTION_INPUT,.keypad_colums[2].logic=GPIO_LOW,
    .keypad_colums[3].port = PORTC_INDEX ,.keypad_colums[3].pin = GPIO_PIN7,.keypad_colums[3].direction = GPIO_DIRECTION_INPUT,.keypad_colums[3].logic=GPIO_LOW
};

seg_config seg =
{
    ._seg_pin[seg_pin0].port = PORTD_INDEX, ._seg_pin[seg_pin0].pin = GPIO_PIN0, ._seg_pin[seg_pin0].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin0].logic = GPIO_LOW, 
    ._seg_pin[seg_pin1].port = PORTD_INDEX, ._seg_pin[seg_pin1].pin = GPIO_PIN1, ._seg_pin[seg_pin1].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin1].logic = GPIO_LOW,
    ._seg_pin[seg_pin2].port = PORTD_INDEX, ._seg_pin[seg_pin2].pin = GPIO_PIN2, ._seg_pin[seg_pin2].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin2].logic = GPIO_LOW,
    ._seg_pin[seg_pin3].port = PORTD_INDEX, ._seg_pin[seg_pin3].pin = GPIO_PIN3, ._seg_pin[seg_pin3].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin3].logic = GPIO_LOW 
};
        
STD_ReturnType ret = E_NOT_OK;
uint8 value;
uint8 num_value = 0;

int main() 
{
    application_initializ();

    while(1)
    {
        ret = keypad_get_value(&keypad ,&value);
        
        __delay_ms(100);
        if (value >= '0' && value <= '9') 
        {
            num_value = value - '0'; // Convert char '0'-'9' to 0-9
        } 
        else 
        {
            num_value = 0x0F;
        }
        
        ret = seg_write_number(&seg , (uint8)num_value);
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = keypad_initialize(&keypad);
    ret = seg_initialization(&seg);
    
}