/**
Purpose: Establish the SPI interface protocol.

Source file in the GE-7000 Code Library.

PN: ME-N60-0
*/

#include "config.h"

#if NORITAKE_OLED_GENERATION == 'B' && NORITAKE_OLED_INTERFACE == 0 && NORITAKE_OLED_SERIAL == 2
#include <Arduino.h>
#include <stddef.h>
#include "interface.h"
#include <SPI.h>

void initPort()
{
    pinMode(RESET_PIN, GPIO_MODE_OUTPUT);
    SPI.begin();
    //SPI.begin(SCK, OUT_PIN, -1, SCK_PIN);
}

void writePort(uint8_t data)
{
    SPI.transfer(data);
}

void hardReset()
{
    digitalWrite(RESET_PIN, LOW);
    _delay_ms(2);
    digitalWrite(RESET_PIN, HIGH);
    _delay_ms(120);
}

#endif
