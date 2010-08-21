/*
  sssd.h - Library to control Serial Seven Segments Display (COM-09764 by SparkFun).
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


/*
  TODO: 
  - Remove the dependency on the SPI library.
  - Add lgpl to the cpp file
*/
#ifndef Sssd_h
#define Sssd_h

#define SSSD_DOT1 (1)
#define SSSD_DOT2 (1<<1)
#define SSSD_DOT3 (1<<2)
#define SSSD_DOT4 (1<<3)
#define SSSD_COLONS (1<<4)
#define SSSD_UPPER_DOT (1<<5)

#define SSSD_SEGMENT_A (1)
#define SSSD_SEGMENT_B (1<<1)
#define SSSD_SEGMENT_C (1<<2)
#define SSSD_SEGMENT_D (1<<3)
#define SSSD_SEGMENT_E (1<<4)
#define SSSD_SEGMENT_F (1<<5)
#define SSSD_SEGMENT_G (1<<6)

#define SSSD_BLANK_DIGIT (0x78)


class SSSD
{
  public:
    /* Constructor - sssd_ss_pin is the number of the arduino pin that connected to the display Slave Select (SCN) */
    SSSD(byte sssd_ss_pin=SS_PIN);
    
    /* Send the rest command to the display. */
    void sendReset();
    
    /* Write digits to the display. Each digit can be nibble (0-9,0xa-0xf) or ASCII representation (E.G. 'A','a').
    For a black digit (all the leds off), pass SSSD_BLANK_DIGIT.
    For full list of available chars see the reference manual. */
    void writeNumbers(byte digit1, byte digit2, byte digit3, byte digit4);
    
    /*
    Set the dots on the display to specific status.
    */
    void setDots(byte flags);
    void changeDots(byte flags);
    
    /*
    Set the brightness of the display. level can be between 0 to 254. Lower number means brighter display.
    */
    void setBrightness(byte level);
    
    /*
    control specific segments. digit is the index of the digit to control. segments is flags byte of the segments.
    */
    void setSegments(byte digit, byte segments);
    
  private:
    SPI mySpi;
    byte dots_status;
    byte ss_pin;
};

#endif
