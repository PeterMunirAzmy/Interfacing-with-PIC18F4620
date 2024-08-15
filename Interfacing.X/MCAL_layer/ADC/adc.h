/* 
 * File:   adc.h
 * Author: peter
 *
 * Created on August 11, 2024, 3:46 PM
 */

#ifndef ADC_H
#define	ADC_H

/*Section : Includes*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../compiler.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"
#include "../Interrupt/interrupt_manager.h"


/*Section : Macro Declaration*/
#define ADC_RESULT_FORMAT_RIGHT             0x01
#define ADC_RESULT_FORMAT_LEFT              0x00                   

#define ADC_VOLTAGE_REFERANCE_ENABLE        0x01
#define ADC_VOLTAGE_REFERANCE_DISABLE       0x00

/*Section : Macro Function Declaration*/
#define ADC_CONVERSION_STATUS()             (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERSION()              (ADCON0bits.GO_nDONE = 1)

#define ADC_CONVERTER_DISABLE()             (ADCON0bits.ADON = 0)
#define ADC_CONVERTER_ENABLE()              (ADCON0bits.ADON = 1)

/* Voltage Reference is Vref+ "on AN3" Vref- "on AN2" */
#define ADC_ENABLE_VOLTAGE_DIFFERANCE()     do{ADCON1bits.VCFG1=1;\
                                               ADCON1bits.VCFG0=1;}\
                                               while(0)

/* Voltage Reference is Vss and Vdd */
#define ADC_DISABLE_VOLTAGE_DIFFERANCE()    do{ADCON1bits.VCFG1=0;\
                                               ADCON1bits.VCFG0=0;}\
                                               while(0)

#define ADC_ANALOG_OR_DIGITAL_CONFIGURATION(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

#define ADC_RESULT_RIGHT_FORMAT()           (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()            (ADCON2bits.ADFM = 0)

          

/*Section : Data Type Declaration*/
typedef enum
{
    ADC_CHANNEL_AN0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
      
}adc_channel_select_t;

/* when you use ADC_AN4_ANALOG_FUNCTIONALITY that mean that AN0 , AN1 ,AN2 ,AN3 and AN4 will be analog pins*/
typedef enum
{
    ADC_ALL_ANALOG_FUNCTIONALITY = 0x01,
    ADC_AN12_ANALOG_FUNCTIONALITY,
    ADC_AN11_ANALOG_FUNCTIONALITY,
    ADC_AN10_ANALOG_FUNCTIONALITY,
    ADC_AN9_ANALOG_FUNCTIONALITY,
    ADC_AN8_ANALOG_FUNCTIONALITY,
    ADC_AN7_ANALOG_FUNCTIONALITY,
    ADC_AN6_ANALOG_FUNCTIONALITY,
    ADC_AN5_ANALOG_FUNCTIONALITY,
    ADC_AN4_ANALOG_FUNCTIONALITY,
    ADC_AN3_ANALOG_FUNCTIONALITY,
    ADC_AN2_ANALOG_FUNCTIONALITY,
    ADC_AN1_ANALOG_FUNCTIONALITY,
    ADC_AN0_ANALOG_FUNCTIONALITY,
    ADC_ALL_DIGITAL_FUNCTIONALITY
      
}adc_analog_functionality_t;

typedef enum
{
    ADC_0_TDA,
    ADC_2_TDA,
    ADC_4_TDA,
    ADC_6_TDA,
    ADC_8_TDA,
    ADC_12_TDA,
    ADC_16_TDA,
    ADC_20_TDA
      
}adc_aquizition_time_t;

typedef enum
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
      
}adc_conversion_clock_t;

typedef struct
{
    void (* ADC_INTERRUPT_HANDLER)(void);
    interrupt_priority priority;
    adc_conversion_clock_t adc_conversion_clock;
    adc_aquizition_time_t adc_aquizition_time;
    adc_analog_functionality_t adc_analog_functionality;
    adc_channel_select_t adc_channel_select;
    uint8 voltage_reference ;
    uint8 result_format ;
}adc_config_t;

/*Section : Function Declaration*/
STD_ReturnType ADC_Init(const adc_config_t *adc_config);
STD_ReturnType ADC_Deinit(const adc_config_t *adc_config);
STD_ReturnType ADC_Select_Channel(const adc_config_t *adc_config , adc_channel_select_t adc_channel_select);
STD_ReturnType ADC_Start_Conversion(const adc_config_t *adc_config);
STD_ReturnType ADC_Is_Conversion_Done(const adc_config_t *adc_config , uint8 *conversion_status);
STD_ReturnType ADC_Get_Conversion_Result(const adc_config_t *adc_config , uint16 *conversion_result);
STD_ReturnType ADC_Full_Conversion_Pending(const adc_config_t *adc_config , adc_channel_select_t adc_channel_select, uint16 *conversion_result);
STD_ReturnType ADC_Full_Conversion_Interrupt(const adc_config_t *adc_config , adc_channel_select_t adc_channel_select);



#endif	/* ADC_H */

