// include libs
#include <LCDMenuLib2.h>
#include <U8glib.h>

// setup u8g object
U8GLIB_ST7920_128X64 u8g(13, 11, 10, U8G_PIN_NONE);

// Horizontal Alignment
#define LCDWidth                      128
#define ALIGN_CENTER(t)               ((LCDWidth - (u8g.getStrWidth(t))) / 2)
#define ALIGN_RIGHT(t)                (LCDWidth -  u8g.getStrWidth(t))
#define ALIGN_LEFT                    0

// settings for u8g lib and LCD
#define _LCDML_DISP_w                 128            // LCD width
#define _LCDML_DISP_h                 64             // LCD height

// font settings
#define _LCDML_DISP_font              u8g_font_ncenB08  // u8glib font 
#define _LCDML_DISP_font_w            4              // font width
#define _LCDML_DISP_font_h            14             // font height

// cursor settings
#define _LCDML_DISP_cursor_char       "="            // cursor char
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
// when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
// the program needs more ram with this changes
#define _LCDML_DISP_rows              _LCDML_DISP_rows_max  // max rows
#define _LCDML_DISP_cols              20                   // max cols

// Prototypes
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// Objects
LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// LCDML MENU/DISP
// LCDML_0        => layer 0
// LCDML_0_X      => layer 1
// LCDML_0_X_X    => layer 2
// LCDML_0_X_X_X  => layer 3
// LCDML_0_...    => layer ...
                                                ///!!!!!/// DO WE NEED TO HOME THE X AXIS AT ALL??? or should we home it to the center?
// For beginners                           
// LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)    
LCDML_add         (0  , LCDML_0         , 1  , "===== HOME ======", NULL);                    // mFunc_information -- this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (1  , LCDML_0         , 2  , "Home Z Axis"      , mFunc_timer_info);        // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (2  , LCDML_0         , 3  , "Set Wiping Distance", NULL);                    // NULL = no menu function
LCDML_add         (3  , LCDML_0_3       , 1  , "=== Parameters ====", NULL);                    // NULL = no menu function
LCDML_add         (4  , LCDML_0_3_1     , 1  , ""                 , NULL);                    // NULL = no menu function
LCDML_add         (5  , LCDML_0_3_1     , 2  , ""                 , NULL);                    // NULL = no menu function
LCDML_add         (6  , LCDML_0_3_1_2   , 1  , ""                 , NULL);                    // NULL = no menu function
LCDML_add         (7  , LCDML_0_3_1_2   , 2  , ""                 , NULL);                    // NULL = no menu function
LCDML_add         (8  , LCDML_0_3_1_2   , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (9  , LCDML_0_3_1     , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (10 , LCDML_0_3       , 2  , "Set Num. of Cycles",mFunc_p2);                // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (11 , LCDML_0_3       , 3  , "Set Init. Position",mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (12 , LCDML_0         , 4  , "Start Wiping"     , NULL);                    // NULL = no menu function
LCDML_add         (13 , LCDML_0_3       , 4  , "Set Wiping Distance", mFunc_goToRootMenu);      // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (14 , LCDML_0_3       , 5  , "Set Wiping Force" , mFunc_jumpTo_timer_info); // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (15 , LCDML_0_3       , 6  , "Reset Parameters" , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab

// Advanced menu (for profit) part with more settings
// Example for one function and different parameters
// It is recommend to use parameters for switching settings like, (small drink, medium drink, big drink) or (200ml, 400ml, 600ml, 800ml) ...
// the parameter change can also be released with dynParams on the next example
// LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (16 , LCDML_0         , 5  , NULL,          ""  , NULL,                0,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_add         (17 , LCDML_0_3       , 7  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_addAdvanced (18 , LCDML_0_5       , 1  , NULL,          ""  , mFunc_para,       20,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced (19 , LCDML_0_5       , 2  , NULL,          ""  , mFunc_para,       30,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_add         (20 , LCDML_0_5       , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab

// Example for dynamic content
// 1. set the string to ""
// 2. use type  _LCDML_TYPE_dynParam   instead of    _LCDML_TYPE_default
// this function type can not be used in combination with different parameters
// LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (21 , LCDML_0         , 6  , NULL,          ""                  , mDyn_para,                0,   _LCDML_TYPE_dynParam);                     // NULL = no menu function

// Example for conditions (for example for a screensaver)
// 1. define a condition as a function of a boolean type -> return false = not displayed, return true = displayed
// 2. set the function name as callback (remove the braces '()' it gives bad errors)
// LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (22 , LCDML_0         , 7  , COND_hide,  ""        , mFunc_screensaver,        0,   _LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab
// The fourth element (false in this case) is a condition which needs to be implemented as a function
// and it shoud return a boolean true or false based on checked condition

// ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    22

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);




// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{
  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();

  // Enable Screensaver (screensaver menu function, time to activate in ms)
  LCDML.SCREEN_enable(mFunc_screensaver, 30000); // set to 10 seconds
  //LCDML.SCREEN_disable();

  // Some needful methods

  // You can jump to a menu function from anywhere with
  //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name
}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{
//  u8g.firstPage();
//  do
//  {
//    display_logo();
//  }while(u8g.nextPage() && ~(LCDML.BT_checkAny()));

  //this function must called here, do not delete it
  LCDML.loop();
}


// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_glcd_tft_box_x1 > _LCDML_glcd_tft_w)
# error _LCDML_glcd_tft_box_x1 is to big
# endif

# if(_LCDML_glcd_tft_box_y1 > _LCDML_glcd_tft_h)
# error _LCDML_glcd_tft_box_y1 is to big
# endif