
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 20;
const int LOADCELL_SCK_PIN = 21;

HX711 scale;

//Calibration ////////////////////////////////////////////////
void Calibration_Cell_1(){
  scale.set_scale(2409.17);
  scale.tare();  
}

///////////////////////////////////////////////////////////////

//Setup///////////////////////////////////////////////////////
void LoadCell_setup() {
 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Calibration_Cell_1();
}
//////////////////////////////////////////////////////////////

//Reading /////////////////////////////////////////////////////
//Channel A
int Cell_1() {
   scale.set_gain(128); // Set gain
  int i = scale.get_units(5);

 //If Serial Not found
 if (scale.wait_ready_retry(10)){
   Serial.println("HX711 not found.");
 }

  return(i);
}
