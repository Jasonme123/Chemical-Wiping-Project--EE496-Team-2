// SETUP
#include "includes.h"

void setup()
{
  function_setup();

  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.println("Start_up"); // only for examples

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();

  // Enable Screensaver (screensaver menu function, time to activate in ms)
  LCDML.SCREEN_enable(cycle_count_display, 120000); // set to 30 seconds

}

// LOOP
void loop()
{
   
  //this function must be called here, do not delete it
  LCDML.loop();

    byte value = digitalRead(hard_pause);
  if (value != Prev_state && value == LOW) {
    HardPause();
    Prev_state = value;
    return;
  }
  Prev_state = value; 
}
