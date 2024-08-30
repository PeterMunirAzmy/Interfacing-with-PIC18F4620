#include "application.h"

void ADC_Interrupt_function(void);
void application_initializ(void);

timer0_t timer0 =
{
    .Timer0_Interrupt_Handlar = ADC_Interrupt_function ,.mode = Timer0_Timer_Mode , .preloaded_value = 3036, 
    .prescaler_status = Timer0_Prescaler_Enable,.register_size = Timer0_16Bit_Register,
    .prescaler_value = Timer0_Prescaler_Dev_8
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
    ret = Timer0_Init(&timer0);
    ret = ecu_led_initializ(&led1);
}


void ADC_Interrupt_function(void) 
{
    flag++;
    ret = ecu_led_toggle(&led1);
}
