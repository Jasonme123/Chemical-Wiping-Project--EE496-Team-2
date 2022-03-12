#include <LCDMenuLib2.h>
#include <U8glib.h>

// U8GLIB
// setup u8g object
U8GLIB_ST7920_128X64 u8g(13, 11, 10, U8G_PIN_NONE);

// *********************************************************************
// Prototypes
// *********************************************************************
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// *********************************************************************
// Objects
// *********************************************************************
LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element 
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// LCDML_0        => layer 0
// LCDML_0_X      => layer 1
// LCDML_0_X_X    => layer 2
// LCDML_0_X_X_X  => layer 3
// LCDML_0_...      => layer ...

// LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
  
LCDML_add         (0  , LCDML_0         , 1  , "Home X-axis"      , mFunc_information);       
LCDML_add         (1  , LCDML_0         , 2  , "Home Z-axis"      , mFunc_timer_info);        
LCDML_add         (2  , LCDML_0         , 3  , "Set Parameters"   , NULL);                    
LCDML_add         (3  , LCDML_0_3       , 1  , "Water"            , NULL);                    
LCDML_add         (4  , LCDML_0_3_1     , 1  , "Initial Position" , NULL);                    
LCDML_add         (5  , LCDML_0_3_1     , 2  , "Wiping Distance"  , NULL);                    
LCDML_add         (6  , LCDML_0_3_1_2   , 1  , "Wiping Force"     , NULL);                    
LCDML_add         (7  , LCDML_0_3_1_2   , 2  , "Pump Flow Rate"   , NULL);                    
LCDML_add         (8  , LCDML_0_3_1_2   , 3  , "Back"             , mFunc_back);              
LCDML_add         (9  , LCDML_0_3_1     , 3  , "Back"             , mFunc_back);              
LCDML_add         (10 , LCDML_0_3       , 2  , "Photo Shot"       , mFunc_p2);                
LCDML_add         (11 , LCDML_0_3       , 3  , "Back"             , mFunc_back);              
LCDML_add         (12 , LCDML_0         , 4  , "Start"            , NULL);                    
LCDML_add         (13 , LCDML_0_4       , 1  , "Go to Root"       , mFunc_goToRootMenu);      
LCDML_add         (14 , LCDML_0_4       , 2  , "Reset"            , mFunc_jumpTo_timer_info); 
LCDML_add         (15 , LCDML_0_4       , 3  , "Back"             , mFunc_back);              


// Advanced menu 
// LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (16 , LCDML_0         , 5  , NULL               , "Pause"      , NULL,                0,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced (17 , LCDML_0_5       , 1  , NULL               , "Parameter 1"      , mFunc_para,       10,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced (18 , LCDML_0_5       , 2  , NULL               , "Parameter 2"      , mFunc_para,       20,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced (19 , LCDML_0_5       , 3  , NULL               , "Parameter 3"      , mFunc_para,       30,            _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_add         (20 , LCDML_0_5       , 4  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab


// Dynamic content
// LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (21 , LCDML_0         , 6  , NULL,          ""                  , mDyn_para,                0,   _LCDML_TYPE_dynParam);                     // NULL = no menu function

// conditions 
// LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (22 , LCDML_0         , 7  , COND_hide,  "screensaver"          , display_cycle_count,        0,   _LCDML_TYPE_default);                      // this menu function can be found on "LCDML_display_menuFunction" tab

// _LCDML_DISP_cnt shoud be updated while adding a menu element

// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    22

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);

// SETUP
void setup()
{
  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();

  // Enable Cycle Count Display (time to activate in ms)
  LCDML.SCREEN_enable(display_cycle_count, 30000); // set to 30 seconds
  //LCDML.SCREEN_disable();

}

// LOOP
void loop()
{
  // this function must called here
  LCDML.loop();
}

// check some errors
# if(_LCDML_glcd_tft_box_x1 > _LCDML_glcd_tft_w)
# error _LCDML_glcd_tft_box_x1 is to big
# endif

# if(_LCDML_glcd_tft_box_y1 > _LCDML_glcd_tft_h)
# error _LCDML_glcd_tft_box_y1 is to big
# endif