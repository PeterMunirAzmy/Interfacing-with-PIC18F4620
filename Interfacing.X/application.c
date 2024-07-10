/* 
 * File:   application.c
 * Author: peter
 *
 * Created on July 1, 2024, 3:02 AM
 */

#include "application.h"
#include "ECU_layer/relay/relay.h"

/*
led_config led_1 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN0, .led_status = GPIO_LOW};
led_config led_2 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN1, .led_status = GPIO_LOW};
led_config led_3 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN2, .led_status = GPIO_LOW};
led_config led_4 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN3, .led_status = GPIO_LOW};
led_config led_5 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN4, .led_status = GPIO_LOW};
led_config led_6 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN5, .led_status = GPIO_LOW};
led_config led_7 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN6, .led_status = GPIO_LOW};
led_config led_8 = {.port_name = PORTD_INDEX, .pin_number = GPIO_PIN7, .led_status = GPIO_LOW};
*/

relay_config relay_1 = {.relay_port = PORTD_INDEX, .relay_pin = GPIO_PIN0, .relay_status = GPIO_LOW};

STD_ReturnType ret = E_NOT_OK;

int main() 
{
    application_initializ();

    while(1)
    {
    /*
        ret = ecu_led_turn_on(&led_1);
        ret = ecu_led_turn_on(&led_2);
        ret = ecu_led_turn_on(&led_3);
        ret = ecu_led_turn_on(&led_4);
        ret = ecu_led_turn_on(&led_5);
        ret = ecu_led_turn_on(&led_6);
        ret = ecu_led_turn_on(&led_7);
        ret = ecu_led_turn_on(&led_8);
        _delay(200);
        ret = ecu_led_turn_off(&led_1);
        ret = ecu_led_turn_off(&led_2);
        ret = ecu_led_turn_off(&led_3);
        ret = ecu_led_turn_off(&led_4);
        ret = ecu_led_turn_off(&led_5);
        ret = ecu_led_turn_off(&led_6);
        ret = ecu_led_turn_off(&led_7);
        ret = ecu_led_turn_off(&led_8);
        _delay(200);
    */
        
        ret = ecu_relay_turn_on(&relay_1);
        //_delay(5000);
        //ret = ecu_relay_turn_off(&relay_1);
        //_delay(5000);
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    /* 
    ret = ecu_led_initializ(&led_1);
    ret = ecu_led_initializ(&led_2);
    ret = ecu_led_initializ(&led_3);
    ret = ecu_led_initializ(&led_4);
    ret = ecu_led_initializ(&led_5);
    ret = ecu_led_initializ(&led_6);
    ret = ecu_led_initializ(&led_7);
    ret = ecu_led_initializ(&led_8);
    */
    ret = ecu_relay_initializ(&relay_1);
}