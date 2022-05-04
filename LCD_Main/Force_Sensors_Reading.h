
#include "includes.h"

#ifndef FORCESENDEF
#define FORCESENDEF

#include "HX711.h"

HX711 scale;


//Calibration ////////////////////////////////////////////////
void Calibration_Cell_1() {
  scale.set_scale(500);
  //scale.tare();
}

///////////////////////////////////////////////////////////////

//Setup///////////////////////////////////////////////////////
void LoadCell_setup() {

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_gain(32); // Set gain

  Calibration_Cell_1();
}
//////////////////////////////////////////////////////////////

//Reading /////////////////////////////////////////////////////
//Channel A
int16_t Cell_1() {

  int16_t i = scale.get_units(1);

  //Serial.print(i);

  // //If Serial Not found
  // if (scale.wait_ready_retry(15)) {
  //   Serial.println("HX711 not found.");
  // }

  return (i);
}


void Cell_test() {

  scale.tare();

  delay(2000);

  //Reset Wipe Counter
  Current_Count = 1;

  //Take user parmaeters and assign them to useful varibles
  Wipe_Dist = wipe_distance; //Wipe Distance in steps
  Init_Pos = init_position; //Inital Position in steps
  Force_Target = wipe_force * 453.59237; //Force we are attempting to Achieve with the Z-axis
  Pump_Rate = ((flow_rate / (1.06)) * 1600); // Flow rate in Steps/Wipe (truncated)
  //Wiping_Speed = wipe_speed;
  Pump_Used = pump;
  ///////////////////////////////////////////////////////
  Serial.print("wipe_force:  ");
  Serial.println(wipe_force);

  Serial.print("Force_Target:  ");
  Serial.println(Force_Target);

  Force_Reading = Cell_1();

  Serial.print("Force_Reading:  ");
  Serial.println(Force_Reading);

  ///////////////////////////////////////////////////////////////
}

#endif
