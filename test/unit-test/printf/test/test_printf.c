/**
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
  */

#include "unity.h"
#include "print.h"
#include "print-cfg.h"

char stringConv[50];
int numOfPrintChar;

void
setUp()
{
  PRINT_BufferLink(stringConv, sizeof(stringConv));
  PRINT_ChannelSelect(PRINT_CHANNEL_BUFFER);
}

void
tearDown()
{

}

void
test_StringToBuffer()
{
  PRINT_BufferClear();
  PRINT_String("binary maker");
  TEST_ASSERT_EQUAL_STRING("binary maker", stringConv);

  PRINT_BufferClear();
  PRINT_String("!@#");
  TEST_ASSERT_EQUAL_STRING("!@#", stringConv);
}

void
test_stringPrintf()
{
  PRINT_BufferClear();
  PRINT_Printf("binary maker %s","makes life beauty");
  TEST_ASSERT_EQUAL_STRING("binary maker makes life beauty", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%s : %s %s","Time","10:10", "Min");
  TEST_ASSERT_EQUAL_STRING("Time : 10:10 Min", stringConv);
}

void
test_integerPrintf()
{
  PRINT_BufferClear();
  PRINT_Printf("%d", 0);
  TEST_ASSERT_EQUAL_STRING("0", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%d", 65535);
  TEST_ASSERT_EQUAL_STRING("65535", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%d", -32768);
  TEST_ASSERT_EQUAL_STRING("-32768", stringConv);
}

void
test_PaddingIntegerPrintf()
{
  PRINT_BufferClear();
  PRINT_Printf("%5d", 0);
  TEST_ASSERT_EQUAL_STRING("    0", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%05d", 0);
  TEST_ASSERT_EQUAL_STRING("00000", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%5d", 589);
  TEST_ASSERT_EQUAL_STRING("  589", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%05d", 589);
  TEST_ASSERT_EQUAL_STRING("00589", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%5d",-589);
  TEST_ASSERT_EQUAL_STRING(" -589", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%05d",-589);
  TEST_ASSERT_EQUAL_STRING("-0589", stringConv);
}


void
test_hexPrintf()
{
  PRINT_BufferClear();
  PRINT_Printf("%x", 0);
  TEST_ASSERT_EQUAL_STRING("0", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%x", 0x5f9);
  TEST_ASSERT_EQUAL_STRING("5f9", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%x", 0xdeed);
  TEST_ASSERT_EQUAL_STRING("deed", stringConv);
}

void
test_PaddingHexPrintf()
{
  PRINT_BufferClear();
  PRINT_Printf("%3x", 0);
  TEST_ASSERT_EQUAL_STRING("  0", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%5x", 0x5f9);
  TEST_ASSERT_EQUAL_STRING("  5f9", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%05x", 0xdeed);
  TEST_ASSERT_EQUAL_STRING("0deed", stringConv);
  
  PRINT_BufferClear();
  PRINT_Printf("%02x", 0xdeed);
  TEST_ASSERT_EQUAL_STRING("deed", stringConv);
}

void
test_PaddingBinPrintf()
{
  PRINT_BufferClear();
  PRINT_Printf("%3b", 0);
  TEST_ASSERT_EQUAL_STRING("  0", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%5b", 0x0f);
  TEST_ASSERT_EQUAL_STRING(" 1111", stringConv);

  PRINT_BufferClear();
  PRINT_Printf("%010b", 0xaa);
  TEST_ASSERT_EQUAL_STRING("0010101010", stringConv);
  
  PRINT_BufferClear();
  PRINT_Printf("%02b", 0x0f);
  TEST_ASSERT_EQUAL_STRING("1111", stringConv);
}