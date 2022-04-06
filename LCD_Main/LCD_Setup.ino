// SETUP
#include "config.h"
#include "Pump_Control.h"
#include "Motor_Control.h"
#include "Force_Sensors_Reading.h"
#include "Homing.h"
#include "Camera_Control.h"
#include "Force_Control.h"
#include "wiping_loop.h"
#include "Safety_Check.h"
#include "A_Setup.h"


void setup()
{


  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();

  // Enable Screensaver (screensaver menu function, time to activate in ms)
  LCDML.SCREEN_enable(cycle_count_display, 30000); // set to 30 seconds

  function_setup();
}

// LOOP
void loop()
{
  //light up enclosure to normal brightness
  analogWrite(bright_pin, Norm_Brightness); 
  
  
  //this function must be called here, do not delete it
  LCDML.loop();
}
