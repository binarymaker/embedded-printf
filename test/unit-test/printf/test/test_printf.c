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

}

void
tearDown()
{

}


void
test_stringPrintf()
{
  PRINT_Sprintf(stringConv, "binary maker %s","makes life beauty");
  TEST_ASSERT_EQUAL_STRING("binary maker makes life beauty", stringConv);

  PRINT_Sprintf(stringConv, "%s : %s %s","Time","10:10", "Min");
  TEST_ASSERT_EQUAL_STRING("Time : 10:10 Min", stringConv);
}

void
test_integerPrintf()
{
  
  PRINT_Sprintf(stringConv, "%d", 0);
  TEST_ASSERT_EQUAL_STRING("0", stringConv);

  PRINT_Sprintf(stringConv, "%d", 65535);
  TEST_ASSERT_EQUAL_STRING("65535", stringConv);

  PRINT_Sprintf(stringConv, "%d", -32768);
  TEST_ASSERT_EQUAL_STRING("-32768", stringConv);
 
}

void
test_PaddingIntegerPrintf()
{
  PRINT_Sprintf(stringConv, "%5d", 0);
  TEST_ASSERT_EQUAL_STRING("    0", stringConv);

  PRINT_Sprintf(stringConv, "%05d", 0);
  TEST_ASSERT_EQUAL_STRING("00000", stringConv);

  PRINT_Sprintf(stringConv, "%5d", 589);
  TEST_ASSERT_EQUAL_STRING("  589", stringConv);

  PRINT_Sprintf(stringConv, "%05d", 589);
  TEST_ASSERT_EQUAL_STRING("00589", stringConv);

  PRINT_Sprintf(stringConv, "%5d",-589);
  TEST_ASSERT_EQUAL_STRING(" -589", stringConv);

  PRINT_Sprintf(stringConv, "%05d",-589);
  TEST_ASSERT_EQUAL_STRING("-0589", stringConv);
}


void
test_hexPrintf()
{
  PRINT_Sprintf(stringConv, "%x", 0);
  TEST_ASSERT_EQUAL_STRING("0", stringConv);

  PRINT_Sprintf(stringConv, "%x", 0x5f9);
  TEST_ASSERT_EQUAL_STRING("5f9", stringConv);

  PRINT_Sprintf(stringConv, "%x", 0xdeed);
  TEST_ASSERT_EQUAL_STRING("deed", stringConv);
}

void
test_PaddingHexPrintf()
{
  PRINT_Sprintf(stringConv, "%3x", 0);
  TEST_ASSERT_EQUAL_STRING("  0", stringConv);

  PRINT_Sprintf(stringConv, "%5x", 0x5f9);
  TEST_ASSERT_EQUAL_STRING("  5f9", stringConv);

  PRINT_Sprintf(stringConv, "%05x", 0xdeed);
  TEST_ASSERT_EQUAL_STRING("0deed", stringConv);
  
  PRINT_Sprintf(stringConv, "%02x", 0xdeed);
  TEST_ASSERT_EQUAL_STRING("deed", stringConv);
}

void
test_PaddingBinPrintf()
{
  PRINT_Sprintf(stringConv, "%3b", 0);
  TEST_ASSERT_EQUAL_STRING("  0", stringConv);

  PRINT_Sprintf(stringConv, "%5b", 0x0f);
  TEST_ASSERT_EQUAL_STRING(" 1111", stringConv);

  PRINT_Sprintf(stringConv, "%010b", 0xaa);
  TEST_ASSERT_EQUAL_STRING("0010101010", stringConv);
  
  PRINT_Sprintf(stringConv, "%02b", 0x0f);
  TEST_ASSERT_EQUAL_STRING("1111", stringConv);
}

void
test_floatPrintf()
{
  PRINT_Sprintf(stringConv, "%01.2f", 1.23);
  TEST_ASSERT_EQUAL_STRING("1.23", stringConv);

  PRINT_Sprintf(stringConv, "%02.2f", 1.23);
  TEST_ASSERT_EQUAL_STRING("01.23", stringConv);

  PRINT_Sprintf(stringConv, "%03.4f", 1.23);
  TEST_ASSERT_EQUAL_STRING("001.2300", stringConv);
 
  PRINT_Sprintf(stringConv, "%03.4f", 0.0001);
  TEST_ASSERT_EQUAL_STRING("000.0001", stringConv);

  PRINT_Sprintf(stringConv, "%1.4f", 0.0001);
  TEST_ASSERT_EQUAL_STRING("0.0001", stringConv);

  PRINT_Sprintf(stringConv, "%2.1f", -1.8);
  TEST_ASSERT_EQUAL_STRING("-1.8", stringConv);

}
