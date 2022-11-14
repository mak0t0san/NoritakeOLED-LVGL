/**
Purpose: Functions for each command in the GE-7000 command set.

Source file in the GE-7000 Code Library.

PN: ME-N60-0
*/

#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "Noritake_OLED_GE7000.h"
#include "interface.h"
#include <alloca.h>

/**
Sets the display memory orientation. (normal or rotated 180 degrees)

angle = 0x00: Normal
angle = 0x01: Rotates 180 degrees

Default: angle = 0x00

Only works on the 7933B OLED module.

@param  angle The desired display memory orientation.
@return none
*/
void Noritake_OLED_GE7000::GE7000_displayAngleControl(uint8_t angle){
#if NORITAKE_OLED_MODEL_CLASS == 7933
	command(0x1f);
	command(0x28);
	command(0x77);
	command(0x80);
	command(angle);
#endif
}

/**
Performs a backspace on the GE display.

@return none
*/
void Noritake_OLED_GE7000::GE7000_back() {
    command(0x08);
}

/**
Moves the cursor forward one position on the GE display.

@return none
*/
void Noritake_OLED_GE7000::GE7000_forward() {
    command(0x09);
}

/**
Performs a line feed on the GE display.

@return none
*/
void Noritake_OLED_GE7000::GE7000_lineFeed() {
    command(0x0a);
}

/**
Brings the cursor to its home position (top left) on the GE display.

@return none
*/
void Noritake_OLED_GE7000::GE7000_home() {
    command(0x0b);
}

/**
Performs a carriage return on the GE display.

@return none
*/
void Noritake_OLED_GE7000::GE7000_carriageReturn() {
    command(0x0d);
}

/**
Moves the cursor to a specific location on the GUD module.

@param  x       The desired x coordinate.
@param  y       The desired y coordinate.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setCursor(unsigned x, unsigned y) {
    command(0x1f);
    command('$');
    command_xy(x, y);
}

/**
Clears the screen of the GE module.

@return none
*/
void Noritake_OLED_GE7000::GE7000_clearScreen() {
    command(0x0c);
}

/**
Turns the cursor on.

@return none
*/
void Noritake_OLED_GE7000::GE7000_cursorOn() {
    command(0x1f, 'C', 1);
}

/**
Turns the cursor off.

@return none
*/
void Noritake_OLED_GE7000::GE7000_cursorOff() {
    command(0x1f, 'C', 0);
}

/**
Initializes the Noritake Display

@return none
*/
void Noritake_OLED_GE7000::GE7000_init() {
    _delay_ms(NORITAKE_OLED_RESET_DELAY);
    initPort();
    command(0x1b);
    command('@');
}

/**
Resets the Noritake Display

@return none
*/
void Noritake_OLED_GE7000::GE7000_reset() {
    hardReset();
}

/**
Enables the use of multiple-byte characters.

@param  emable  Enable or disable multiple byte characters.
@return none
*/
void Noritake_OLED_GE7000::GE7000_useMultibyteChars(bool enable) {
    #if (NORITAKE_OLED_MODEL_CLASS-7000)/100==9
        us_command('g', 0x02);
        command(enable);
    #endif
}

/**
Sets the multiple byte character set to be used.

Code for each character set:
<ul>
<li> 0x00 - Japanese
<li> 0x01 - Korean
<li> 0x02 - Simplified Chinese
<li> 0x03 - Traditional Chinese
</ul>
@param  code    The character set code to be used.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setMultibyteCharset(uint8_t code) {
    #if (NORITAKE_OLED_MODEL_CLASS-7000)/100==9
        us_command('g', 0x0f);
        command(code);
    #endif
}

/**
Enables or disables the use of custom characters.

@param  enable  Enable of disable custom characters.
@return none
*/
void Noritake_OLED_GE7000::GE7000_useCustomChars(bool enable) {
    command(0x1b, '%', enable);
}

/**
Helper function for GE7000_defineCustomChar.

@return uint8_t The desired column.
*/
static inline uint8_t getColumn(const uint8_t *src, int col) {
    uint8_t out = 0;
    for (int i=0; i<8; i++)
        if (src[i] & (1<<(4-col))) out += 1<<(7-i);
    return out;
}

/**
code starts at 0x20 and ends at 0x27
<ul>
<li> 0 - GUD900 5x7 Format
<li> 1 - GUD900 7x8 Format
<li> 2 - CUU Format
</ul>
To print custom character, write the code of the character
to the display after using this function.

@param   code   The code for the character being defined.
@param   format The format of the character being defined.
@param   *data  The data for the character being defined.
@returns none
*/
void Noritake_OLED_GE7000::GE7000_defineCustomChar(uint8_t code, FontFormat format, const uint8_t *data) {
    command(0x1b, '&', 0x01);
    command(code);
    command(code);
    
    switch (format) {
    case CUUFormat:
        command(5);
        for (uint8_t i=0; i<5; i++)
            command(getColumn(data, i));
        break;
    
    case GU70005x7Format:
        command(5);
        print((const char*)data, 5);
        break;
    case GU70007x8Format:
        command(7);
        print((const char*)data, 7);
        break;
    }
}

/**
Deletes a previously defined custom character.

@param  code    Address of the custom character to be deleted.
@return none
*/
void Noritake_OLED_GE7000::GE7000_deleteCustomChar(uint8_t code) {
    command(0x01b, '?', 0x01);
    command(code);
}

/**
Sets the desired ASCII variant to be used.
Also called "International font select" in the GE7000 Datasheet.
Font codes:
<ul>
<li> 0x00 - America
<li> 0x01 - France
<li> 0x02 - Germany
<li> 0x03 - England
<li> 0x04 - Denmark 1
<li> 0x05 - Sweden
<li> 0x06 - Italy
<li> 0x07 - Spain 1
<li> 0x08 - Japan
<li> 0x09 - Norway
<li> 0x0A - Denmark 2
<li> 0x0B - Spain 2
<li> 0x0C - Latin America
<li> 0x0D - Korea
</ul>
@param  code   The code of the ASCII variant to be used.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setAsciiVariant(AsciiVariant code) {
    command(0x1b, 'R', code);
}

/**
Sets the desired character set.
Character set codes:
<ul>
<li> 0x00 - PC437(USA-Euro std)
<li> 0x01 - Katakana - Japanese
<li> 0x02 - PC850 (Multilingual)
<li> 0x03 - PC860 (Portuguese)
<li> 0x04 - PC863 (Canadian-French)
<li> 0x05 - PC865 (Nordic)
<li> 0x10 - WPC1252 (Latin)
<li> 0x11 - PC866 (Cryllic #2)
<li> 0x12 - PC852 (Latin 2)
<li> 0x13 - PC858 (Eastern European)
</ul>
@param  code   The code for the desired character set.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setCharset(Charset code) {
	if(code < 0x05 || (0x10 <= code && code <= 0x13)){
    	command(0x1b, 't', code);
	}
}

/**
Sets the scroll mode on the GE module.
Scroll modes:
<ul>
<li> 0x01 - Wrapping mode
<li> 0x02 - Vertical scroll mode
<li> 0x03 - Horizontal scroll mode
</ul>
@param  mode   The desired scroll mode.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setScrollMode(ScrollMode mode) {
    command(0x1f);
    command(mode);
}

/**
Sets the horizontal scroll speed on the GE series module.
Speed parameter specifics:
<ul>
<li> 0x00 <= speed <= 0x1f
<li> speed = 0x00 : Instantaneous Speed
<li> speed = 0x01 : IntTime / 2 dots
<li> speed = 0x02 - 0x1f : (n-1) * IntTime / dot
</ul>
@param  speed  The desired horizontal scroll speed.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setHorizScrollSpeed(uint8_t speed) {
    command(0x1f, 's', speed);
}

/**
Turns the display inversion OFF.

@return none
*/
void Noritake_OLED_GE7000::GE7000_invertOff() {
    command(0x1f, 'r', 0);
}

/**
Turns the display inversion ON.

@return none
*/
void Noritake_OLED_GE7000::GE7000_invertOn() {
    command(0x1f, 'r', 1);
}

/**
Sets the composition mode of the GUD module.

Composition modes:
<ul>
<li> 0x00 - Normal display write (not mixture display)
<li> 0x01 - OR display write
<li> 0x02 - AND display write
<li> 0x03 - XOR display write
</ul>
@param  mode  The desired composotion mode.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setCompositionMode(CompositionMode mode) {
    command(0x1f, 'w', mode);
}

/**
Sets the screen brightness of the GE module.

Screen brightness levels:
<ul>
<li> 0x01 - 12.5%
<li> 0x02 - 25.0%
<li> 0x03 - 37.5%
<li> 0x04 - 50.0%
<li> 0x05 - 62.5%
<li> 0x06 - 75.0%
<li> 0x07 - 87.5%
<li> 0x08 - 100%
</ul>
@param  level The desired brightness level.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setScreenBrightness(unsigned level) {
    if (level == 0)
        GE7000_displayOff();
    else if (level <= 100) {
        GE7000_displayOn();
        command(0x1f, 'X', (level*10 + 120)/125);
    }
}

/**
Suspends the program and waits for a user defined amount of time.

@param  time    The amount of time for the MCU to wait.
@return none
*/
void Noritake_OLED_GE7000::GE7000_wait(uint8_t time) {
    us_command('a', 0x01);
    command(time);
}

/**
Scrolls the screen based on certain parameters.

@param  x       The amount of pixels for the screen to scroll horizontally.
@param  y       The amount of pixels for the screen to scroll vertically.
@param times    The number of times the screen will scroll?
@param speed    The speed at which scrolling occurs.
@return none
*/
void Noritake_OLED_GE7000::GE7000_scrollScreen(unsigned x, unsigned y, unsigned times, uint8_t speed) {
    unsigned pos = (x*NORITAKE_OLED_LINES)+(y/8);
    us_command('a', 0x10);
    command(pos);
    command(pos>>8);
    command(times);
    command(times>>8);
    command(speed);
}

/**
Resets the blink settings on the module to all zeros.

@return none
*/
void Noritake_OLED_GE7000::GE7000_blinkScreen() {
    us_command('a', 0x11);
    command(0);
    command(0);
    command(0);
    command(0);
}

/**
Blinks the GE series module screen based on user input parameters.

@param  enable   Enables or disables screen blinking.
<ul>
                <li> 0x00 - Normal display
                <li> 0x01 - Blink display (alternatively Normal and Blank display)
                <li> 0x02 - Blink display (alternatively Normal and Reverse display) </ul>
@param  reverse  Enables or disables the reverse blinking pattern.
@param  onTime   The time that the display stays ON during blinking
@param  offTtime The time that the displays stays OFF during blinking.
@return none
*/
void Noritake_OLED_GE7000::GE7000_blinkScreen(bool enable, bool reverse, uint8_t onTime, uint8_t offTime, uint8_t times) {
    us_command('a', 0x11);
    command(enable? (reverse? 2: 1): 0);
    command(onTime);
    command(offTime);
    command(times);
}

/**
Turns tha display OFF.

@return none
*/
void Noritake_OLED_GE7000::GE7000_displayOff() {
    us_command('a', 0x40);
    command(0);
}

/**
Turns tha display ON.

@return none
*/
void Noritake_OLED_GE7000::GE7000_displayOn() {
    us_command('a', 0x40);
    command(0x01);
}

/**
Sets the screen saver mode for the GE series module.

Screen saver modes:
<ul>
<li> 0x00 - Display power OFF
<li> 0x01 - Display power ON
<li> 0x02 - All dots OFF
<li> 0x03 - All dots ON
<li> 0x04 - Repeat blink display with normal and reverse display
</ul>
@param  mode    The desired screensaver mode. (see ScreenSaver)
@return none
*/
void Noritake_OLED_GE7000::GE7000_screenSaver(ScreenSaver mode) {
    us_command('a', 0x40);
    command(mode);
}

/**
Sets the font style for the GE series module.

@param  proportional Enable or disable a proportional font style.
@param  evenSpacing  Enable or disable even spacing between characters.
@return none
*/
void Noritake_OLED_GE7000::GE7000_setFontStyle(bool proportional, bool evenSpacing) {
    us_command('g', 0x03);
    command(proportional * 2 + evenSpacing);
}

/**
Sets the font size for the GE series module.

Font size select only works on the 7933B module.

@param  x
@param  y
@param  tall 
@return none
*/
void Noritake_OLED_GE7000::GE7000_setFontSize(uint8_t x, uint8_t y, bool tall) {
    if (x<=4 && y<=2) {        
        us_command('g', 0x40);
        command(x);
        command(y);
        #if (NORITAKE_OLED_MODEL_CLASS-7000)/100==9
            us_command('g', 0x01);
            command(tall+1);
        #endif
    }
}

/**
Selects the current window.

@param  window  The desired window to select. (0-4)
@return none
*/
void Noritake_OLED_GE7000::GE7000_selectWindow(uint8_t window) {
    if (window <= 4)
        command(0x10 + window);
}

/**
Defines a specific window for the GE series module.

@param  window  The number of the window to be created. (1-4)
@param  x       The x coordinate of the new window.
@param  y       The y coordinate of the new window.
@param  width   The width of the new window.
@param  height  The height of the new window.
@return none
*/
void Noritake_OLED_GE7000::GE7000_defineWindow(uint8_t window, unsigned x, unsigned y, unsigned width, unsigned height) {
    us_command('w', 0x02);
    command(window);
    command(0x01);
    command_xy(x, y);
    command_xy(width, height);
}

/**
Deletes a previously defined window.

@param  window  The number of the window to be deleted. (1-4)
@return none
*/
void Noritake_OLED_GE7000::GE7000_deleteWindow(uint8_t window) {
    us_command('w', 0x02);
    command(window);
    command(0);
    command_xy(0, 0);
    command_xy(0, 0);
}

/**
Joins all of the screens into one base screen.

@return none
*/
void Noritake_OLED_GE7000::GE7000_joinScreens() {
    us_command('w', 0x10);
    command(0x01);
}

/**
Separates all of the screens into four separate screens.

@return none
*/
void Noritake_OLED_GE7000::GE7000_separateScreens() {
    us_command('w', 0x10);
    command(0);
}

/**
Prints a character to the display.

@param  c     The character to be sent.
@return none
*/
void Noritake_OLED_GE7000::print(char c) {
    command(c);
}

/**
Prints a string of characters to the display.

@param *str  The string to be sent.
@return none
*/
void Noritake_OLED_GE7000::print(const char *str) {
    while (*str)
        writePort(*str++);
}

/**
Prints a character buffer to the display.

@param  *buffer The buffer to be sent.
@param  size    The size of the buffer.
@return none
*/
void Noritake_OLED_GE7000::print(const char *buffer, size_t size) {
    while (size--)
        print(*buffer++);
}

/**
Prints a long to the display.

@param  number The number to be sent.
@param  base   The desired base of the number.
@return none
*/
void Noritake_OLED_GE7000::print(long number, uint8_t base) {
    if (number < 0) {
        print('-');
        number = -number;
    }
    printNumber(number, base);
}

/**
Prints an integer to the display.

@param  number The number to be sent.
@param  base   The desired base of the number.
@return none
*/
void Noritake_OLED_GE7000::print(int number, uint8_t base) {
    print((long)number, base);
}

/**
Prints an unsigned long to the display.

@param  number The number to be sent.
@param  base   The desired base of the number.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned long number, uint8_t base) {
    printNumber(number, base);
}

/**
Prints an unsigned integer to the display.

@param  number The number to be sent.
@param  base   The desired base of the number.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned number, uint8_t base) {
    print((unsigned long)number, base);
}

/**
Performs a carriage return and line feed on the GE display.

@return none
*/
void Noritake_OLED_GE7000::crlf() {
    GE7000_carriageReturn();
    GE7000_lineFeed();
}

/**
Prints a character to the display and then performs
a carriage return and line feed.

@param  c    The character to be written.
@return none
*/
void Noritake_OLED_GE7000::println(char c) {
    print(c);
    crlf();
}

/**
Prints a string of characters to the display and then
performs a carriage return and line feed.

@param  *str The string of characters to be written.
@return none
*/
void Noritake_OLED_GE7000::println(const char *str) {
    print(str);
    crlf();
}

/**
Prints a buffer of characters to the display and then
performs a carriage return and line feed.

@param  *buffer The character buffer to be written.
@param  size    Size of the character buffer.
@return none
*/
void Noritake_OLED_GE7000::println(const char *buffer, size_t size) {
    print(buffer, size);
    crlf();
}

/**
Prints a specific base long to the display and then performs a carriage
return and line feed.

@param  number The number to be written.
@param  base   The desired number base to be used.
@return none
*/
void Noritake_OLED_GE7000::println(long number, uint8_t base) {
    print(number, base);
    crlf();
}

/**
Prints a specific base number to the display and the performs abort
carriage return and line feed.

@param  number The number to be written.
@param  base   The desired number base to be used.
@return none
*/
void Noritake_OLED_GE7000::println(int number, uint8_t base) {
    println((long) number, base);
}

/**
Prints a specific base unsigned long to the display and then performs a carriage
return and line feed.

@param  number The number to be written.
@param  base   The desired number base to be used.
@return none
*/
void Noritake_OLED_GE7000::println(unsigned long number, uint8_t base) {
    print(number, base);
    crlf();
}

/**
Prints a specific base unsigned number to the display and the performs abort
carriage return and line feed.

@param  number The number to be written.
@param  base   The desired number base to be used.
@return none
*/
void Noritake_OLED_GE7000::println(unsigned number, uint8_t base) {
    println((unsigned long) number, base);
}

/**
Prints a specific base unsigned long to the display and then performs a carriage
return and line feed. This function is recursive.

@param  number The number to be written.
@param  base   The desired number base to be used.
@return none
*/
void Noritake_OLED_GE7000::printNumber(unsigned long number, uint8_t base) {
    if (number/base)
        printNumber(number/base, base);
    number %= base;
    print(number + (number < 10? '0': 'A' - 10));
}

/**
Draws an image to the display.

@param  width  The width of the image to be drawn.
@param  height The height of the image to be drawn.
@param  *data  The data of the image to be drawn.
@return none
*/
void Noritake_OLED_GE7000::GE7000_drawImage(unsigned width, uint8_t height, const uint8_t *data) {
    if (height > NORITAKE_OLED_HEIGHT) return;
    us_command('f', 0x11);
    command_xy(width, height);
    command((uint8_t) 1);
    for (unsigned i = 0; i<(height/8)*width; i++)
        command(data[i]);
}

/**
Draws an image that is stored in FROM.

Only works on the 7933B module.

@param  address The address of the image to be drawn.
@param  srcHeight The height of the defined source image.
@param  width The width of the image in dots (pixels).
@param  height The height of the image in dots (pixels).
@return none
*/
void Noritake_OLED_GE7000::GE7000_drawFROMImage(unsigned long address, uint8_t srcHeight, unsigned width, uint8_t height) {
    #if (NORITAKE_OLED_MODEL_CLASS-7000)/100==9      
        if (height > NORITAKE_OLED_HEIGHT) return;
        us_command('f', 0x10);
        command(0x01);
        command(address);
        command(address>>8);
        command(address>>16);
        command(srcHeight/8);
        command((srcHeight/8)>>8);
        command_xy(width, height);
        command((uint8_t) 1);
    #endif
}

static unsigned min(unsigned x, unsigned y) { return x<y? x: y; }

/**
Draws a filled-in rectangle on the display.

@param  x0   The x coordinate of the top-left corner of the rectangle.
@param  y0   The y coordinate of the top-left corner of the rectangle.
@param  x1   The x coordinate of the bottom-right corner of the rectangle.
@param  y1   The y coordinate of the bottom-right corner of the rectangle.
@param  on   Either enables (logic 1) or disables (logic 0) the rectangle from being drawn.
@return none
*/
void Noritake_OLED_GE7000::GE7000_fillRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, bool on) {
    x0 = min(NORITAKE_OLED_WIDTH, x0);
    x1 = min(NORITAKE_OLED_WIDTH, x1);
    y0 = min(NORITAKE_OLED_HEIGHT, y0);
    y1 = min(NORITAKE_OLED_HEIGHT, y1);
    if (y1<=y0 || x1<=x0) return;
    uint8_t bufw = 8, bufh = (y1-y0+7)/8*8;
    uint8_t *buf = (uint8_t*)alloca(bufh/8 * bufw);
    for (unsigned x = 0; x < x1-x0; x += bufw) {
        uint8_t part = (x + bufw < x1-x0)? bufw: (x1-x0) - x;
        memset(buf, 0, bufh/8 * bufw);
        if (on)
            for (uint8_t col = 0; col < part; col++) {
                for (uint8_t py = y0 % 8; py < y0 % 8 + min(y1-y0, 8); py++)
                    buf[col*bufh/8] |= 1 << (7-py);
                for (uint8_t row = (y0+7)/8; row < y1/8; row++)
                    buf[row - y0/8 + col*bufh/8] = 0xff;
                if (y0/8 != y1/8)
                    for (uint8_t py = 0; py < y1 % 8; py++)
                        buf[(y1-y0)/8 + col*bufh/8] |= 1 << (7-py);
            }
        GE7000_setCursor(x + x0, y0);
        GE7000_drawImage(bufw, bufh, buf);
    }
}

/**
Sends a byte command to the display.

@param  data The command data to be sent.
@return none
*/
void Noritake_OLED_GE7000::command(uint8_t data) {
    writePort(data);
}

/**
Sends xy coordinates to the display.
Y coordinates are divided into character columns.

@param  x    The desired x coordinate.
@param  y    The desired y coordinate.
@return none
*/
void Noritake_OLED_GE7000::command_xy(unsigned x, unsigned y) {
    command(x);
    command(x>>8);
    y /= 8;
    command(y);
    command(y>>8);
}

/**
Sends xy coordinates to the display.

@param  x    The desired x coordinate.
@param  y    The desired y coordinate.
@return none
*/
void Noritake_OLED_GE7000::command_xy1(unsigned x, unsigned y) {
    command(x);
    command(x>>8);
    command(y);
    command(y>>8);
}

/**
A commonly used command set that is generally called by
other functions. Starts witha unit separator command.

@param  group The command group identifier.
@param  cmd   The desired command.
@return none
*/
void Noritake_OLED_GE7000::us_command(uint8_t group, uint8_t cmd) {
   command(0x1f);
   command(0x28);
   command(group);
   command(cmd);
}

/**
Sends a group of three commands to the display.

@param  prefix Usually a unit separator.
@param  group  The command group identifier
@param  cmd    The desired command.
@return none
*/
void Noritake_OLED_GE7000::command(uint8_t prefix, uint8_t group, uint8_t cmd) {
   command(prefix);
   command(group);
   command(cmd);
}

/**
Prints a buffer of characters to the display at a specific xy coordinate.

@param  x       The desired x coordinate.
@param  y       The desired y coordinate.
@param  *buffer The character buffer to be written.
@param  len     The length of the buffer.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned x, uint8_t y, const char *buffer, uint8_t len) {
    #if NORITAKE_OLED_GENERATION == 'B'
        us_command('d', 0x30);
        command_xy1(x, y);
        command(0);
        command(len);
        while (len--)
            command(*buffer++);
    #endif
}

/**
Prints a character string to the display at a specific xy coordinate.

@param  x    The desired x coordinate.
@param  y    The desired y coordinate.
@param  *str The string to be written.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned x, uint8_t y, const char *str) {
    #if NORITAKE_OLED_GENERATION == 'B'
        print(x, y, str, strlen(str));
    #endif
}

/**
Prints a chracter to the display at a specific xy coordinate.

@param  x    The desired x coordinate.
@param  y    The desired y coordinate.
@param  c    The character to be written.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned x, uint8_t y, char c) {
    #if NORITAKE_OLED_GENERATION == 'B'
        print(x, y, &c, 1);
    #endif
}

/**
Prints the desired base of a number at a specific xy coordinate.

@param  x      The desired x coordinate.
@param  y      The desired y coordinate.
@param  number The number to be written.
@param  base   The number base to be used.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned x, uint8_t y, int number, uint8_t base) {
    #if NORITAKE_OLED_GENERATION == 'B'
        if (number < 0) {
            print(x, y, '-');
            print(-1, y, (unsigned)-number, base);        
        } else
            print(x, y, (unsigned)number, base);
    #endif
}

/**
Prints the desired base of an unsigned number at a specific xy coordinate.

@param  x      The desired x coordinate.
@param  y      The desired y coordinate.
@param  number The number to be written.
@param  base   The number base to be used.
@return none
*/
void Noritake_OLED_GE7000::print(unsigned x, uint8_t y, unsigned number, uint8_t base) {
    #if NORITAKE_OLED_GENERATION == 'B'
        char buf[16], *p = buf + sizeof buf;
        do
            *--p = number % base + (number % base < 10? '0': 'A' - 10);
        while (number /= base);
        print(x, y, p, buf + sizeof buf - p);
    #endif
}

/**
Draws the passed in image on the display.

@param   x      The top-left x coordinate of the image being drawn.
@param   y      The top-left y coordinate of the image being drawn.
@param   width  The width of the image being drawn.
@param   height The height of the image being drawn.
@param   *data  The data of the image being drawn.
@returns none
*/
void Noritake_OLED_GE7000::GE7000_drawImage(unsigned x, uint8_t y, unsigned width, uint8_t height, const uint8_t *data) {
    #if NORITAKE_OLED_GENERATION == 'B'
        us_command('d', 0x21);
        command_xy1(x, y);
        command_xy1(width, height);
        command(0x01);
        for (unsigned i = 0; i<(height/8)*width; i++)
            command(data[i]);
    #endif
}

/**
Draws an image on the display.

@param   x         The top-left x coordinate of the image being drawn.
@param   y         The top-left y coordinate of the image being drawn.
@param   area      Indicates where the image will be drawn. Flash or screen.
@param   address   The address of the image to be drawn.
@param   srcHeight The height of the defined image.
@param   width     The width of the image being drawn.
@param   height    The height of the image being drawn.
@param   offsetx   The x coordinate offset needed to draw the image.
@param   offsety   The y coordinate offset needed to draw the image.
@returns none
*/
void Noritake_OLED_GE7000::GE7000_drawImage(unsigned x, uint8_t y, ImageMemoryArea area, unsigned long address, uint8_t srcHeight, unsigned width, uint8_t height, unsigned offsetx, unsigned offsety) {
    #if NORITAKE_OLED_GENERATION == 'B'
        if (height > NORITAKE_OLED_HEIGHT) return;
        us_command('d', 0x20);
        command_xy1(x, y);
        command(area);
        command(address);
        command(address>>8);
        command(address>>16);
        command(srcHeight/8);
        command(srcHeight/8>>8);
        command_xy1(offsetx, offsety);
        command_xy1(width, height);
        command(0x01);
    #endif
}

/**
Draws an image on the display.

@param   x         The top-left x coordinate of the image being drawn.
@param   y         The top-left y coordinate of the image being drawn.
@param   area      Indicates where the image will be drawn. Flash or screen.
@param   address   The address of the image to be drawn.
@param   width     The width of the image being drawn.
@param   height    The height of the image being drawn.
@returns none
*/
void Noritake_OLED_GE7000::GE7000_drawImage(unsigned x, uint8_t y, ImageMemoryArea area, unsigned long address, unsigned width, uint8_t height) {
    #if NORITAKE_OLED_GENERATION == 'B'
        GE7000_drawImage(x, y, area, address, (height + 7) & ~7, width, height, 0, 0);
    #endif
}

/**
Program space print.

@param  *str The string of characters to be written.
@return none
*/
void Noritake_OLED_GE7000::print_p(const char *str) {
    while (pgm_read_byte(str))
        writePort(pgm_read_byte(str++));
}

/**
Program space print.

@param  x       The desired x coordinate.
@param  y       The desired y coordinate.
@param  *buffer The character buffer to be written.
@param  len     The length of the character buffer.
@return none
*/
void Noritake_OLED_GE7000::print_p(unsigned x, uint8_t y, const char *buffer, uint8_t len) {
    #if NORITAKE_OLED_GENERATION == 'B'
        us_command('d', 0x30);
        command_xy1(x, y);
        command(0);
        command(len);
        while (len--)
            command(pgm_read_byte(buffer++));
    #endif
}

/**
Program space print.

@param  x    The desired x coordinate.
@param  y    The desired y coordinate.
@param  *str The character string to be written.
@return none
*/
void Noritake_OLED_GE7000::print_p(unsigned x, uint8_t y, const char *str) {
    #if NORITAKE_OLED_GENERATION == 'B'
        const char *end = str;
        while (pgm_read_byte(end)) end++;
        print_p(x, y, str, end - str);
    #endif
}

/**
Program space image draw.

@param width The width of the image.
@param height The height of the image.
@param *data The data of the image to be drawn.
*/
void Noritake_OLED_GE7000::GE7000_drawImage_p(unsigned width, uint8_t height, const uint8_t *data) {
    if (height > NORITAKE_OLED_HEIGHT) return;
    us_command('f', 0x11);
    command_xy(width, height);
    command((uint8_t) 1);
    for (unsigned i = 0; i<(height/8)*width; i++)
        command(pgm_read_byte(data+i));
}

/**
Program space image draw.
*/
void Noritake_OLED_GE7000::GE7000_drawImage_p(unsigned x, uint8_t y, unsigned width, uint8_t height, const uint8_t *data) {
    #if NORITAKE_OLED_GENERATION == 'B'
        us_command('d', 0x21);
        command_xy1(x, y);
        command_xy1(width, height);
        command(0x01);
        for (unsigned i = 0; i<(height/8)*width; i++)
            command(pgm_read_byte(data+i));
    #endif
}
