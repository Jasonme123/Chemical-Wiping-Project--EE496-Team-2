//---CONTROL WITH ENCODER---
//   * rotate left = Up
//   * rotate right = Down
//   * push = Enter
//   * push long = Quit
//   * push + rotate left = Left
//   * push + rotate right = Right

  // global defines
  #define encoder_A_pin       3    // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
  #define encoder_B_pin       2    // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
  #define encoder_button_pin  32    // physical pin , use internal pullup

  #define g_LCDML_CONTROL_button_long_press    800   // ms
  #define g_LCDML_CONTROL_button_short_press   120   // ms

  #define ENCODER_OPTIMIZE_INTERRUPTS //Only when using pin2/3 (or 20/21 on mega)
  #include <Encoder.h> 

  Encoder ENCODER(encoder_A_pin, encoder_B_pin);

  unsigned long  g_LCDML_CONTROL_button_press_time = millis();
  bool  g_LCDML_CONTROL_button_prev       = HIGH;

void lcdml_menu_control(void)
{
  // declare variable for this function
  int32_t g_LCDML_CONTROL_Encoder_position = ENCODER.read();
  bool g_LCDML_button = digitalRead(encoder_button_pin);
  
  // If something must init, put in in the setup condition
  if(LCDML.BT_setup())
  {
    // runs only once

    // init pins, enable pullups
    pinMode(encoder_A_pin      , INPUT_PULLUP);
    pinMode(encoder_B_pin      , INPUT_PULLUP);
    pinMode(encoder_button_pin , INPUT_PULLUP);
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
