#include "application.h"

led_config led1 = 
{.port_name=PORTC_INDEX, .pin_number = GPIO_PIN0, .led_status = LED_OFF};

led_config led2 = 
{.port_name=PORTC_INDEX, .pin_number = GPIO_PIN1, .led_status = LED_OFF};

button_config btn = 
{.button_pin.pin = GPIO_PIN2, .button_pin.port=PORTC_INDEX, .button_pin.direction = GPIO_DIRECTION_INPUT,
 ._button_activ = BUTTON_ACTIVE_HIGHT, ._button_status = BUTTON_RELEASED};

STD_ReturnType ret = E_NOT_OK;
uint8 counter = 0, high_value = 0, ret_data = 0, btn_state, prev_btn_state = BUTTON_RELEASED;

void application_initializ(void)
{
    ret = ecu_led_initializ(&led1);
    ret = ecu_led_initializ(&led2);
    ret = ecu_button_init(&btn);
    
    // Read the last stored state from EEPROM
    ret = EEPROM_Data_Read_Byte(0x3FF, &ret_data);
    
    // Update the counter and LED states according to the stored value
    counter = ret_data;
    switch(counter)
    {
        case 1:
            ecu_led_turn_on(&led1);
            ecu_led_turn_off(&led2);
            break;
        case 2:
            ecu_led_turn_on(&led2);
            ecu_led_turn_off(&led1);
            break;
        case 3:
            ecu_led_turn_off(&led1);
            ecu_led_turn_off(&led2);
            counter = 0;  // Reset counter for the next cycle
            break;
        default:
            // If EEPROM data is invalid, reset everything
            ecu_led_turn_off(&led1);
            ecu_led_turn_off(&led2);
            counter = 0;
            break;
    }
}

int main() 
{
    application_initializ();
    
    while(1)
    {
        ret = ecu_button_read_state(&btn, &btn_state);
        
        // Simple debounce logic
        if (btn_state == BUTTON_PRESSED && prev_btn_state == BUTTON_RELEASED) 
        {
            high_value++;
            prev_btn_state = BUTTON_PRESSED;
        } 
        else if (btn_state == BUTTON_RELEASED && prev_btn_state == BUTTON_PRESSED) 
        {
            prev_btn_state = BUTTON_RELEASED;
        }
        
        if (high_value >= 1)
        {
            high_value = 0;
            counter++;
            if (counter > 3)
            {
                counter = 1;  // Wrap around to first state
            }
            ret = EEPROM_Data_Write_Byte(0x3FF, counter);  // Store the new state
        }
        
        // Update LEDs based on the counter value
        switch(counter)
        {
            case 1:
                ecu_led_turn_on(&led1);
                ecu_led_turn_off(&led2);
                break;
            case 2:
                ecu_led_turn_on(&led2);
                ecu_led_turn_off(&led1);
                break;
            case 3:
                ecu_led_turn_off(&led1);
                ecu_led_turn_off(&led2);
                break;
        }
    }

    return (EXIT_SUCCESS);
}
