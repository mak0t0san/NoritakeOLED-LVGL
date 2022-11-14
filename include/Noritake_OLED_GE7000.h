/**
Purpose: Function header file for the GE-7000 command set. 
Source file in the GE-7000 Code Library.

PN: ME-N60-0
*/

#include <stdint.h>
#include <stddef.h>

/**
 * Identifies the memory area to use in an operation.
 */
enum ImageMemoryArea {
    FlashImageArea = 1,
    ScreenImageArea = 2
};

/**
 * Identifies the module's scrolling and wrapping behavior.
 */
enum ScrollMode {
    WrappingMode =    1,
    VertScrollMode =  2,
    HorizScrollMode = 3
};

/**
 * Identifies the way that new image and text are combined with the contents that are already on the screen.
 */
enum CompositionMode {
    NormalCompositionMode = 0,
    OrCompositionMode =     1,
    AndCompositionMode =    2,
    XorCompositionMode =    3
};

/**
 * Enable/disable the screen saver.
 */
enum ScreenSaver {
    AllDotsOffSaver = 2,
    AllDotsOnSaver =  3,
    InvertSaver =   4
};

/**
 * Identifies the size and data format.
 */
enum FontFormat {
     GU70005x7Format =0,
     GU70007x8Format =1,
     CUUFormat =    2,
     LCDFormat =    CUUFormat     
};

/**
 * Identifies national ASCII variants.
 */
enum AsciiVariant {
    AmericaAscii =  0,
    FranceAscii =   1,
    GermanyAscii =  2,
    EnglandAscii =  3,
    Denmark1Ascii = 4,
    SwedenAscii =  5,
    ItalyAscii =    6,
    Spain1Ascii =   7,
    JapanAscii =    8,
    NorwayAscii =   9,
    Denmark2Ascii = 10,
    Spain2Ascii =   11,
    LatinAmericaAscii = 12,
    KoreaAscii = 13
};

/**
 * Identifies the character set code page.
 */
enum Charset {
    CP437 = 0, EuroStdCharset = CP437,
    Katakana = 1,
    CP850 = 2, MultilingualCharset = CP850,
    CP860 = 3, PortugeseCharset = CP860,
    CP863 = 4, CanadianFrenchCharset = CP863,
    CP865 = 5, NordicCharset = CP865,
    CP1252 = 0x10,
    CP866 = 0x11, Cyrillic2Charset = CP866,
    CP852 = 0x12, Latin2Charset = CP852,
    CP858 = 0x13
};

/**
 * Identifies a multi-byte character set.
 */
enum MultibyteCharset {
	ShiftJIS = 0, JapaneseMBCS = ShiftJIS,
	KSC5601 = 1, KoreanMBCS = KSC5601,
	GB2312 = 2, SimplifiedChineseMBCS = GB2312,
	Big5 = 3, TraditionalChineseMBCS = Big5
};

class Noritake_OLED_GE7000 {

    void initialState();
    void printNumber(unsigned long number, uint8_t base);
    void printNumber(unsigned x, uint8_t y, unsigned long number, uint8_t base);
    void command(uint8_t data);
    void us_command(uint8_t group, uint8_t cmd);
    void command(uint8_t prefix, uint8_t group, uint8_t cmd);
    void command_xy(unsigned x, unsigned y);
    void command_xy1(unsigned x, unsigned y);
    void crlf();

public:

	void GE7000_displayAngleControl(uint8_t angle);
    void GE7000_back();
    void GE7000_forward();
    void GE7000_lineFeed();
    void GE7000_home();
    void GE7000_carriageReturn();
    void GE7000_setCursor(unsigned x, unsigned y);
    void GE7000_clearScreen();
    void GE7000_cursorOn();
    void GE7000_cursorOff();
    void GE7000_init();
    void GE7000_reset();
    void GE7000_useMultibyteChars(bool enable);
    void GE7000_setMultibyteCharset(uint8_t code);
    void GE7000_useCustomChars(bool enable);
    void GE7000_defineCustomChar(uint8_t code, FontFormat format, const uint8_t *data);
    void GE7000_deleteCustomChar(uint8_t code);
    void GE7000_setAsciiVariant(AsciiVariant code);
    void GE7000_setCharset(Charset code);
    void GE7000_setScrollMode(ScrollMode mode);
    void GE7000_setHorizScrollSpeed(uint8_t speed);
    void GE7000_invertOn();
    void GE7000_invertOff();
    void GE7000_setCompositionMode(CompositionMode mode);
    void GE7000_setScreenBrightness(unsigned level);
    void GE7000_wait(uint8_t time);
    void GE7000_scrollScreen(unsigned x, unsigned y, unsigned count, uint8_t speed);
    void GE7000_blinkScreen();
    void GE7000_blinkScreen(bool enable, bool reverse, uint8_t on, uint8_t off, uint8_t times);
    void GE7000_displayOn();
    void GE7000_displayOff();
    void GE7000_screenSaver(ScreenSaver mode);
    void GE7000_drawImage(unsigned width, uint8_t height, const uint8_t *data);
    void GE7000_drawFROMImage(unsigned long address, uint8_t srcHeight, unsigned width, uint8_t height);
    void GE7000_setFontStyle(bool proportional, bool evenSpacing);
    void GE7000_setFontSize(uint8_t x, uint8_t y, bool tall);
    void GE7000_selectWindow(uint8_t window);
    void GE7000_defineWindow(uint8_t window, unsigned x, unsigned y, unsigned width, unsigned height);
    void GE7000_deleteWindow(uint8_t window);
    void GE7000_joinScreens();
    void GE7000_separateScreens();

    void print(char c);
    void print(const char *str);
    void print(const char *buffer, size_t size);
    void print(int number, uint8_t base);
    void print(unsigned number, uint8_t base);
    void print(long number, uint8_t base);
    void print(unsigned long number, uint8_t base);
    void println(char c);
    void println(const char *str);
    void println(const char *buffer, size_t size);
    void println(int number, uint8_t base);
    void println(unsigned number, uint8_t base);
    void println(long number, uint8_t base);
    void println(unsigned long number, uint8_t base);

    void GE7000_fillRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, bool on=true);
    
    void print(unsigned x, uint8_t y, char c);
    void print(unsigned x, uint8_t y, const char *str);
    void print(unsigned x, uint8_t y, const char *buffer, uint8_t len);
    void print(unsigned x, uint8_t y, int number, uint8_t base);
    void print(unsigned x, uint8_t y, unsigned number, uint8_t base);
    void GE7000_drawImage(unsigned x, uint8_t y, unsigned width, uint8_t height, const uint8_t *data);
    void GE7000_drawImage(unsigned x, uint8_t y, ImageMemoryArea area, unsigned long address, uint8_t srcHeight, unsigned width, uint8_t height, unsigned offsetx, unsigned offsety);
    void GE7000_drawImage(unsigned x, uint8_t y, ImageMemoryArea area, unsigned long address, unsigned width, uint8_t height);
    
    void print_p(const char *str);
    void print_p(unsigned x, uint8_t y, const char *str);
    void print_p(unsigned x, uint8_t y, const char *buffer, uint8_t len);
    void GE7000_drawImage_p(unsigned width, uint8_t height, const uint8_t *data);
    void GE7000_drawImage_p(unsigned x, uint8_t y, unsigned width, uint8_t height, const uint8_t *data);
};
