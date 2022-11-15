// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: PowerMonitorMono

#include "ui.h"
#include "ui_helpers.h"
#include <math.h>

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Screen1;
lv_obj_t *ui_Screen1_Panel1;
lv_obj_t *ui_Screen1_Chart1;
lv_obj_t *ui_Screen1_Arc1;
lv_obj_t *ui_Screen1_Label1;
lv_obj_t *ui_Screen1_Label3;
lv_obj_t *ui_Screen1_Label2;
lv_obj_t * ui_Screen1_Panel2;
lv_chart_series_t *chart_series;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 1
#error "LV_COLOR_DEPTH should be 8bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Panel1, 100);
    lv_obj_set_height(ui_Screen1_Panel1, 29);
    lv_obj_set_x(ui_Screen1_Panel1, 2);
    lv_obj_set_y(ui_Screen1_Panel1, 5);
    lv_obj_clear_flag(ui_Screen1_Panel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Screen1_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Screen1_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Screen1_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Screen1_Panel1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Chart1 = lv_chart_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Chart1, lv_pct(100));
    lv_obj_set_height(ui_Screen1_Chart1, lv_pct(100));
    lv_obj_set_align(ui_Screen1_Chart1, LV_ALIGN_CENTER);
    lv_obj_set_style_border_width(ui_Screen1_Chart1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_Screen1_Chart1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_Screen1_Chart1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_chart_set_type(ui_Screen1_Chart1, LV_CHART_TYPE_BAR);
    lv_chart_set_range(ui_Screen1_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_div_line_count(ui_Screen1_Chart1, 0, 0);
    chart_series = lv_chart_add_series(ui_Screen1_Chart1, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);

    /*Set the next points on 'ser1'*/
    for (int i = 0; i < 10; i++)
    {
        chart_series->y_points[i] = (lv_coord_t)(50 + sin(i) * 50);
    }

    lv_chart_refresh(ui_Screen1_Chart1);

    ui_Screen1_Arc1 = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Arc1, 64);
    lv_obj_set_height(ui_Screen1_Arc1, 64);
    lv_obj_set_align(ui_Screen1_Arc1, LV_ALIGN_TOP_RIGHT);
    lv_arc_set_value(ui_Screen1_Arc1, 33);
    lv_obj_set_style_border_color(ui_Screen1_Arc1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Screen1_Arc1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Screen1_Arc1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Label1 = lv_label_create(ui_Screen1_Arc1);
    lv_obj_set_width(ui_Screen1_Label1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Screen1_Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_Screen1_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label1, "50");
    lv_obj_set_style_text_color(ui_Screen1_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen1_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Label3 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Screen1_Label3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Screen1_Label3, 12);
    lv_obj_set_y(ui_Screen1_Label3, 0);
    lv_label_set_text(ui_Screen1_Label3, "POWER");
    lv_obj_set_style_text_color(ui_Screen1_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen1_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_Label3, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Label3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Label3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Label3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Label3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Label3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

       ui_Screen1_Panel2 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Panel2, 183);
    lv_obj_set_height(ui_Screen1_Panel2, 28);
    lv_obj_set_align(ui_Screen1_Panel2, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_Screen1_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Label2 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_Label2, lv_pct(100));
    lv_obj_set_height(ui_Screen1_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label2, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_Screen1_Label2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_Screen1_Label2, "The quick brown fox jumps over the lazy dog.");
    lv_obj_set_style_text_color(ui_Screen1_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen1_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_Label2, &ui_font_firacode16, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
