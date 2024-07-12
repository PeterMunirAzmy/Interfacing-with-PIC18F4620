/* 
 * File:   newfile.c
 * Author: peter
 *
 * Created on July 12, 2024, 3:17 PM
 */

#include "7-seg.h"

/**
 * 
 * @param _seg_config
 * @return 
 */
STD_ReturnType seg_initialization(const seg_config *_seg_config)
{
    STD_ReturnType ret = E_OK;
     

    if (NULL == _seg_config) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_Initialization(&(_seg_config->_seg_pin[seg_pin0]));
        ret = gpio_pin_Initialization(&(_seg_config->_seg_pin[seg_pin1]));
        ret = gpio_pin_Initialization(&(_seg_config->_seg_pin[seg_pin2]));
        ret = gpio_pin_Initialization(&(_seg_config->_seg_pin[seg_pin3]));
    }
    return ret;
}

/**
 * 
 * @param _seg_config
 * @param number
 * @return 
 */
STD_ReturnType seg_write_number(const seg_config *_seg_config , uint8 number)
{
    STD_ReturnType ret = E_OK;
     

    if ((NULL == _seg_config) || (number > 9))
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        ret = gpio_pin_write_logic(&(_seg_config->_seg_pin[seg_pin0]),(number >> seg_pin0) & BIT_MASK);
        ret = gpio_pin_write_logic(&(_seg_config->_seg_pin[seg_pin1]),(number >> seg_pin1) & BIT_MASK);
        ret = gpio_pin_write_logic(&(_seg_config->_seg_pin[seg_pin2]),(number >> seg_pin2) & BIT_MASK);
        ret = gpio_pin_write_logic(&(_seg_config->_seg_pin[seg_pin3]),(number >> seg_pin3) & BIT_MASK);
    }
    return ret;
}
