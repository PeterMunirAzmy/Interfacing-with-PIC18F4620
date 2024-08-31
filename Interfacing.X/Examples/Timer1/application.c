#include "application.h"


void Timer1_Interrupt_function(void);
void application_initializ(void);

timer1_t timer1 =
{
    .Timer1_Interrupt_Handlar = Timer1_Interrupt_function ,.mode = Timer1_Timer_Mode , .preloaded_value = 15536, 
    .register_size = Timer1_16Bit_Register, .prescaler_value = Timer1_Prescaler_Dev_4,
    .clock_status=Timer1_Clock_Asynchronous ,.timer1_OSC = Timer1_OSC_Disable
};


led_config led1 = 
{.port_name=PORTC_INDEX, .pin_number = GPIO_PIN0, .led_status = LED_OFF};
       
STD_ReturnType ret = E_NOT_OK;
volatile uint16 flag =0;
int main() 
{
    application_initializ();
    
    while (1) 
    {
        
    }
    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = Timer1_Init(&timer1);
    ret = ecu_led_initializ(&led1);
}


void Timer1_Interrupt_function(void) 
{
    ret = ecu_led_toggle(&led1);
}
