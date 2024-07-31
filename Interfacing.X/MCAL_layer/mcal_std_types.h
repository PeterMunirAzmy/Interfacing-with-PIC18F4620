/* 
 * File:   mcal_std_types.h
 * Author: peter
 *
 * Created on July 1, 2024, 3:41 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/*Section : Includes*/
#include "mcal_std_libraries.h"
#include "compiler.h"

/*Section : Macro Declaration*/
#define STD_HIGH            0x01
#define STD_LOW             0x00

#define STD_ON              0x01
#define STD_OFF             0x00

#define STD_ACTIVE          0x01
#define STD_IDEL            0x00

#define E_OK                (STD_ReturnType)0x01
#define E_NOT_OK            (STD_ReturnType)0x00

#define ENABLE_CONFIG       0x01
#define DISABLE_CONFIG      0x00

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;

typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;

typedef uint8               STD_ReturnType;

/*Section : Function Declaration*/

#endif	/* MCAL_STD_TYPES_H */

