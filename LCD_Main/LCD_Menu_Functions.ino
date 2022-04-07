
#include "Pump_Control.h"
#include "Motor_Control.h"
#include "Force_Sensors_Reading.h"
#include "Homing.h"
#include "Camera_Control.h"
#include "Force_Control.h"
#include "wiping_loop.h"
#include "Safety_Check.h"
#include "A_Setup.h"


/*  Menu Callback Function                                                *
 * EXAMPLE CODE:
// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    //LCDML_UNUSED(param);
    // setup
    // is called only if it is started
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
    //LCDML.FUNC_setGBA() 
    //
  }
  if(LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change
    // uncomment this line when the screensaver should not be called when this function is running
    // reset screensaver timer
    //LCDML.SCREEN_resetTimer();
    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }
  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions ends.
    // this means when you are calling a jumpTo ore a goRoot function
    // that this part is called before a function is closed
  }
}
 */

void mFunc_information(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    // setup function
    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), F("To close this"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("function press"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 3), F("any button or use"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 4), F("back button"));
    } while( u8g.nextPage() );
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if(LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
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

// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (global variable)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    g_func_timer_info = 5;       // reset and set timer

    char buf[20];
    sprintf (buf, "wait %d seconds", g_func_timer_info);

    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("or press back button"));
    } while( u8g.nextPage() );

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(g_timer_1);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

    // this function is called every 100 milliseconds

    // this method checks every 1000 milliseconds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000))
    {
      g_timer_1 = millis();
      g_func_timer_info--;                // increment the value every second
      char buf[20];
      sprintf (buf, "wait %d seconds", g_func_timer_info);

      u8g.setFont(_LCDML_DISP_font);
      u8g.firstPage();
      do {
        u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
        u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), F("or press back button"));
      } while( u8g.nextPage() );

    }

    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normally
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// THIS FUNCTION MIGHT WORK FOR OUR PURPOSES

// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    // print LCD content
    char buf[17];
    sprintf (buf, "count: %d of 3", 0);

    u8g.setFont(_LCDML_DISP_font);
    u8g.firstPage();
    do {
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 1), F("press a or w button"));
      u8g.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
    } while( u8g.nextPage() );

    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the up button
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

   // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


void cycle_count_display(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    u8g.firstPage();
    do {
      u8g.drawFrame(1,1,126,62);
      u8g.drawFrame(0,0,128,64);
      u8g.drawFrame(19,35,90,24);
      u8g.setFont(u8g_font_ncenB10);
      u8g.drawStr( 5, 16, F("CYCLE COUNT:"));
      u8g.drawStr(ALIGN_CENTER("0"), 31, F("0"));
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr(ALIGN_CENTER("Rotate Or Click"), 46, F("Rotate Or Click"));
      u8g.drawStr(ALIGN_CENTER("To Exit"), 56, F("To Exit"));
    } while(u8g.nextPage());

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())              // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }

  if(LCDML.FUNC_close())            // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

void mFunc_back_by_1(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go tow layers back
  }
}

void mFunc_back_by_2(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(2);      // leave this function and go tow layers back
  }
}

void mFunc_goToRootMenu(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

void mFunc_jumpTo_timer_info(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}



// Function For Z-Axis Homing 
void z_homing(uint8_t param) {

   if(LCDML.FUNC_setup())   // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
  }  

  if(LCDML.FUNC_loop())   // ****** LOOP *********
  {   
      uint32_t position_ = init_position;

      home_z_axis();

      LCDML.FUNC_goBackToMenu(0);
//      u8g.setFont(u8g_font_ncenB08);
//      u8g.drawStr(ALIGN_CENTER("Z Axis is homed"), 58, F("Z Axis is homed"));
   }  
}

// Function For Both Axes Homing 
void both_axis_homing(uint8_t param) {

   if(LCDML.FUNC_setup())  // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
  }  

  int count = 0;
  if(LCDML.FUNC_loop())  // ****** LOOP *********
  {  
      while (init_position != 0) {
          if (init_position > 0) {
           
              init_position--;
          }
          Serial.print("init_position:  ");
          Serial.println(init_position);
      }
      LCDML.FUNC_goBackToMenu(0);
   }
}

void logo_display(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
      // remmove compiler warnings when the param variable is not used:
      LCDML_UNUSED(param);
      u8g.firstPage();
      do
      {
        display_logo();
      }while(u8g.nextPage());

      LCDML.FUNC_setLoopInterval(10000);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())              // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())            // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

void reset_params(uint8_t param)
{
  if(LCDML.FUNC_setup())         
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    cycle_num = 0;
    wipe_force = 0;
    cycle_num = 0;
    photo_interval = 0;
    flow_rate = 0;
    wipe_speed = 0;
    real_wipe_speed = 0.0;
    pump = 1;
    LCDML.FUNC_goBackToMenu(0); 
  }
}


void testing_cycle(uint8_t param) {
// ****** SETUP *********
   if(LCDML.FUNC_setup())   
  {
  // WipingSetup();
    LCDML_UNUSED(param);// remove compiler warnings when the param variable is not used:
  }  

    if(LCDML.FUNC_loop())   // ****** LOOP *********
  {   
 //WipingLoop();
  }
     if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
              {
                LCDML.FUNC_goBackToMenu(1);  // leave this function
              }
                  
      
      LCDML.FUNC_goBackToMenu(0);
//      u8g.setFont(u8g_font_ncenB08);
//      u8g.drawStr(ALIGN_CENTER("Z Axis is homed"), 58, F("Z Axis is homed"));
   } 
