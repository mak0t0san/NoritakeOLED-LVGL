/**
Purpose: Establish the asynchronous serial interface protocol.

Source file in the GE-7000 Code Library.

PN: ME-N60-0
*/

#include "config.h"

#if NORITAKE_OLED_INTERFACE==0 && NORITAKE_OLED_SERIAL==0

#include <stddef.h>
#include <avr/io.h>
#include <util/delay.h>
#include "interface.h"

void initPort() {
    RAISE(RESET);
    #if NORITAKE_OLED_RS232==1
        LOWER(OUT);
    #else
        RAISE(OUT);
    #endif
    DIRECTION(OUT,1);
    DIRECTION(RESET,1);
    DIRECTION(BUSY,0);
}

void writePort(uint8_t data) {
    #if NORITAKE_OLED_RS232==1
        while (!CHECK(BUSY));
        RAISE(OUT);
        #if NORITAKE_OLED_BAUD==115200
            _delay_us(1e6 / NORITAKE_OLED_BAUD * 1.1);
        #else
            _delay_us(1e6 / NORITAKE_OLED_BAUD * 1.3);
        #endif
        for (uint8_t i = 1; i; i<<=1) {
            if (data & i)
                LOWER(OUT);
            else
                RAISE(OUT);

            #if NORITAKE_OLED_BAUD==115200
                _delay_us(1e6 / NORITAKE_OLED_BAUD * .85);
            #else
                _delay_us(1e6 / NORITAKE_OLED_BAUD * .9);
            #endif

        }
        LOWER(OUT);
        _delay_us(1e6 / NORITAKE_OLED_BAUD);
    #else
        while (CHECK(BUSY));
        LOWER(OUT);
        #if NORITAKE_OLED_BAUD==115200
            _delay_us(1e6 / NORITAKE_OLED_BAUD * 1.1);
        #else
            _delay_us(1e6 / NORITAKE_OLED_BAUD * 1.3);
        #endif
        for (uint8_t i = 1; i; i<<=1) {
            if (data & i)
                RAISE(OUT);
            else
                LOWER(OUT);

            #if NORITAKE_OLED_BAUD==115200
                _delay_us(1e6 / NORITAKE_OLED_BAUD * .85);
            #else
                _delay_us(1e6 / NORITAKE_OLED_BAUD * .9);
            #endif

        }
        RAISE(OUT);
        _delay_us(1e6 / NORITAKE_OLED_BAUD);
    #endif
}

void hardReset() {
    initPort();
    LOWER(RESET);
    _delay_ms(2);
    RAISE(RESET);
    _delay_ms(120);
}

#endif
