/* 
 * File:   eeprom.c
 * Author: peter
 *
 * Created on August 4, 2024, 4:01 PM
 */

#include "eeprom.h"

/**
 * 
 * @param address
 * @param data
 * @return 
 */
STD_ReturnType EEPROM_Data_Write_Byte(uint16 address , uint8 data)
{
    STD_ReturnType ret = E_OK;
    
    /* Read the interrupt status (enable or disable) */
    uint8 interrupt_status = INTCONbits.GIE;
    
    /* update the address registers */
    EEADRH = (uint8)(address >> 8)&(0x03);
    EEADR = (uint8)(address & 0xFF);
    
    /* update the data registers */
    EEDATA = data;
    
    /* select access data EEPROM memory */
    EECON1bits.CFGS = ACCESS_EEPROM_OR_FLASH_MEMORY;
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    
    /* allow write cycles to flash program / data EEPROM */
     EECON1bits.WREN = ALLOW_WRITE_CYCLE_TO_FALSH_AND_EEPROM;
    
    /* disable all interrupts "General interrupts" */
     INTERRUPT_DISABLE_GLOBLE_INTERRUPT();
    /* write the required sequence : 0x55 -> 0xAA */
     EECON2 = 0x55;
     EECON2 = 0xAA;
     
    /* initialize the EEPROM data erase / write cycle */
    EECON1bits.WR = EEPROM_EREAS_OR_WRITE_CYCLE;
            
    /* wait for write to complete */
    while(EECON1bits.WR);

    /* inhibits write cycles to flash program / data EEPROM */
    EECON1bits.WREN = INHIBITS_WRITE_CYCLE_FALSH_AND_EEPROM;

    /* restore the interrupt status "enable or disable" */
    INTCONbits.GIE = interrupt_status;
    return ret;
}

/**
 * 
 * @param address
 * @param return_data
 * @return 
 */
STD_ReturnType EEPROM_Data_Read_Byte(uint16 address, uint8 *return_data)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == return_data)
    {
        ret = E_NOT_OK;
    }
    else
    {
    /* update the address registers */
    EEADRH = (uint8)(address >> 8)&(0x03);
    EEADR = (uint8)(address & 0xFF);
    
    /* select access data EEPROM memory */
    EECON1bits.CFGS = ACCESS_EEPROM_OR_FLASH_MEMORY;
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    
    /* initialize the EEPROM data read */
    EECON1bits.RD = EEPROM_DATA_READ;
    NOP();
    NOP();
    /* Return data */
    *return_data = EEDATA;
    }
    
    return ret;
}