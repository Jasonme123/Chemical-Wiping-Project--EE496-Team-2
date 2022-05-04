#include "includes.h"




/*  Menu Callback Function                                                *
   EXAMPLE CODE:
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
  if (LCDML.FUNC_setup())         // ****** SETUP *********
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
    } while ( u8g.nextPage() );
  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if (LCDML.FUNC_close())     // ****** STABLE END *********
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
  if (LCDML.FUNC_setup())         // ****** SETUP *********
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
    } while ( u8g.nextPage() );

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(g_timer_1);
  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

    // this function is called every 100 milliseconds

    // this method checks every 1000 milliseconds if it is called
    if (LCDML.TIMER_ms(g_timer_1, 1000))
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
      } while ( u8g.nextPage() );

    }

    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normally
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();
    }
  }

  if (LCDML.FUNC_close())     // ****** STABLE END *********
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
  if (LCDML.FUNC_setup())         // ****** SETUP *********
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
    } while ( u8g.nextPage() );

    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();
  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
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
        } while ( u8g.nextPage() );
      }
    }

    // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


void cycle_count_display(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    u8g.firstPage();
    do {
      u8g.drawFrame(1, 1, 126, 62);
      u8g.drawFrame(0, 0, 128, 64);
      u8g.drawFrame(12, 35, 104, 24);
      u8g.setFont(u8g_font_ncenB10);
      u8g.drawStr(ALIGN_CENTER("SLEEP MODE"), 16, F("SLEEP MODE"));
      u8g.drawStr(ALIGN_CENTER("IS ON"), 31, F("IS ON"));
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr(ALIGN_CENTER("Rotate or Click"), 46, F("Rotate or Click"));
      u8g.drawStr(ALIGN_CENTER("To Exit"), 56, F("To Exit"));
    } while (u8g.nextPage());

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())             // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }

  if (LCDML.FUNC_close())           // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

void mFunc_back_by_1(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go tow layers back
  }
}

void mFunc_back_by_2(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(2);      // leave this function and go tow layers back
  }
}

void mFunc_goToRootMenu(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

void mFunc_jumpTo_timer_info(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}

void Enable_motors(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())             // ****** LOOP *********
  {
    // Enable Motors
    enable_Stepper();
    u8g.firstPage();
    do {
      u8g.drawFrame(1, 1, 126, 62);
      u8g.drawFrame(0, 0, 128, 64);
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr( ALIGN_CENTER("Both Motors"), 18, F("Both Motors"));
      u8g.drawStr( ALIGN_CENTER("Have Been Enabled."), 34, F("Have Been Enabled."));
      u8g.drawStr( ALIGN_CENTER("Rotate to Exit"), 50, F("Rotate to Exit"));
    }
    while (u8g.nextPage());
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }

  if (LCDML.FUNC_close())           // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.FUNC_goBackToMenu(0);
  }
}

void Disable_motors(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())             // ****** LOOP *********
  {
    // Disable steppers
    disable_Stepper();
    u8g.firstPage();
    do {
      u8g.drawFrame(1, 1, 126, 62);
      u8g.drawFrame(0, 0, 128, 64);
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr( ALIGN_CENTER("Both Motors"), 18, F("Both Motors"));
      u8g.drawStr( ALIGN_CENTER("Have Been Disabled."), 34, F("Have Been Disabled."));
      u8g.drawStr( ALIGN_CENTER("Rotate to Exit"), 50, F("Rotate to Exit"));
    }
    while (u8g.nextPage());
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }

  if (LCDML.FUNC_close())           // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.FUNC_goBackToMenu(0);
  }
}


// Function For Z-Axis Homing
void z_homing(uint8_t param) {

  if (LCDML.FUNC_setup())  // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);


  }

  if (LCDML.FUNC_loop())  // ****** LOOP *********
  {

    home_z_axis();

    LCDML.FUNC_goBackToMenu(0);
    //      u8g.setFont(u8g_font_ncenB08);
    //      u8g.drawStr(ALIGN_CENTER("Z Axis is homed"), 58, F("Z Axis is homed"));
  }
}

// Function For Both Axes Homing
void both_axis_homing(uint8_t param) {

  if (LCDML.FUNC_setup())  // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);


  }

  if (LCDML.FUNC_loop())  // ****** LOOP *********
  {
    homeBoth();

    LCDML.FUNC_goBackToMenu(0);
  }
}

// Function For Taring Load Cells
void tare_load_cells(uint8_t param) {

  if (LCDML.FUNC_setup())  // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
  }

  if (LCDML.FUNC_loop())  // ****** LOOP *********
  {
    scale.tare();
    u8g.firstPage();
    do {
      u8g.drawFrame(1, 1, 126, 62);
      u8g.drawFrame(0, 0, 128, 64);
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr( ALIGN_CENTER("Load Cells"), 18, F("Load Cells"));
      u8g.drawStr( ALIGN_CENTER("Have Been Tarred."), 34, F("Have Been Tarred."));
      u8g.drawStr( ALIGN_CENTER("Rotate to Exit"), 50, F("Rotate to Exit"));
    }
    while (u8g.nextPage());
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }
}

void logo_display(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    u8g.firstPage();
    do
    {
      display_logo();
    } while (u8g.nextPage());

    LCDML.FUNC_setLoopInterval(10000);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())             // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if (LCDML.FUNC_close())           // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

void reset_params(uint8_t param)
{
  if (LCDML.FUNC_setup())
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    Cycle_Target = 0;
    Photo_Interval = 0;
    flow_rate = 0;
    wipe_speed = 0;
    wipe_distance = 0;
    wipe_distance_in_inches = 0;
    init_position_in_inches = 0;
    real_wipe_speed = 0.0;
    pump = 1;
    delay_ = 0;
    wipe_Delay = 0;
    Brightness = 0;
    Photo_Brightness = 0;
    Enclosure_Brightness = 0;
    real_Enclosure_Brightness = 0;
    LCDML.FUNC_goBackToMenu(0);
  }
}


void testing_cycle(uint8_t param) {
  // ****** SETUP *********
  if (LCDML.FUNC_setup())
  {
    LCDML_UNUSED(param);
  }

  if (LCDML.FUNC_loop())  // ****** LOOP *********
  {
    Current_Count = 0;
    u8g.firstPage();
        do {
          u8g.drawFrame(1, 1, 126, 62);
          u8g.drawFrame(0, 0, 128, 64);
          u8g.setFont(u8g_font_ncenB10);
          u8g.drawStr( ALIGN_CENTER("Starting"), 30, F("Starting"));
          u8g.drawStr( ALIGN_CENTER("Testing Cycle"), 46, F("Testing Cycle"));
        }
        while (u8g.nextPage());

    WipingSetup();
    
    //if wipe cycle target reached, go home
    while (Current_Count < Cycle_Target) {

      WipingLoop();
      if(endstopError){

        u8g.firstPage();
        do {
          u8g.drawFrame(1, 1, 126, 62);
          u8g.drawFrame(0, 0, 128, 64);
          u8g.setFont(u8g_font_ncenB10);
          u8g.drawStr( ALIGN_CENTER("<< ERROR >>"), 16, F("<< ERROR >>"));
          u8g.drawStr( ALIGN_CENTER("The Endstop"), 34, F("The Endstop"));
          u8g.drawStr( ALIGN_CENTER("Has Triggered."), 52, F("Has Triggered."));
        }
        while (u8g.nextPage());
      }else if (is_empty){
        u8g.firstPage();
        do {
          u8g.drawFrame(1, 1, 126, 62);
          u8g.drawFrame(0, 0, 128, 64);
          u8g.setFont(u8g_font_ncenB10);
          u8g.drawStr( ALIGN_CENTER("<< ERROR >>"), 16, F("<< ERROR >>"));
          u8g.drawStr( ALIGN_CENTER("Container Needs"), 34, F("Container Needs"));
          u8g.drawStr( ALIGN_CENTER("To Be Filled."), 52, F("To Be Filled."));
        }
        while (u8g.nextPage());
      }

      if (Current_Count % 5 == 0) {

        u8g.firstPage();
        do {
          u8g.drawFrame(1, 1, 126, 62);
          u8g.drawFrame(0, 0, 128, 64);
          u8g.drawFrame(5, 35, 118, 24);
          u8g.setFont(u8g_font_ncenB10);
          u8g.drawStr( 5, 16, F("CYCLE COUNT:"));
          char buf[20];
          sprintf (buf, "%u", Current_Count);
          u8g.drawStr(ALIGN_CENTER(buf), 31, buf);
          u8g.setFont(u8g_font_ncenB08);
          u8g.drawStr(ALIGN_CENTER("Click Red Button"), 46, F("Click Red Button"));
          u8g.drawStr(ALIGN_CENTER("To Pause Testing"), 56, F("To Pause Testing"));
        }
        while (u8g.nextPage());
      }
    }
    //turn off interrupt based motor control
    noInterrupts();
    TIMER1_INTERRUPTS_OFF
    TIMER2_INTERRUPTS_OFF

    xPosition_Update = false;
    zPosition_Update = false;
    u8g.firstPage();
    do {
      u8g.drawFrame(1, 1, 126, 62);
      u8g.drawFrame(0, 0, 128, 64);
      u8g.drawFrame(5, 35, 118, 24);
      u8g.setFont(u8g_font_ncenB10);
      u8g.drawStr( 5, 16, F("CYCLE COUNT:"));
      char buf[20];
      sprintf (buf, "%u", Current_Count);
      u8g.drawStr(ALIGN_CENTER(buf), 31, buf);
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr(ALIGN_CENTER("Click on Red Button"), 46, F("Click on Red Button"));
      u8g.drawStr(ALIGN_CENTER("To Pause Testing"), 56, F("To Pause Testing"));
    }
    while (u8g.nextPage());
    //Home Both Axis
    homeBoth();

    //take final photo
    Photo();
  }

  u8g.firstPage();
    do {
      u8g.drawFrame(1, 1, 126, 62);
      u8g.drawFrame(0, 0, 128, 64);
      u8g.drawFrame(12, 35, 104, 24);
      u8g.setFont(u8g_font_ncenB10);
      u8g.drawStr(ALIGN_CENTER("Test Has:"), 16, F("Test Has:"));
      u8g.drawStr(ALIGN_CENTER("Completed!:"), 31, F("Completed!:"));
      u8g.setFont(u8g_font_ncenB08);
      u8g.drawStr(ALIGN_CENTER("Rotate or Click"), 46, F("Rotate or Click"));
      u8g.drawStr(ALIGN_CENTER("To Exit"), 56, F("To Exit"));
    }
    while (u8g.nextPage());

    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  
}


void turn_on_LEDs(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())             // ****** LOOP *********
  {
    analogWrite(bright_pin, 255);
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }

  if (LCDML.FUNC_close())           // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

void turn_off_LEDs(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())             // ****** LOOP *********
  {
    analogWrite(bright_pin, 0);
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu(0);  // leave this function
    }
  }

  if (LCDML.FUNC_close())           // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

void move_x_axis(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }

      if (LCDML.BT_checkUp())
      {

        X_max();
        if (!x_max) {
          move_motor_left();
        }
        LCDML.BT_resetUp();
      }

      if (LCDML.BT_checkDown())
      {
        X_min();
        if (!x_zero) {
          move_motor_right();
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[25];
  int8_t decimal;
  int8_t floating;

  x_adjust_position_in_inches = (x_adjust_position / 1088.00) * 100;
  decimal = (int)x_adjust_position_in_inches / 100;
  floating = (int)x_adjust_position_in_inches % 100;
  
  sprintf (buf, "Start: %d.%d inches", decimal, floating);

  u8g.drawStr( _LCDML_DISP_box_x0 + _LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1 + line)), buf); // the value can be changed with left or right
}


void move_z_axis(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }

      if (LCDML.BT_checkUp())
      {
        Z_min();
        if (!z_zero) {
          digitalWrite(Z_DIR_PIN, UP);
          for (int x = 1; x < 4267; x++) { //4267 steps per 1/4 inch
            Z_min();
            Z_STEP_HIGH;
            delayMicroseconds(Z_Homing_Speed);
            Z_STEP_LOW;
            delayMicroseconds(Z_Homing_Speed);
            z_adjust_position--;
            if (z_adjust_position >= 1){
              z_adjust_position--;          
            }
          }
          Current_ZPos--;
            //Get new Force Reading
          Force_Reading = Cell_1();
          Serial.println(Force_Reading);
        }
        else {

        }
        LCDML.BT_resetUp();
      }

      if (LCDML.BT_checkDown())
      {

        if ((z_adjust_position < z_axis_length) && Current_ZPos < 1000000) {
          digitalWrite(Z_DIR_PIN, DOWN);
          for (int x = 1; x < 4267; x++) {
            Z_STEP_HIGH;
            delayMicroseconds(Z_Homing_Speed);
            Z_STEP_LOW;
            delayMicroseconds(Z_Homing_Speed);
            z_adjust_position++;
          }
          Current_ZPos++;

          //Get new Force Reading
          Force_Reading = Cell_1();
          Serial.println(Force_Reading);
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[25];
  int8_t decimal;
  int8_t floating;

  z_adjust_position_in_inches = (z_adjust_position / 17064.00) * 100;
  decimal = (int)z_adjust_position_in_inches / 100;
  floating = (int)z_adjust_position_in_inches % 100;
  
  sprintf (buf, "Start: %d.%d inches", decimal, floating);

  u8g.drawStr( _LCDML_DISP_box_x0 + _LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1 + line)), buf); // the value can be changed with left or right
}
