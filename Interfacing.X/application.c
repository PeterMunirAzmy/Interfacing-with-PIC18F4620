#include "application.h"


void Timer3_Interrupt_function(void);

timer3_t timer3=
{
    .Timer3_Interrupt_Handlar = Timer3_Interrupt_function ,.mode = Timer3_Counter_Mode, .preloaded_value =15536,
    .register_size = Timer3_16Bit_Register,.prescaler_value = Timer3_Prescaler_Dev_8,
    .clock_status=Timer3_Clock_Asynchronous, .priority=INTERRUPT_LOW_PRIORITY
};
    
STD_ReturnType ret = E_NOT_OK;
volatile uint16 counter_value;

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
    ret = Timer3_Init(&timer3);
}


void Timer3_Interrupt_function(void) 
{
    counter_value++;
}
