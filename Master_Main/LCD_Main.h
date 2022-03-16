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
void LCD_setup()
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


// check some errors
# if(_LCDML_glcd_tft_box_x1 > _LCDML_glcd_tft_w)
# error _LCDML_glcd_tft_box_x1 is to big
# endif

# if(_LCDML_glcd_tft_box_y1 > _LCDML_glcd_tft_h)
# error _LCDML_glcd_tft_box_y1 is to big
# endif




//////////////////////////////////// LCD_Menu_Function.h
//////////////////////////////////// LCD_Menu_Function.h
//////////////////////////////////// LCD_Menu_Function.h


void your_function_name(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change

    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions end.
  }
}

// Condition Function 
boolean COND_hide()  // hide a menu element
{
  return false;  // hidden
}

void mFunc_information(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);
    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), F("To close this"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("function press"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 3), F("Rotate the encoder"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 4), F("or click on it"));
    } while( u8g.nextPage() );
  }

  if(LCDML.FUNC_loop())           
  {
    if(LCDML.BT_checkAny()) 
    {
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (global variable)
void mFunc_timer_info(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);

    g_func_timer_info = 20;       // reset and set timer

    char buf[20];
    sprintf (buf, "wait %d seconds", g_func_timer_info);

    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("or press back button"));
    } while( u8g.nextPage() );



    LCDML.FUNC_setLoopInterval(100);  

    LCDML.TIMER_msReset(g_timer_1);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset Cycle_Count_Display timer
    LCDML.SCREEN_resetTimer();

    // this method checks every 1000 milliseconds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000))
    {
      g_timer_1 = millis();
      g_func_timer_info--;                
      char buf[20];
      sprintf (buf, "wait %d seconds", g_func_timer_info);

      u8g.setFont(_LCDML_DISP_font);
      u8g.firstPage();
      do {
        u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
        u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("or press back"));
      } while( u8g.nextPage() );

    }

    if (g_func_timer_info <= 0)
    {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
  }
}

uint8_t g_button_value = 0; // button value counter
void mFunc_p2(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);

    // setup function
    // print LCD content
    char buf[17];
    sprintf (buf, "count: %d of 3", 0);

    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), F("Rotate Encoder"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
    } while( u8g.nextPage() );

    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) 
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;

        // update LCD content
        char buf[17];
        sprintf (buf, "count: %d of 3", g_button_value);

        u8g.setFont(_LCDML_DISP_font);
        u8g.firstPage();
        do {
          u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), F("press a or w button"));
          u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
        } while( u8g.nextPage() );
      }
    }

    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      
    }
  }

  if(LCDML.FUNC_close())     
  {
  }
}

void display_cycle_count(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);
    u8g.setFont(_LCDML_DISP_big_font);
    u8g.firstPage();
    do {
      u8g.setFont(_LCDML_DISP_big_font);
      u8g.drawStr( 11, 21, F("Cycle Count: "));
      u8g.setFont(u8g_font_gdr20);
      u8g.drawStr(ALIGN_CENTER("0"), 52, F("0"));
    } while( u8g.nextPage() );

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())              // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) // check if Encoder is interacted
    {
      LCDML.FUNC_goBackToMenu();  
    }
  }

  if(LCDML.FUNC_close())       // ****** STABLE END *********
  {
    LCDML.MENU_goRoot();
  }
}

void mFunc_back(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);

    // end function and go n layer back
    LCDML.FUNC_goBackToMenu(1);      // go a layer back
  }
}

void mFunc_goToRootMenu(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

void mFunc_jumpTo_timer_info(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);

    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}

void mFunc_para(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    char buf[20];
    sprintf (buf, "parameter: %d", param);

    // setup function
    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("press any key"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 3), F("to leave it"));
    } while( u8g.nextPage() );

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // For example
    switch(param)
    {
      case 10:
        // do something
        break;

      case 20:
        // do something
        break;

      case 30:
        // do something
        break;

      default:
        // do nothing
        break;
    }


    if (LCDML.BT_checkAny()) 
    {
      LCDML.FUNC_goBackToMenu();  
    }
  }

  if(LCDML.FUNC_close())        
  {
  }
}


////////////// LCD_Menu_Control.h
////////////// LCD_Menu_Control.h
////////////// LCD_Menu_Control.h




//   * rotate left = Up
//   * rotate right = Down
//   * push = Enter
//   * push long = Quit
//   * push + rotate left = Left
//   * push + rotate right = Right

// global defines
#define encoder_A_pin       20    
#define encoder_B_pin       21    
#define encoder_button_pin  49    

#define g_LCDML_CONTROL_button_long_press    800   // ms
#define g_LCDML_CONTROL_button_short_press   120   // ms

#define ENCODER_OPTIMIZE_INTERRUPTS 
#include <Encoder.h> 

Encoder ENCODER(encoder_A_pin, encoder_B_pin);

unsigned long  g_LCDML_CONTROL_button_press_time = millis();
bool  g_LCDML_CONTROL_button_prev       = HIGH;

void lcdml_menu_control(void)
{
  // declare variable for this function
  int32_t g_LCDML_CONTROL_Encoder_position = ENCODER.read();
  bool g_LCDML_button                      = digitalRead(encoder_button_pin);
  
  if(LCDML.BT_setup())
  {
    pinMode(encoder_A_pin      , INPUT_PULLUP);
    pinMode(encoder_B_pin      , INPUT_PULLUP);
    pinMode(encoder_button_pin  , INPUT_PULLUP);
  }

  // check if encoder is rotated on direction A
  if(g_LCDML_CONTROL_Encoder_position <= -3) 
  {
    // check if the button is pressed and the encoder is rotated
    // the button is low active
    if(g_LCDML_button == LOW)
    {
      // button is pressed
      LCDML.BT_left();  

      // reset button press time for next detection
      g_LCDML_CONTROL_button_prev = HIGH;
    }
    else
    {
      LCDML.BT_down();
    }    

    // init encoder for the next step
    ENCODER.write(g_LCDML_CONTROL_Encoder_position+4);
  }
  
  // check if encoder is rotated on direction B
  else if(g_LCDML_CONTROL_Encoder_position >= 3)
  {    
    // check if the button is pressed and the encoder is rotated
    // the button is low active
    if(g_LCDML_button == LOW)
    {
      // button is pressed
      LCDML.BT_right(); 

      // reset button press time for next detection
      g_LCDML_CONTROL_button_prev = HIGH;
    }
    else
    {
      LCDML.BT_up();
    }   

    // init encoder for the next step
    ENCODER.write(g_LCDML_CONTROL_Encoder_position-4);
  }
  else
  {
    // check if the button was pressed for a shortly time or a long time
    
    //falling edge, button pressed, no action
    if(g_LCDML_button == LOW && g_LCDML_CONTROL_button_prev == HIGH)  
    {
      g_LCDML_CONTROL_button_prev = LOW;
      g_LCDML_CONTROL_button_press_time = millis();
    }

    // rising edge, button not pressed, check how long was it pressed    
    else if(g_LCDML_button == HIGH && g_LCDML_CONTROL_button_prev == LOW) 
    {
      g_LCDML_CONTROL_button_prev = HIGH;
      
      // check how long was the button pressed and detect a long press or a short press

      // check long press situation
      if((millis() - g_LCDML_CONTROL_button_press_time) >= g_LCDML_CONTROL_button_long_press)
      {
        // long press detected
        LCDML.BT_quit();
      }
      // check short press situation
      else if((millis() - g_LCDML_CONTROL_button_press_time) >= g_LCDML_CONTROL_button_short_press)
      {
        // short press detected
        LCDML.BT_enter();
      }
    }

    // do nothing
    else 
    {
      // do nothing
    }
  }
}


//// LCD_Menu_Display.h


void lcdml_menu_display()
{
  // for first test set font here
  u8g.setFont(_LCDML_DISP_font);

  // content variable
  char content_text[_LCDML_DISP_cols];  // save the content text of every menu element
  // menu element object
  LCDMenuLib2_menu *tmp;
  // some limit values
  uint8_t i = LCDML.MENU_getScroll();
  uint8_t maxi = _LCDML_DISP_rows + i;
  uint8_t n = 0;

   // init vars
  uint8_t n_max             = (LCDML.MENU_getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.MENU_getChilds());

  uint8_t scrollbar_min     = 0;
  uint8_t scrollbar_max     = LCDML.MENU_getChilds();
  uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
  uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);


  u8g.setFont(_LCDML_DISP_font);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on.


  // generate content
  u8g.firstPage();
  do {


    n = 0;
    i = LCDML.MENU_getScroll();
    // update content
    // ***************

      // clear menu
      // ***************

    // check if this element has children
    if ((tmp = LCDML.MENU_getDisplayedObj()) != NULL)
    {
      // loop to display lines
      do
      {
        // check if a menu element has a condition and if the condition be true
        if (tmp->checkCondition())
        {
          // check the type off a menu element
          if(tmp->checkType_menu() == true)
          {
            // display normal content
            LCDML_getContent(content_text, tmp->getID());
            u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (n + 1), content_text);
          }
          else
          {
            if(tmp->checkType_dynParam()) {
              tmp->callback(n);
            }
          }
          // increment some values
          i++;
          n++;
        }
      // try to go to the next sibling and check the number of displayed rows
      } while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
    }

    // set cursor
    u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (LCDML.MENU_getCursorPos() + 1),  _LCDML_DISP_cursor_char);

    if(_LCDML_DISP_draw_frame == 1) {
       u8g.drawFrame(_LCDML_DISP_box_x0, _LCDML_DISP_box_y0, (_LCDML_DISP_box_x1-_LCDML_DISP_box_x0), (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0));
    }

    // display scrollbar when more content as rows available and with > 2
    if (scrollbar_max > n_max && _LCDML_DISP_scrollbar_w > 2)
    {
      // set frame for scrollbar
      u8g.drawFrame(_LCDML_DISP_box_x1 - _LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y0, _LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y1-_LCDML_DISP_box_y0);

      // calculate scrollbar length
      uint8_t scrollbar_block_length = scrollbar_max - n_max;
      scrollbar_block_length = (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0) / (scrollbar_block_length + _LCDML_DISP_rows);

      //set scrollbar
      if (scrollbar_cur_pos == 0) {                                 // top position     (min)
        u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y0 + 1                                                     , (_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
      }
      else if (scrollbar_cur_pos == (scrollbar_max-1)) {            // bottom position  (max)
        u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y1 - scrollbar_block_length                                , (_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
      }
      else {                                                        // between top and bottom
        u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y0 + (scrollbar_block_length * scrollbar_cur_pos + 1),(_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
      }
    }
  } while ( u8g.nextPage() );
}

void lcdml_menu_clear()
{
}


////// LCD_Dynamic_Content.h


uint8_t g_dynParam = 100; 
void mDyn_para(uint8_t line)
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

        // do something        
        LCDML.BT_resetEnter();
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp())
      {
        g_dynParam++;
        LCDML.BT_resetUp();
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown())
      {
        g_dynParam--;
        LCDML.BT_resetDown();
      }


      if(LCDML.BT_checkLeft())
      {
        g_dynParam++;
        LCDML.BT_resetLeft();
      }
      
      if(LCDML.BT_checkRight())
      {
        g_dynParam--;
        LCDML.BT_resetRight();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Cycle Count: %d", 0);

  // setup function
  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right

}
