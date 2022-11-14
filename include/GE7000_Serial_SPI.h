/*******************************************************
Establishes the SPI interface with the GE7000 module.

Noritake Co., Inc.
Version: 1.0 (ME-N64-0)
Support Contact: support.ele@noritake.com
*******************************************************/
#pragma once

#include "GE7000_Interface.h"

#define _delay_us(x) delayMicroseconds(x)
#define _delay_ms(x) delay(x)

class GE7000_Serial_SPI : public GE7000_Interface
{

protected:
    uint8_t OUT_PIN = 13;
    uint8_t BUSY_PIN;
    uint8_t SCK_PIN;
    uint8_t RESET_PIN;
    uint8_t CS_PIN;

public:
    GE7000_Serial_SPI(uint8_t out, uint8_t busy, uint8_t sck, uint8_t reset, uint8_t cs) : OUT_PIN(out), BUSY_PIN(busy), SCK_PIN(sck), RESET_PIN(reset), CS_PIN(cs)
    {
        // 13, 12, 14, 27, 25); // SIN,BUSY,SCK,RESET,CS
    }

    void init()
    {
        pinMode(CS_PIN, OUTPUT);
        pinMode(RESET_PIN, OUTPUT);
        pinMode(OUT_PIN, OUTPUT);
        pinMode(SCK_PIN, OUTPUT);
        pinMode(BUSY_PIN, INPUT);
        digitalWrite(OUT_PIN, LOW);
        digitalWrite(SCK_PIN, HIGH);
        digitalWrite(RESET_PIN, HIGH);
        digitalWrite(CS_PIN, HIGH);
    }

    void write(uint8_t data)
    {
        LOWER(CS);
        while (CHECK(BUSY))
            ;
        for (uint8_t i = 0x80; i; i >>= 1)
        {
            LOWER(SCK);
            // delayMicroseconds(1);
            _delay_us(1);
            if (data & i)
                RAISE(OUT);
            else
                LOWER(OUT);
            RAISE(SCK);
            _delay_us(1);
        }
        _delay_us(17);
        RAISE(CS);
    }

    void hardReset()
    {
        init();
        LOWER(CS);
        LOWER(RESET);
        _delay_ms(1);
        RAISE(RESET);
        _delay_ms(100);
        RAISE(CS);
    }
};