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
