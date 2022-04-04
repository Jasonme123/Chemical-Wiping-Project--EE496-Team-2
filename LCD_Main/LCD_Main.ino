// include libs
#include <LCDMenuLib2.h>
#include <U8glib.h>
#include "config.h"
#include "Camera_Control.h"
#include "Pump_Control.h"
#include "Force_Sensors_Reading.h"
#include "Force_Control.h"
#include "Homing.h"
#include "wiping_loop.h"


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
#define _LCDML_DISP_font_w            5              // font width
#define _LCDML_DISP_font_h            14             // font height

// cursor settings
#define _LCDML_DISP_cursor_char       ">" 

// cursor char
#define _LCDML_DISP_cur_space_before  2              // cursor space between
#define _LCDML_DISP_cur_space_behind  4              // cursor space between

// menu position and size
#define _LCDML_DISP_box_x0            0              // start point (x0, y0)
#define _LCDML_DISP_box_y0            0              // start point (x0, y0)
#define _LCDML_DISP_box_x1            128            // width x  (x0 + width)
#define _LCDML_DISP_box_y1            64             // hight y  (y0 + height)
#define _LCDML_DISP_draw_frame        1              // draw a box around the menu

// scrollbar width
#define _LCDML_DISP_scrollbar_w       6              // scrollbar width (if this value is < 3, the scrollbar is disabled)

// nothing change here
#define _LCDML_DISP_cols_max          ((_LCDML_DISP_box_x1-_LCDML_DISP_box_x0)/_LCDML_DISP_font_w)
#define _LCDML_DISP_rows_max          ((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0)/_LCDML_DISP_font_h))/_LCDML_DISP_font_h)

// rows and cols
#define _LCDML_DISP_rows              _LCDML_DISP_rows_max  // max rows
#define _LCDML_DISP_cols              20                    // max cols

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
                                               
// LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function) 
   
LCDML_add         (0  , LCDML_0         , 1  , "===== HOME ======", logo_display);                   
LCDML_add         (1  , LCDML_0         , 2  , "Home Z-Axis"      , NULL);        
LCDML_add         (2  , LCDML_0         , 3  , "Set Parameters"   , NULL);   
LCDML_add         (3  , LCDML_0         , 4  , "Start Testing Cycle", NULL);  
LCDML_add         (4  , LCDML_0         , 5  , "Home X&Z Axes"    , NULL);  
LCDML_add         (5  , LCDML_0         , 6  , "Tare Load Cells"  , NULL);  
LCDML_add         (6  , LCDML_0         , 7  , "Cycle Count"      , cycle_count_display);  

LCDML_add         (7  , LCDML_0_6       , 1  , "=TARE LOAD CELLS=", NULL);                    
LCDML_add         (8  , LCDML_0_6       , 2  , "Start"            , z_homing);                   
LCDML_add         (9  , LCDML_0_6       , 3  , "Back"             , mFunc_back_by_1); 
 
LCDML_add         (10 , LCDML_0_2       , 1  , "= Z-AXIS HOMING =", NULL);                    
LCDML_add         (11 , LCDML_0_2       , 2  , "Start Homing"     , z_homing);                   
LCDML_add         (12 , LCDML_0_2       , 3  , "Back"             , mFunc_back_by_1);   

LCDML_add         (13 , LCDML_0_4       , 1  , "==TESTING CYCLE==", NULL);                    
LCDML_add         (14 , LCDML_0_4       , 2  , "Start Testing"    , testing_cycle);     
LCDML_add         (15 , LCDML_0_4       , 3  , "Back"             , mFunc_back_by_1); 

LCDML_add         (16 , LCDML_0_5       , 1  , "X&Z AXES HOMING"  , NULL);                    
LCDML_add         (17 , LCDML_0_5       , 2  , "Start Homing"     , both_axis_homing);     
LCDML_add         (18 , LCDML_0_5       , 3  , "Back"             , mFunc_back_by_1); 

LCDML_add         (19 , LCDML_0_3       , 1  , "SET PARAMETERS"   , NULL);       
LCDML_add         (20 , LCDML_0_3       , 2  , "Wiping Distances" , NULL);                           
LCDML_add         (21 , LCDML_0_3       , 3  , "Number of Cycles" , NULL);                    
LCDML_addAdvanced (22 , LCDML_0_3       , 4  , NULL               , "Photo Int. "  , Photo_Int,     0,   _LCDML_TYPE_dynParam);    
LCDML_addAdvanced (23 , LCDML_0_3       , 5  , NULL               , "Wipe Force"   , Set_Force,     0,   _LCDML_TYPE_dynParam);
LCDML_addAdvanced (24 , LCDML_0_3       , 6  , NULL               , "Wipe Speed"   , Wipe_Speed,    0,   _LCDML_TYPE_dynParam);
LCDML_addAdvanced (25 , LCDML_0_3       , 7  , NULL               , "Select Pump"  , Pump_Select,   0,   _LCDML_TYPE_dynParam);                                                                   
LCDML_addAdvanced (26 , LCDML_0_3       , 8  , NULL               , "Flow Rate"    , Flow_Rate,     0,   _LCDML_TYPE_dynParam);     
LCDML_add         (27 , LCDML_0_3       , 9  , "Reset Parameters" , reset_params);              
LCDML_add         (28 , LCDML_0_3       , 10 , "Back"             , mFunc_back_by_1);    

LCDML_add         (29 , LCDML_0_3_3     , 1  , "NUM OF CYCLES"    , NULL);                    
LCDML_addAdvanced (30 , LCDML_0_3_3     , 2  , NULL               , "Increase By:" , Sel_increase_interval,  0,   _LCDML_TYPE_dynParam);                    
LCDML_addAdvanced (31 , LCDML_0_3_3     , 3  , NULL               , "Cycle Num"    , Num_of_Cycles, 0,   _LCDML_TYPE_dynParam); 
LCDML_add         (32 , LCDML_0_3_3     , 4  , "Back"             , mFunc_back_by_1);                       

LCDML_add         (33 , LCDML_0_3_2     , 1  , "SET INIT. POSITION"     , NULL);                    
//LCDML_add         (34 , LCDML_0_3_2     , 2  , "Start"                , set_init_position); 
LCDML_addAdvanced (34 , LCDML_0_3_2     , 2  , NULL                     , "Start"    , set_init_position, 0,   _LCDML_TYPE_dynParam);     
LCDML_add         (35 , LCDML_0_3_2     , 3  , "Next"                   , NULL); 

LCDML_add         (36 , LCDML_0_3_2_3   , 1  , "SET WIPING DIST."       , NULL);                    
//LCDML_add         (37 , LCDML_0_3_2_3   , 2  , "Start"                , both_axis_homing);    
LCDML_addAdvanced (37 , LCDML_0_3_2_3     , 2  , NULL                   , "Start"    , set_wipe_distance, 0,   _LCDML_TYPE_dynParam);      
LCDML_add         (38 , LCDML_0_3_2_3   , 3  , "Back"                   , mFunc_back_by_2);                           

LCDML_addAdvanced (39  , LCDML_0        , 8  , COND_hide, "Cycle Count" , cycle_count_display,  0,  _LCDML_TYPE_default);    

// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    39

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);