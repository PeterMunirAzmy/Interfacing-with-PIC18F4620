#include "application.h"


void Timer3_Interrupt_function(void);

timer3_t timer3=
{
    .Timer3_Interrupt_Handlar = Timer3_Interrupt_function ,.mode = Timer3_Counter_Mode, .preloaded_value =15536,
    .register_size = Timer3_16Bit_Register,.prescaler_value = Timer3_Prescaler_Dev_8,
    .clock_status=Timer3_Clock_Asynchronous, .priority=INTERRUPT_LOW_PRIORITY
};

led_config led1 = 
{.port_name=PORTC_INDEX, .pin_number = GPIO_PIN0, .led_status = LED_OFF};
    
STD_ReturnType ret = E_NOT_OK;
volatile uint16 counter_value;

int main() 
{
    application_initialize();
    
    while (1) 
    {
        
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void)
{
    ret = Timer3_Init(&timer3);
    ret = ecu_led_initialize(&led1);
}


void Timer3_Interrupt_function(void) 
{
    ret = ecu_led_toggle(&led1);
}
