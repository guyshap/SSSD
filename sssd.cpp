/*
  sssd.cpp - Library to control Serial Seven Segments Display (COM-09764 by SparkFun).
  Copyright (c) 2010 Guy Shapiro
  Version: 15.8.10
  
  This library was inspired by the code of Quazar & Busaboi 
  (http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1247533060/2#2)
  
  The part reference manual can be found on 
  http://www.sparkfun.com/datasheets/Components/LED/7-Segment/SFE-0012-DS-7segmentSerial-v41.pdf



  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <Spi.h>
#include "WProgram.h"

#include "sssd.h"

SSSD::SSSD(byte sssd_ss_pin):
ss_pin(sssd_ss_pin)
{
  mySpi = SPI();
  pinMode(ss_pin, OUTPUT);
  Spi.mode((1<<SPR1));
  digitalWrite(ss_pin, HIGH);
  sendReset();
}

void SSSD::sendReset()
{
  digitalWrite(ss_pin, LOW);
  Spi.transfer(0x76);
  digitalWrite(ss_pin, HIGH);
  dots_status = 0;
}

void SSSD::writeNumbers(byte digit1, byte digit2, byte digit3, byte digit4)
{
  digitalWrite(ss_pin, LOW);
  Spi.transfer(digit1);
  Spi.transfer(digit2);
  Spi.transfer(digit3);
  Spi.transfer(digit4);
  digitalWrite(ss_pin, HIGH);
}

void SSSD::setDots(byte flags)
{
  digitalWrite(ss_pin, LOW);
  Spi.transfer(0x77);
  Spi.transfer(flags);
  digitalWrite(ss_pin, HIGH);
  dots_status = flags;
}

void SSSD::changeDots(byte flags)
{
  dots_status ^= flags;
  setDots(dots_status);
}

void SSSD::setBrightness(byte level)
{
  digitalWrite(ss_pin, LOW);
  Spi.transfer(0x7A);
  Spi.transfer(level);
  digitalWrite(ss_pin, HIGH);
}

void SSSD::setSegments(byte digit, byte segments)
{
  digitalWrite(ss_pin, LOW);
  //The singel digits control commands are 0x7B - 0x7E
  //We convert digit from 1 to 4 into this command.
  Spi.transfer(0x7A+digit);
  Spi.transfer(segments);
  digitalWrite(ss_pin, HIGH);
}
