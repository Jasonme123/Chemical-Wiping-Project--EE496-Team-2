


#ifndef WIPECONTDEF
#define WIPECONTDEF

//Wiping_Cycle

#include "includes.h"

///////////////////////////////////////////////////////////////////////////////
void WipingSetup() {

  //Turn off motor interrupt routines
  TIMER1_INTERRUPTS_OFF
  TIMER2_INTERRUPTS_OFF



  //Reset Wipe Counter
  Current_Count = 1;

  //Take user parmaeters and assign them to useful varibles
  Wipe_Dist = -wipe_distance; //Wipe Distance in steps
  Init_Pos = init_position; //Inital Position in steps
  Force_Target = wipe_force * 453.59237; //Force we are attempting to Achieve with the Z-axis
  Pump_Rate = ((real_flow_rate / (1.06)) * 1600); // Flow rate in Steps/Wipe (truncated)
  xMin_Interval = map(real_wipe_speed, 1, 2.5, 141, 79);

  // Serial.print("wiping Speed:   ");
  // Serial.println(xMin_Interval);


  Serial.print("Pump_Rate:   ");
  Serial.println(Pump_Rate);
  
  Pump_Used = pump;

  ///////////////////////////////////////////////////////////////

  //Home Both Axis
  homeBoth();
  scale.tare();
  wipe_blink();

  //Unpriming and Priming Pumps
  unPriming();
  wipe_blink();
  Priming();
  wipe_blink();

  //If you don't want photos
  if (Photo_Interval == 0) {
    Photo_Interval = 4294967;
  }


  //move wipe to the inital position
  for (uint8_t i = 0; i < 100;) { //for loop counter for a delay
    i++;
    Serial.println("Delay");
  }
  intial_x_axis();
  wipe_blink();



  //move z axis down until target force is reached
  touchDown();
  wipe_blink();

  xPosition_Update = true;
  // prepareMovement( 0,  Wipe_Dist);

  delay(2000);
  wiping = true;

    TIMER1_INTERRUPTS_ON
    TIMER2_INTERRUPTS_ON

}

///////////////////////////////////////////////////////////////////////////////

void WipingLoop() {
// if(Pumping_Needed == true){
//   Pump(Pump_Rate);
//   Pumping_Needed = false;
// }

  //Take a photo if needed
  if (((Current_Count % Photo_Interval) == 0) && !photo_taken){
    Photo();
  }

  //Check Containers
  if (Current_Count % 100 == 0){
    check_containers();
    if (is_empty) return;
  }

  //Get new Force Reading
  Force_Reading = Cell_1();


  //Force Controller Option 1 (PID)
  //Controller_1();

  //Chasing the Error
  Controller_2();
  

}


#endif
