#include <Arduino.h>

#include <GE7000_Serial_SPI.h>
#include <Noritake_VFD_GE7000.h>
#include "lvgl.h"
#include "ui.h"

static GE7000_Serial_SPI interface(13, 12, 14, 27, 25); // SIN,BUSY,SCK,RESET,CS
static Noritake_VFD_GE7000 oled;

static const uint16_t screen_width = 256;
static const uint16_t screen_height = 64;

// The buffer size determines how many bytes wil be drawn at a time
// In this example, we take the screen width and multiply by the height, then divide by 4
// Dividing by 4 will mean that we'll have a buffer big enough to draw 1/4th of the screen a time
// Or in another words, we'll need to send data to the screen 4 times to make a full image
#define DISP_BUF_SIZE screen_width *screen_height / 4

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[DISP_BUF_SIZE];

/**
 * @brief THis function is used by LVGL to take the rendered image and then send the data to the screen.
 *
 * @param disp
 * @param area
 * @param color_p
 */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  // Calculate width
  const uint32_t w = (area->x2 - area->x1 + 1);

  // Calculate height
  const uint32_t h = (area->y2 - area->y1 + 1);

  // The data from LVGL has one byte per pixel.  We want 1 byte (8 bits) for 8 vertical pixels,
  // therefore we only need 1/8th the size of an arry
  const uint32_t array_size = w * h / 8;

  // Initialize our new array
  uint8_t newArray[array_size];

  u_int32_t x, y, idx;
  // Loop through each pixel, going from one column at a time
  for (x = 0; x < w; x++)
  {
    for (y = 0; y < h; y++)
    {
      // `>> 3` is the same as dividing by 2^3 (8) and truncating but just a bit more performant
      idx = (y >> 3) + ((h >> 3) * x);
      const lv_color_t color = color_p[x + (y * w)];

      if (lv_color_brightness(color) > 128)
      {
        // Set the bit to 1
        newArray[idx] |= (1 << (7 - y % 8));
      }
      else
      {
        // Set the appropriate bit to 0
        newArray[idx] &= ~(1 << (7 - y % 8));
      }
    }
  }

  // drawImage is expecting a byte array where there first byte contains data for the first 8 vertical pixels.
  // The data then goes from top to bottom, then left to right
  oled.GE7000_drawImage(area->x1, area->y1, w, h, newArray);

  // Let lvgl know that flushing is finished
  lv_disp_flush_ready(disp);
}

/**
 * @brief The Noritake OLEDs require an image to have a height in a multiple of 8, as it draws one 8 pixel tall column at a time.
 *
 * @param disp_drv
 * @param area
 */
void my_rounder(lv_disp_drv_t *disp_drv, lv_area_t *area)
{
  // Round down to the nearest multiple of 8
  // For example, 7 becomes 0,  8 becomes 8, 9 becomes 8, 17 becomes 16
  // ~(0x7) (NOT(7)) 7 in binary is 0000 0111, flipping the bits of that becomes 1111 1000
  // A bitwise AND will set the first three bits to 0 preventing it from not being a multiple of 8
  area->y1 &= ~(0x7);

  // Round up to the nearest multiple of 8, then -1
  // For example, 4 becomes 7,  8 becomes 15, 9 becomes 15, 17 becomes 23
  // Bitwise OR the value with 0000 0111
  area->y2 |= (0x7);
}

void setup()
{
  lv_init(); // Initialize LVGL library

  oled.begin(screen_width, screen_height);
  oled.interface(interface); // select which interface to use
  oled.isModelClass(7933);
  oled.isGeneration('B'); // Uncomment this for B generation
  oled.GE7000_reset();    // reset module
  oled.GE7000_init();     // initialize module

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, DISP_BUF_SIZE);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screen_width;
  disp_drv.ver_res = screen_height;

  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.rounder_cb = my_rounder;
  lv_disp_drv_register(&disp_drv);

  // Use monochrome theme, since we're using a monochrome OLED
  lv_disp_t *disp = lv_disp_get_default();
  lv_theme_t *theme_mono = lv_theme_mono_init(disp, true, LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, theme_mono);
  ui_init();
}

bool chart_updated = false;
void loop()
{
  // Generate some test data that changes the value on the screen
  const long time = millis() / 100L;
  const bool direction = (time / 100) % 2;
  const uint16_t arc_value = (direction ? 100 - (time % 100) : (time % 100));

  lv_arc_set_value(ui_Screen1_Arc1, arc_value);
  lv_label_set_text(ui_Screen1_Label1, std::to_string(arc_value).c_str());

  if (!(time % 4))
  {
    if (!chart_updated)
    {
      for (int i = 0; i < 10; i++)
      {
        chart_series->y_points[i] = (lv_coord_t)(50 + sin(time + i) * 50);
      }

      lv_chart_refresh(ui_Screen1_Chart1);
      chart_updated = true;
    }
  }
  else
  {
    chart_updated = false;
  }

  lv_task_handler(); // Needs to be called periodically, about every 5ms according ot the docs
  oled.GE7000_setScreenBrightness(arc_value);
  delay(5);
}
