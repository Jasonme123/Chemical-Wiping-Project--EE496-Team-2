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