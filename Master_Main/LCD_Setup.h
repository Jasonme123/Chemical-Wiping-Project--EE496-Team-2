// *********************************************************************
// SETUP
// *********************************************************************
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
  //LCDML.SCREEN_disable();

  // Some needful methods

  // You can jump to a menu function from anywhere with
  //  LCDML.OTHER_jumpToFunc(logo_display); // the parameter is the function name
}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{
  //this function must be called here, do not delete it
  LCDML.loop();
}