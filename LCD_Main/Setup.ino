// SETUP
#include "includes.h"

void setup()
{
  
  Pump_setup(); //Pump Setup
  Camera_setup(); //Camera Setup
  LoadCell_setup(); //Force feedback load cell setup
  Control_setup(); //force controller setup 
  homingSetup(); //endstop pinmode setup

  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();

  // Enable Screensaver (screensaver menu function, time to activate in ms)
  LCDML.SCREEN_enable(cycle_count_display, 30000); // set to 30 seconds


}

// LOOP
void loop()
{
  
  //this function must be called here, do not delete it
  LCDML.loop();
}