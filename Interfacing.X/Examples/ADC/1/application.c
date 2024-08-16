#include "application.h"

void ADC_Interrupt_function(void);

adc_config_t adc1=
{
    .ADC_INTERRUPT_HANDLER = ADC_Interrupt_function, .adc_aquizition_time=ADC_12_TDA, 
    .adc_channel_select=ADC_CHANNEL_AN0, .adc_conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_16, 
    .result_format=ADC_RESULT_FORMAT_RIGHT, .voltage_reference = ADC_VOLTAGE_REFERANCE_DISABLE
};

lcd_4bit lcd_1 =
{
    .lcd_en.port = PORTC_INDEX, .lcd_en.pin = GPIO_PIN0, .lcd_en.direction = GPIO_DIRECTION_OUTPUT, .lcd_en.logic = GPIO_LOW,
    .lcd_rs.port = PORTC_INDEX, .lcd_rs.pin = GPIO_PIN1, .lcd_rs.direction = GPIO_DIRECTION_OUTPUT, .lcd_rs.logic = GPIO_LOW,

    .lcd_data[0].port = PORTC_INDEX, .lcd_data[0].pin = GPIO_PIN2, .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX, .lcd_data[1].pin = GPIO_PIN3, .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX, .lcd_data[2].pin = GPIO_PIN4, .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX, .lcd_data[3].pin = GPIO_PIN5, .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[3].logic = GPIO_LOW
};
       
STD_ReturnType ret = E_NOT_OK;
uint16 res_1;
uint16 result[6];


int main() 
{
    application_initializ();
    ret = lcd_4bit_send_string_pos(&lcd_1 , 1 , 1 ,"POT: ");
            
    while(1)
    {
        ret = ADC_Full_Conversion_Interrupt(&adc1 , ADC_CHANNEL_AN0);
        ret = convert_uint16_to_string(res_1 , result);
        ret = lcd_4bit_send_string_pos(&lcd_1 , 1 , 6 , result);
        
    }


    return (EXIT_SUCCESS);
}

void application_initializ(void)
{
    ret = ADC_Init(&adc1);
    ret = lcd_4bit_init(&lcd_1);
}


void ADC_Interrupt_function()
{
    ret = ADC_Get_Conversion_Result(&adc1 , &res_1);
    
}
