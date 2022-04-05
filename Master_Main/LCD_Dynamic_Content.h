/* ===================================================================== *
 *                                                                       *
 * Dynamic content                                                       *
 *                                                                       *
 * ===================================================================== *
 */
uint32_t Force_dynParam = 0; // when this value comes from an EEPROM, load it in setup
uint32_t cycle_dynParam = 0;
uint32_t photo_dynParam = 0;
uint32_t flow_rate = 0;
uint8_t wipe_speed = 0;  // Used For User Input as sprintf formatting of floating point values is not supported in Arduino
float real_wipe_speed = 0.0;  // Used For Actual Calculations
uint8_t pump = 1;

void Set_Force(uint8_t line)
// *********************************************************************
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
        // ...
        
        LCDML.BT_resetEnter();
      }

      // This check have only an effect when MENU_disScroll is set
      // UP == Increase
      // DOWN == Dicrease
      if(LCDML.BT_checkUp())
      {
        if (Force_dynParam > 0){
            Force_dynParam--;
        }
        LCDML.BT_resetUp();
      }
      
      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown())
      {
        if (Force_dynParam < 15){
            Force_dynParam++;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Wipe Force: %d lbf", Force_dynParam);

  // setup function
  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}

void Num_of_Cycles(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }
      if(LCDML.BT_checkUp())
      { 
        if (cycle_dynParam > 1000){
            cycle_dynParam-= 1000;
        }
        LCDML.BT_resetUp();
      }
      if(LCDML.BT_checkDown())
      {
        cycle_dynParam+=1000;
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Cycle Num: %lu ", cycle_dynParam);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}


void Photo_Int(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }

      if(LCDML.BT_checkUp())
      { 
        if (photo_dynParam > 10){
            photo_dynParam -= 10;
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        photo_dynParam += 10;
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Photo Int. : %lu ", photo_dynParam);

  // setup function
  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right

}

void Flow_Rate(uint8_t line)
// *********************************************************************
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }

      if(LCDML.BT_checkUp())
      { 
        if (flow_rate > 0){
            flow_rate -= 1;
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        flow_rate += 1;
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[25];
  sprintf (buf, "Flow Rate: %lu ml/wp", flow_rate);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}

void Wipe_Speed(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }
      
      if(LCDML.BT_checkUp())
      { 
        if (wipe_speed > 0){
            wipe_speed -= 1;
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        if (wipe_speed < 25){
            wipe_speed += 1;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[25];
  uint8_t decimal;
  uint8_t floating;

  decimal = wipe_speed / 10;
  floating = wipe_speed % 10;

  sprintf (buf, "Wipe Speed: %u.%u in/s", decimal, floating);
  // converting decimal to float
  real_wipe_speed = (float)wipe_speed / 10;
  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right

}

void Pump_Select(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
          LCDML.MENU_enScroll();
        }
        LCDML.BT_resetEnter();
      }
      if(LCDML.BT_checkUp())
      { 
        if (pump > 1){
            pump -= 1;
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        if (pump < 2){
            pump += 1;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Select Pump: %u", pump);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}













