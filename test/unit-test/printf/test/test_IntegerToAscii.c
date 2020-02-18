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
test_simpleNumberConv()
{


  numOfPrintChar = PRINT_IntegerToAscii(0, stringConv, RADIX_DEC, 0, 0, 0);
  
  TEST_ASSERT_EQUAL(1, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("0", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(1290, stringConv, RADIX_DEC, 0, 0, 0);
  
  TEST_ASSERT_EQUAL(4, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("1290", stringConv);
}

void
test_nagativeNumConv()
{
   numOfPrintChar = PRINT_IntegerToAscii(-0, stringConv, RADIX_DEC, 0, 0, 0);
  
  TEST_ASSERT_EQUAL(1, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("0", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(-25, stringConv, RADIX_DEC, 0, 0, 0);
  
  TEST_ASSERT_EQUAL(3, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("-25", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(-1290, stringConv, RADIX_DEC, 0, 0, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("-1290", stringConv);
}

void
test_paddingNumConv()
{
  numOfPrintChar = PRINT_IntegerToAscii(0, stringConv, RADIX_DEC, 5, 0, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("    0", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(123, stringConv, RADIX_DEC, 5, 0, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("  123", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(98765, stringConv, RADIX_DEC, 3, 0, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("98765", stringConv);
}

void
test_paddingNegativeNumConv()
{
  numOfPrintChar = PRINT_IntegerToAscii(-123, stringConv, RADIX_DEC, 5, 0, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING(" -123", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(-98765, stringConv, RADIX_DEC, 3, 0, 0);
  
  TEST_ASSERT_EQUAL(6, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("-98765", stringConv);
}

void
test_zeroPaddingNumConv()
{
  numOfPrintChar = PRINT_IntegerToAscii(0, stringConv, RADIX_DEC, 5, 1, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("00000", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(123, stringConv, RADIX_DEC, 5, 1, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("00123", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(98765, stringConv, RADIX_DEC, 3, 1, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("98765", stringConv);
}

void
test_ZeroPaddingNegativeNumConv()
{
  numOfPrintChar = PRINT_IntegerToAscii(-123, stringConv, RADIX_DEC, 5, 1, 0);
  
  TEST_ASSERT_EQUAL(5, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("-0123", stringConv);

  numOfPrintChar = PRINT_IntegerToAscii(-98765, stringConv, RADIX_DEC, 3, 1, 0);
  
  TEST_ASSERT_EQUAL(6, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("-98765", stringConv);
}

void
test_signPaddingNegativeNumConv()
{
  numOfPrintChar = PRINT_IntegerToAscii(123, stringConv, RADIX_DEC, 0, 0, 1);
  
  TEST_ASSERT_EQUAL(4, numOfPrintChar);
  TEST_ASSERT_EQUAL_STRING("+123", stringConv);

}