#include "application.h"


void Timer1_Interrupt_function(void);
void application_initializ(void);

timer1_t counter1 =
{
    .Timer1_Interrupt_Handlar = Timer1_Interrupt_function ,.mode = Timer1_Counter_Mode , .preloaded_value =15535,
    .timer1_OSC = Timer1_OSC_Disable,.register_size = Timer1_16Bit_Register,.prescaler_value = Timer1_Prescaler_Dev_8,
    .clock_status=Timer1_Clock_Asynchronous, .priority=INTERRUPT_LOW_PRIORITY
};
    
STD_ReturnType ret = E_NOT_OK;
volatile uint16 counter_value , val;

int main() 
{
    application_initializ();
    
    while (1) 
    {
        ret = Timer1_Read_Value(&counter1 , &counter_value);
    }
    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = Timer1_Init(&counter1);
}


void Timer1_Interrupt_function(void) 
{
    val++;
}
