/* 
 * File:   adc.c
 * Author: peter
 *
 * Created on August 11, 2024, 3:46 PM
 */

#include "adc.h"

static void (*ADC_InterruptHandler)(void) = NULL;
static inline void ADC_Voltage_Reference_Configuration(const adc_config_t *adc_config);
static inline void ADC_Result_Format_Configuration(const adc_config_t *adc_config);
static inline void ADC_Input_Channel_Port_Configuration(adc_channel_select_t adc_channel_select);


/**
 * 
 * @param adc_config
 * @return 
 */
STD_ReturnType ADC_Init(const adc_config_t *adc_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == adc_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable the ADC */
        ADC_CONVERTER_DISABLE();
        
        /* configuration the acquisition time */
        ADCON2bits.ACQT = adc_config->adc_aquizition_time;
        
        /* configuration the conversion clock */
        ADCON2bits.ADCS = adc_config->adc_conversion_clock;
        
        /* configuration the default channel and make its pin as an input pin */
        ADCON0bits.CHS = adc_config->adc_channel_select;
        ADC_Input_Channel_Port_Configuration(adc_config->adc_channel_select);
        
        /* configuration the interrupt */
        INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
        INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_FLAG_CLEAR();
        switch(adc_config->priority)
        {
            case INTERRUPT_HIGH_PRIORITY :
                ADC_HIGHT_BRIORITY_SET();
                break;
            case INTERRUPT_LOW_PRIORITY :
                ADC_LOW_BRIORITY_SET();
                break;
        }
        ADC_InterruptHandler = adc_config->ADC_INTERRUPT_HANDLER;
        /* configuration the result format */
        ADC_Result_Format_Configuration(adc_config);
        
        /* configuration the voltage reference */
        ADC_Voltage_Reference_Configuration(adc_config);
        /* enable the ADC */
        ADC_CONVERTER_ENABLE();

    }
    return ret; 
}

/**
 * 
 * @param adc_config
 * @return 
 */
STD_ReturnType ADC_Deinit(const adc_config_t *adc_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == adc_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable the ADC */
        ADC_CONVERTER_DISABLE();
        ADC_INTERRUPT_DISABLE();
    }
    return ret; 
}

/**
 * 
 * @param adc_config
 * @param adc_channel_select
 * @return 
 */
STD_ReturnType ADC_Select_Channel(const adc_config_t *adc_config , adc_channel_select_t adc_channel_select)
{
    STD_ReturnType ret = E_OK;
    if(NULL == adc_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* configuration the default channel and make its pin as an input pin */
        ADCON0bits.CHS = adc_channel_select;
        ADC_Input_Channel_Port_Configuration(adc_channel_select);
    }
    return ret; 
}

/**
 * 
 * @param adc_config
 * @return 
 */
STD_ReturnType ADC_Start_Conversion(const adc_config_t *adc_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == adc_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
    }
    return ret; 
}

/**
 * 
 * @param adc_config
 * @param conversion_status
 * @return 
 */
STD_ReturnType ADC_Is_Conversion_Done(const adc_config_t *adc_config , uint8 *conversion_status)
{
    STD_ReturnType ret = E_OK;
    if((NULL == adc_config) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = !(ADCON0bits.GO_nDONE);
    }
    return ret; 
}

/**
 * 
 * @param adc_config
 * @param conversion_result
 * @return 
 */
STD_ReturnType ADC_Get_Conversion_Result(const adc_config_t *adc_config , uint16 *conversion_result)
{
    STD_ReturnType ret = E_OK;
    if((NULL == adc_config) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(adc_config->result_format)
        {
        case ADC_RESULT_FORMAT_RIGHT:
            *conversion_result =  (uint16)((ADRESH << 8) + ADRESL );
            break;
        case ADC_RESULT_FORMAT_LEFT:
            *conversion_result =  (uint16)(((ADRESH << 8) + ADRESL) >> 6);
            break;
        default:
            *conversion_result =  (uint16)(ADRESL +  (ADRESH << 8));
            break;            
        }
        
    }
    return ret;
}

/**
 * 
 * @param adc_config
 * @param conversion_status
 * @param adc_channel_select
 * @param conversion_result
 * @return 
 */
STD_ReturnType ADC_Full_Conversion_Pending(const adc_config_t *adc_config , adc_channel_select_t adc_channel_select,
                                           uint16 *conversion_result)
{
    STD_ReturnType ret = E_OK;
    
    if((NULL == adc_config) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if((ret = ADC_Select_Channel(adc_config , adc_channel_select)) == E_OK)
        {
            if((ret = ADC_Start_Conversion(adc_config)) == E_OK)
            {
                while(ADCON0bits.GO_nDONE);
                ret = ADC_Get_Conversion_Result(adc_config , conversion_result);
            }
        }
    }
    return ret;
}

/**
 * 
 * @param adc_config
 * @param adc_channel_select
 * @return 
 */
STD_ReturnType ADC_Full_Conversion_Interrupt(const adc_config_t *adc_config , adc_channel_select_t adc_channel_select)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == adc_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = ADC_Select_Channel(adc_config , adc_channel_select);
        ret = ADC_Start_Conversion(adc_config);
        
    }
    return ret;
}

/* -------------------- Helper Functions -------------------- */

static inline void ADC_Input_Channel_Port_Configuration(adc_channel_select_t adc_channel_select)
{
    switch(adc_channel_select)
    {
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1:
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3:
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4:
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5:
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7:
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8:
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9:
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11:
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        
    }
}

static inline void ADC_Voltage_Reference_Configuration(const adc_config_t *adc_config)
{
    switch(adc_config->voltage_reference)
    {
        case ADC_VOLTAGE_REFERANCE_ENABLE:
            ADC_ENABLE_VOLTAGE_DIFFERANCE();
            break;
        case ADC_VOLTAGE_REFERANCE_DISABLE:
            ADC_DISABLE_VOLTAGE_DIFFERANCE();
            break;
        default:
            ADC_DISABLE_VOLTAGE_DIFFERANCE();
            break;            
    }
}

static inline void ADC_Result_Format_Configuration(const adc_config_t *adc_config)
{
    switch(adc_config->result_format)
    {
        case ADC_RESULT_FORMAT_RIGHT:
            ADC_RESULT_RIGHT_FORMAT();
            break;
        case ADC_RESULT_FORMAT_LEFT:
            ADC_RESULT_LEFT_FORMAT();
            break;
        default:
            ADC_RESULT_RIGHT_FORMAT();
            break;            
    }
}

void ADC_ISR(void)
{
    ADC_INTERRUPT_FLAG_CLEAR();
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}