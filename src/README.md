This is a sample project that shows how you can use the LVGL library with a Noritake OLED display.

In particular, I am using a GE256x64B display

Using LVGL makes it easy to create graphical interfaces and you're no longer constrained by the limitations of the
Noritake OLED display, such as positioning an image at a coordinate that's a multiple of 8, or font limitations. 

LVGL is smart to only re-render parts of the display that are changing which means you don't have to redraw the entire screen for a refresh.

