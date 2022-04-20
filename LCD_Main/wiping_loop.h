


#ifndef WIPECONTDEF
#define WIPECONTDEF

//Wiping_Cycle

#include "includes.h"

///////////////////////////////////////////////////////////////////////////////
void WipingSetup() {
  
  //Turn off motor interrupt routines
  TIMER1_INTERRUPTS_OFF
  
                                    Serial.print("hello");

   //Reset Wipe Counter
   Current_Count = 1; 

  //Take user parmaeters and assign them to useful varibles
   Wipe_Dist = wipe_distance; //Wipe Distance in steps
   Init_Pos = init_position; //Inital Position in steps
   //Force_Target = wipe_force; //Force we are attempting to Achieve with the Z-axis
   Cycle_Target = cycle_num; //Number of wipes per each test
   Photo_Interval = photo_interval; //number of wipes between a Photo is taken
   Pump_Rate = ((flow_rate/(1.06)) * 1600); // Flow rate in Steps/Wipe (truncated)
   //Wiping_Speed = wipe_speed;
   Pump_Used = pump;



  //Home Both Axis
    homeBoth();

    wipe_blink();

  //Unpriming and Priming Pumps
     unPriming();
     wipe_blink();
     Priming();
     wipe_blink();
     
  //If you don't want photos
    if(Photo_Interval == 0){
    Photo_Interval = 4294967;
     }

                                            Serial.println("progress"); //REMOVE LATER
                                            Serial.println(Current_XPos);
                                            

  //move wipe to the inital position
    for(uint8_t i = 0; i<100;){     //for loop counter for a delay
    i++;
    Serial.println("Delay");
  }
  intial_x_axis(); 
  wipe_blink();
                                            
                                            
  
  //move z axis down until target force is reached
  touchDown();
  wipe_blink();

}
  
///////////////////////////////////////////////////////////////////////////////

void WipingLoop(){
  
  //Turn interrupts back on for motor control
  TIMER1_INTERRUPTS_ON

   xPosition_Update = true;

  Serial.println("Yay im in the loop");

  delay(2000);
  
  
  //if wipe cycle target reached, go home
  while(Current_Count < Cycle_Target){
  Serial.print("Current_Count:  ");
  Serial.println(Current_Count);

  
  //Check Endstops
  X_min();
  X_max();
  Z_min();

  //Checking Endstops and Load Cell
  safety_Check();
  
  //Take a photo if needed
  if((Current_Count % Photo_Interval) == 0){
    Photo();
  }
  
//Get new Force Reading
  Force_Reading = Cell_1();
  
//Force Controller Option 1 (PID)
  //Controller_1();

//Chasing the Error
  Controller_2();
  Serial.print("Force Reading2:   ");
  Serial.println(Force_Reading);
  
  Serial.print("Output_Position:   ");
  Serial.println(Output_Position);

//X-Axis Wiping Cycle
    volatile stepperInfo& sx = steppers[0];
    if(sx.movementDone){    
     xPosition_Update = true;
     Current_Count++;
     wipe_blink();
     Pump(Pump_Rate); //Pumping done per wipe 
    }

/////////////////////////////////////////////////////////
//Motor Command Sender

//if x motor target changes, tell the motor to move to the new target  
     if(xPosition_Update){  
       xPosition_Update = false;
       prepareMovement( 0,  Wipe_Dist); //xmotor
       Wipe_Dist = (-Wipe_Dist);
       runAndWait();
     }
     
//if z motor target changes, tell the motor to move to the new target

     if(zPosition_Update){
      zPosition_Update = false;
      prepareMovement( 1,  Output_Position ); //zmotor
      runAndWait();
     }

            
    }

    //turn off interrupt based motor control       
    noInterrupts();
    
    //Home Both Axis
    homeBoth();
    
 }
   


#endif
