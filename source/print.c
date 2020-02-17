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

/* Includes ------------------------------------------------------------------*/
#include "print.h"
#include "stdint.h"
#include <stdarg.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t* printBuffer;
static uint8_t printBufIndex;
static uint8_t printBufSize;

static void (*PRINT_PutChar)(uint8_t);
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void
PRINT_OutFunction(void (*putCharFunction)(uint8_t))
{
  PRINT_PutChar = putCharFunction;
}

void
PRINT_String(uint8_t *str)
{
  uint16_t chIdx_i16 = 0;

  while (str[chIdx_i16] != '\0')
  {
    PRINT_PutChar(str[chIdx_i16]);
    chIdx_i16++;
  }
}

uint32_t
PRINT_IntegerToAscii(int32_t number,
                     uint8_t *buffer,
                     radix_et radix,
                     uint8_t zeropad_length,
                     uint8_t isZeroPadding_b)
{
  uint8_t i = 0;
  uint16_t len = 0;
  uint8_t is_negative = 0;
  int32_t num;
  uint8_t buffer_limit;
  uint8_t swap;

  num = number;
  

  buffer_limit = 32; //TODO : macro

  if ((num < 0) && (radix == RADIX_DEC))
  {
    num = -num;
    is_negative = 1;
    if (zeropad_length && (0 != isZeroPadding_b))
    {
      zeropad_length--;
    }
  }
  
  if (num == 0)
  {
      buffer[len++] = '0';
  }

  while ((num != 0) && (buffer_limit > len))
  {
    int rem = num % radix;
    buffer[len++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / radix;
  }
  

  if (0 != isZeroPadding_b)
  {
    for (i = len; i < zeropad_length; i++)
    {
       buffer[len++] = '0';
    }

    if (is_negative && (buffer_limit > len))
    {
      buffer[len++] = '-';
    }
  }
  else
  {
    if (is_negative && (buffer_limit > len))
    {
      buffer[len++] = '-';
    }
        
    for (i = len; i < zeropad_length; i++)
    {
       buffer[len++] = ' ';
    }
  }

  buffer[len] = '\0';

  for (i = 0; i < len / 2; i++)
  {
    swap = buffer[i];
    buffer[i] = buffer[len - i - 1];
    buffer[len - i - 1] = swap;
  }

  return len;
}

void
PRINT_Printf(const uint8_t *argList, ...)
{
  const uint8_t *ptr;
  va_list argp;
  int16_t num_i16;
  int32_t num_i32;
  uint16_t num_u16;
  uint32_t num_u32;
  uint8_t *str;
  uint8_t ch;
  uint8_t isZeroPadding_b = 0;
  uint8_t numOfDigitToPrint_u8;
  uint8_t numOfFractionToPrint_u8 = 0;
  double num_float;
  uint8_t convBuffer[32];

  va_start(argp, argList);

  for (ptr = argList; *ptr != '\0'; ptr++)
  {

    ch = *ptr;
    if (ch == '%') /* Check for '%' for format specifier */
    {
      ptr++;
      ch = *ptr;
      if ((ch >= '0') && (ch <= '9'))
      {
        if (ch == '0')
        {
          isZeroPadding_b = 1;
          ptr++;
          ch = *ptr;
        }
        else
        {
          isZeroPadding_b = 0;
        }
        
        numOfDigitToPrint_u8 = 0;
        while ((ch >= '0') && (ch <= '9'))
        {
          numOfDigitToPrint_u8 = (numOfDigitToPrint_u8 * 10) + (ch - '0');
          ptr++;
          ch = *ptr;
        }
        if(ch == '.')
        {
          ptr++;
          ch = *ptr;
          numOfFractionToPrint_u8 = 0;
          while ((ch >= '0') && (ch <= '9'))
          {
            numOfFractionToPrint_u8 = (numOfFractionToPrint_u8 * 10) + (ch - '0');
            ptr++;
            ch = *ptr;
          }
        }
        else
        {
          numOfFractionToPrint_u8 = 0u;
        }
        
      }
      else
      {
        numOfDigitToPrint_u8 = 0;
      }

      switch (ch) /* Decode the type of the argument */
      {
        case 'C':
        case 'c':
          ch = va_arg(argp, int);
          PRINT_PutChar(ch);
          break;

        case 'd':
          num_i16 = va_arg(argp, int16_t);
          PRINT_IntegerToAscii(num_i16, 
                              convBuffer, 
                              RADIX_DEC, 
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'D':
          num_i32 = va_arg(argp, int32_t);
          PRINT_IntegerToAscii(num_i32,
                              convBuffer,
                              RADIX_DEC,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'u':
          num_u16 = va_arg(argp, uint16_t);
          PRINT_IntegerToAscii(num_u16,
                              convBuffer,
                              RADIX_DEC,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'U':
          num_u32 = va_arg(argp, uint32_t);
          PRINT_IntegerToAscii(num_u32,
                              convBuffer,
                              RADIX_DEC,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'x':
          num_u16 = va_arg(argp, uint16_t);
          PRINT_IntegerToAscii(num_u16,
                              convBuffer,
                              RADIX_HEX,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'X':
          num_u32 = va_arg(argp, uint32_t);
          PRINT_IntegerToAscii(num_u32,
                              convBuffer,
                              RADIX_HEX,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'b':
          num_u16 = va_arg(argp, int);
          if (numOfDigitToPrint_u8 == 0xff) // todo
            numOfDigitToPrint_u8 = 16;
          PRINT_IntegerToAscii(num_u16,
                              convBuffer,
                              RADIX_BIN,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'B':
          num_u32 = va_arg(argp, uint32_t);
          if (numOfDigitToPrint_u8 == 0xff) // todo
            numOfDigitToPrint_u8 = 16;
          PRINT_IntegerToAscii(num_u32,
                              convBuffer,
                              RADIX_BIN,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          break;

        case 'F':
        case 'f':
          num_float = va_arg(argp, double);
          if (numOfDigitToPrint_u8 == 0xff) // todo
          {  numOfDigitToPrint_u8 = 16; }
          num_i32 = (int32_t)num_float;
          uint32_t fraction_multiplier_u32 = 1;
          for(uint8_t i_u8 = 0; i_u8 < numOfFractionToPrint_u8; i_u8++)
          {
            fraction_multiplier_u32 *= 10;
          }
          uint32_t faction_u32 = (num_float - (double)num_i32) * (fraction_multiplier_u32);
          if(0.0 > num_float) /*-ve*/
          {
            faction_u32 *= -1;
          }
          
          PRINT_IntegerToAscii(num_i32,
                              convBuffer,
                              RADIX_DEC,
                              numOfDigitToPrint_u8,
                              isZeroPadding_b);
          PRINT_String(convBuffer);
          PRINT_PutChar(0x2E); /* [.] */
          PRINT_IntegerToAscii(faction_u32,
                              convBuffer,
                              RADIX_DEC,
                              numOfFractionToPrint_u8,
                              1);
          PRINT_String(convBuffer);
          break;
        case 'S':
        case 's':
          str = va_arg(argp, uint8_t *);
          PRINT_String(str);
          break;

        case '%':
          PRINT_PutChar('%');
          break;
      }
    }
    else
    {
      PRINT_PutChar(ch);
    }
  }

  va_end(argp);
}

/* internal buffer */
void
PRINT_BufferLink(uint8_t* buffer, uint8_t size)
{
  printBuffer  = buffer;
  printBufSize = size;
  PRINT_BufferClear();
}

void
PRINT_BufferWrite(uint8_t ch)
{
  printBuffer[printBufIndex] = ch;
  printBufIndex++;
}

void
PRINT_BufferClear()
{
  uint8_t i;
  printBufIndex = 0;
  for(i = 0; i < printBufSize; i++)
  {
    printBuffer[i] = 0;
  }
}