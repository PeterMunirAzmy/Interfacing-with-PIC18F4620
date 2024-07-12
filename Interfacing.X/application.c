/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"


seg_config seg1 =
{
    ._seg_pin[seg_pin0].port = PORTC_INDEX, ._seg_pin[seg_pin0].pin = GPIO_PIN0, ._seg_pin[seg_pin0].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin0].logic = GPIO_LOW,
    ._seg_pin[seg_pin1].port = PORTC_INDEX, ._seg_pin[seg_pin1].pin = GPIO_PIN1, ._seg_pin[seg_pin1].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin1].logic = GPIO_LOW,
    ._seg_pin[seg_pin2].port = PORTC_INDEX, ._seg_pin[seg_pin2].pin = GPIO_PIN2, ._seg_pin[seg_pin2].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin2].logic = GPIO_LOW,
    ._seg_pin[seg_pin3].port = PORTC_INDEX, ._seg_pin[seg_pin3].pin = GPIO_PIN3, ._seg_pin[seg_pin3].direction = GPIO_DIRECTION_OUTPUT, ._seg_pin[seg_pin3].logic = GPIO_LOW,
};
STD_ReturnType ret = E_NOT_OK;

int main() 
{
    application_initializ();

    while(1)
    {
        ret = seg_write_number(&seg1 , 5);
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = seg_initialization(&seg1);
    
}