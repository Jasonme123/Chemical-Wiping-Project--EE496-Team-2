#include "includes.h"

void Set_Force(uint8_t line)
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
        if (wipe_force > 1){
            wipe_force--;
        }
        LCDML.BT_resetUp();
      }
      
      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown())
      {
        if (wipe_force < 3){
            wipe_force++;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Wipe Force: %d lbf", wipe_force);

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
        if (Cycle_Target > 1 && (Cycle_Target-increase_interval) > 0){
            Cycle_Target-= increase_interval;
        }
        LCDML.BT_resetUp();
      }
      if(LCDML.BT_checkDown())
      {
        if (Cycle_Target < 1000000 && (Cycle_Target+increase_interval) < 1000000){
            Cycle_Target+= increase_interval;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Cycle Num: %u ", Cycle_Target);

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
        if (Photo_Interval > 10){
            Photo_Interval -= 10;
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        Photo_Interval += 10;
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Photo Int. : %u ", Photo_Interval);

  // setup function
  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right

}

void Flow_Rate(uint8_t line)
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
        if (flow_rate < 9){
            flow_rate += 1;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[25];
  uint8_t decimal;
  uint8_t floating;

  decimal = flow_rate / 10;
  floating = flow_rate % 10;
  
  sprintf (buf, "Lqd Flow: %u.%u ml/wp", decimal, floating);
  real_flow_rate = (float)flow_rate / 10;
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
        if (wipe_speed > 10){
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
        if (pump > 0){
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


void Sel_increase_interval(uint8_t line)
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
        if (increase_interval > 1 && (increase_interval / 10 >= 1)){
            increase_interval /= 10;
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        if (increase_interval < 100000 && (increase_interval * 10 < 100000)){
            increase_interval *= 10;
        }
        LCDML.BT_resetDown();
      }
    }
  }

  char buf[20];
  sprintf (buf, "Increase By: %lu", increase_interval);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}


void set_init_position(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        homeBoth();
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

        X_max();
         if (!x_max){
            move_motor_left_init();  
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        X_min();
        if (!x_zero){ 
            move_motor_right_init();
        }
        LCDML.BT_resetDown();
      } 
    }
  }

  char buf[25];
  int8_t decimal;
  int8_t floating;

  init_position_in_inches = (init_position / 1088.00) * 100;
  decimal = (int)init_position_in_inches / 100;
  floating = (int)init_position_in_inches % 100;
  
  sprintf (buf, "Start: %d.%d inches", decimal, floating);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}


void set_wipe_distance(uint8_t line)
{
  if (line == LCDML.MENU_getCursorPos())
  {
    if(LCDML.BT_checkAny())
    {
      // to disable or enable scrolling
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
        X_max();
         if (!x_max){
            move_motor_left_dist();  
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        X_min();
        if (!x_max){ 
            move_motor_right_dist();     
        }
        LCDML.BT_resetDown();
      }
    }
  }
  char buf[25];
  int8_t decimal;
  int8_t floating;

  wipe_distance_in_inches = (wipe_distance / 1088.00) * 100;
  decimal = (int)wipe_distance_in_inches / 100;
  floating = (int)wipe_distance_in_inches % 100;
  
  sprintf (buf, "Start: %d.%d inches", decimal, floating);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}


void Set_Brightness(uint8_t line)
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
        if (Brightness > 0){       
     
            Brightness--;
            Photo_Brightness = map(Brightness,0,10,0,255);
            analogWrite(5, Photo_Brightness);
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        if (Brightness < 10){
           
            Brightness++;
            Photo_Brightness = map(Brightness,0,10,0,255);
            analogWrite(5, Photo_Brightness);
        }
        LCDML.BT_resetDown();
      } 
    }
  }

  char buf[20];
  sprintf (buf, "Flash Brightness: %u", Brightness);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}


void Wipe_Delay(uint8_t line)
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
        if (delay_ > 1){       
     
            delay_--;
            
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        if (delay_ < 10){
           
            delay_++;
        }
        LCDML.BT_resetDown();
      } 
    }
  }

  char buf[20];
  sprintf (buf, "Wipe Delay: %u sec", delay_);
  wipe_Delay = delay_ * 1000;

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}



void Enclosure_Brightness_(uint8_t line)
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
        if (Enclosure_Brightness > 1){       
     
            Enclosure_Brightness--;
            real_Enclosure_Brightness = map(Enclosure_Brightness,0,10,0,127);
            analogWrite(5, real_Enclosure_Brightness);
        }
        LCDML.BT_resetUp();
      }

      if(LCDML.BT_checkDown())
      {
        if (Enclosure_Brightness < 10){
           
            Enclosure_Brightness++;
            real_Enclosure_Brightness = map(Enclosure_Brightness,0,10,0,127);
            analogWrite(5, real_Enclosure_Brightness);
        }
        LCDML.BT_resetDown();
      } 
    }
  }

  char buf[20];
  sprintf (buf, "Turn ON - : %u", Enclosure_Brightness);

  u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
}
