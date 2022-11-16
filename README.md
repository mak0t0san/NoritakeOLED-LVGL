This is a sample project that shows how you can use the LVGL library with a Noritake OLED display.

In particular, I am using a GE256x64B display

Using LVGL makes it easy to create graphical interfaces and you're no longer constrained by the limitations of the
Noritake OLED display, such as positioning an image at a coordinate that's a multiple of 8, or font limitations. 

LVGL is smart to only re-render parts of the display that are changing which means you don't have to redraw the entire screen for a refresh.

The Noritake OLED runs on 3.3V.  I have this connected to an ESP32 development board (Wemos D1 R32) which uses 3.3V outputs, but also using the Arduino framework.  I have not tested this out on an 8-bit ATMEL based Arduino chip which runs on 5V and wouldn't recomment it either.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/rjNBjvUzsLw/0.jpg)](http://www.youtube.com/watch?v=rjNBjvUzsLw "Noritake OLED LVGL demo")
