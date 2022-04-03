//For arduino Mega
////////////////////////////////////////////////////////////////////
#define X_STEP_HIGH             PORTH |=  0b00010000; //D7
#define X_STEP_LOW              PORTH &= ~0b00010000;

//z - motor step pin
//#define Z_STEP_HIGH             PORTL |=  0b00000010; //D48
//#define Z_STEP_LOW              PORTL &= ~0b00000010;

//x motor pins
#define X_DIR_PIN          6
#define X_STEP_PIN         7
#define X_ENABLE_PIN       52

//z motor pins
//#define Z_DIR_PIN          50
//#define Z_STEP_PIN         48 //add
//#define Z_ENABLE_PIN       46

//////////////////////////////////////////////////////////////////
//pump1 motor test
#define Z_DIR_PIN          44
#define Z_STEP_PIN         42
#define Z_ENABLE_PIN       40

//pump1 motor test
#define Z_STEP_HIGH             PORTL |=  0b10000000; //D42
#define Z_STEP_LOW              PORTL &= ~0b10000010;
//////////////////////////////////////////////////////////////////
//LCD User defined Parameters
double wipe_Distance = 3; // (inches)
int num_Cycles = 10; //number of cycles

//////////////////////////////////////////////////////////////////
//X-motor Config
double x_Gear = 12;  //X motor gear diameter (mm)
int rev_Step = 1600; //Steps Per revolution
double x_circumference = (3.14159 * x_Gear * 0.0393); //x motor gear circumference (inches) 
volatile int x_movement = (rev_Step * (wipe_Distance / x_circumference)); // X axis movement in steps

boolean xPosition_Update = false;
int xcelleraion = 100;
int xMin_Interval = 15;

//////////////////////////////////////////////////////////////////
//Z-motor Config
boolean zPosition_Update = false;
int z_movement = 1000;
int zcelleration = 1000;
int zMin_Interval = 50;

//////////////////////////////////////////////////////////////////
//Force Controller

double Force;

// variables will change:
int distance;
int SPEED;
int done = 0;
boolean M_direction;
double Output_Position;

//////////////////////////////////////////////////////////////////
//Load Cell Reading


//********************************************************************************************************************
// LCD Parameter Definitions
//********************************************************************************************************************

// Horizontal Alignment
#define LCDWidth                      128
#define ALIGN_CENTER(t)               ((LCDWidth - (u8g.getStrWidth(t))) / 2)
#define ALIGN_RIGHT(t)                (LCDWidth -  u8g.getStrWidth(t))
#define ALIGN_LEFT                    0

// settings for u8g lib and LCD
#define _LCDML_DISP_w                 128            // LCD width
#define _LCDML_DISP_h                 64             // LCD height

// font settings
#define _LCDML_DISP_font              u8g_font_6x13  // u8glib font (more fonts under u8g.h line 1520 ...)
#define _LCDML_DISP_big_font          u8g_font_9x18  // bigger font
#define _LCDML_DISP_font_w            6              // font width
#define _LCDML_DISP_font_h            13             // font height

// cursor settings
#define _LCDML_DISP_cursor_char       ">"            // cursor char
#define _LCDML_DISP_cur_space_before  2              // cursor space between
#define _LCDML_DISP_cur_space_behind  4              // cursor space between

// menu position and size
#define _LCDML_DISP_box_x0            0              // start point (x0, y0)
#define _LCDML_DISP_box_y0            0              // start point (x0, y0)
#define _LCDML_DISP_box_x1            128            // width x  (x0 + width)
#define _LCDML_DISP_box_y1            64             // hight y  (y0 + height)
#define _LCDML_DISP_draw_frame        1              // draw a box around the menu

 // scrollbar width
#define _LCDML_DISP_scrollbar_w       6  // scrollbar width (if this value is < 3, the scrollbar is disabled)

// nothing change here
#define _LCDML_DISP_cols_max          ((_LCDML_DISP_box_x1-_LCDML_DISP_box_x0)/_LCDML_DISP_font_w)
#define _LCDML_DISP_rows_max          ((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0)/_LCDML_DISP_font_h))/_LCDML_DISP_font_h)

// rows and cols
// when using more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
#define _LCDML_DISP_rows              _LCDML_DISP_rows_max  // max rows
#define _LCDML_DISP_cols              20                   // max cols

// END
//********************************************************************************************************************
