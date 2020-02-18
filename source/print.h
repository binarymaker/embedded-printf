/**\cond
  ******************************************************************************
  * ______  _                             ___  ___        _               
  * | ___ \(_)                            |  \/  |       | |              
  * | |_/ / _  _ __    __ _  _ __  _   _  | .  . |  __ _ | | __ ___  _ __ 
  * | ___ \| || '_ \  / _` || '__|| | | | | |\/| | / _` || |/ // _ \| '__|
  * | |_/ /| || | | || (_| || |   | |_| | | |  | || (_| ||   <|  __/| |   
  * \____/ |_||_| |_| \__,_||_|    \__, | \_|  |_/ \__,_||_|\_\\___||_|   
  *                                 __/ |                                 
  *                                |___/                                  
  *                                                                       
  * Copyright (C) 2019 Binary Maker - All Rights Reserved
  *
  * This program and the accompanying materials are made available
  * under the terms described in the LICENSE file which accompanies
  * this distribution.
  * Written by Binary Maker <https://github.com/binarymaker>
  ******************************************************************************
  \endcond*/

#ifndef PRINT_12405ad7_fc71_11e9_af12_74dfbf0d835a
#define PRINT_12405ad7_fc71_11e9_af12_74dfbf0d835a

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * \brief Source file version tag
 *        
 *        version info: [15:8] main [7:0] beta
 */
#define __PRINT_VERSION      (0x0001u)

/* Includes ------------------------------------------------------------------*/
#include "print-cfg.h"
#include "stdint.h"
#include <stdarg.h>
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  RADIX_BIN = 2,
  RADIX_OCT = 8,
  RADIX_DEC = 10,
  RADIX_HEX = 16
} radix_et;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define PRINT_Sprintf(buffer,_F, ...)  {                                    \
                                PRINT_BufferLink(buffer, sizeof(buffer));   \
                                PRINT_OutFunction(PRINT_BufferWrite);       \
                                PRINT_BufferClear();                        \
                                PRINT_Printf((_F), __VA_ARGS__);            \
                               }
/* Exported functions ------------------------------------------------------- */

uint32_t
PRINT_IntegerToAscii(int32_t number,
                     uint8_t *buffer,
                     radix_et radix,
                     uint8_t zeropad_length,
                     uint8_t isZeroPadding_b,
                     uint8_t sign_notation_b);

void
PRINT_OutFunction(void (*putCharFunction)(uint8_t));

void
PRINT_String(uint8_t *str);

void 
PRINT_Printf(const uint8_t *argList, ...);

void
PRINT_BufferLink(uint8_t* buffer, uint8_t size);

void
PRINT_BufferWrite(uint8_t ch);

void
PRINT_BufferClear();

#ifdef __cplusplus
}
#endif

#endif /* PRINT_12405ad7_fc71_11e9_af12_74dfbf0d835a */

