
#include "includes.h"

#ifndef FORCESENDEF
#define FORCESENDEF

#include "HX711.h"

HX711 scale;


//Calibration ////////////////////////////////////////////////
void Calibration_Cell_1(){
  scale.set_scale(2409.17);
  //scale.tare();  
}

///////////////////////////////////////////////////////////////

//Setup///////////////////////////////////////////////////////
void LoadCell_setup() {
 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_gain(128); // Set gain

  Calibration_Cell_1();
}
//////////////////////////////////////////////////////////////

//Reading /////////////////////////////////////////////////////
//Channel A
uint32_t Cell_1() {

  uint32_t i = scale.get_units(5); 

  //Serial.print(i); 

 //If Serial Not found
 if (scale.wait_ready_retry(10)){
   Serial.println("HX711 not found.");
 }

  return(i);
}

#endif
