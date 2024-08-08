/* 
 * File:   eeprom.h
 * Author: peter
 *
 * Created on August 4, 2024, 4:01 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/*Section : Includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/internal_interrupt.h"

/*Section : Macro Declaration*/
#define ACCESS_FLASH_MEMORY                     1
#define ACCESS_EEPROM_MEMORY                    0

#define ACCESS_CONFIGURATION_REGISTERS          1
#define ACCESS_EEPROM_OR_FLASH_MEMORY           0

#define ALLOW_WRITE_CYCLE_TO_FALSH_AND_EEPROM   1
#define INHIBITS_WRITE_CYCLE_FALSH_AND_EEPROM   0

#define EEPROM_EREAS_OR_WRITE_CYCLE             1
#define EEPROM_WRITE_CYCLE_IS_COMPLETE          0

#define EEPROM_DATA_READ                        1
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/

/*Section : Function Declaration*/
STD_ReturnType EEPROM_Data_Write_Byte(uint16 addres , uint8 data);
STD_ReturnType EEPROM_Data_Read_Byte(uint16 addres, uint8 *return_data);


#endif	/* EEPROM_H */

