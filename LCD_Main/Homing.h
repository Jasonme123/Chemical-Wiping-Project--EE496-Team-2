
#include "includes.h"

#ifndef HOMEDEF
#define HOMEDEF

//Homing Cycle Functions


/////////////////////////////////////////////////////////
//General Setup
void homingSetup(){

  //DATA Direction

   pinMode(Z_DIR_PIN, OUTPUT); // Motor control
   pinMode(Z_STEP_PIN, OUTPUT);
   pinMode(Z_ENABLE_PIN, OUTPUT);

  
   pinMode(X_DIR_PIN, OUTPUT); // Motor control
   pinMode(X_STEP_PIN, OUTPUT);
   pinMode(X_ENABLE_PIN, OUTPUT);

}

/////////////////////////////////////////////////////////
//If we detect an error while homing
void homing_error(){
  while(1);
  }
  
/////////////////////////////////////////////////////////
//X axis homing function
void home_x_axis(){
  enable_Stepper();
TIMER1_INTERRUPTS_OFF

//digitalWrite(X_ENABLE_PIN, LOW);

uint32_t homing_checker;
digitalWrite(X_DIR_PIN, RIGHT);

  while(!x_zero){
    //X_min();
    X_STEP_HIGH;
    delayMicroseconds(X_Homing_Speed);
    X_STEP_LOW;
    delayMicroseconds(X_Homing_Speed);
    homing_checker++;

      if (homing_checker > x_axis_length){  //If while traveling home we move more than the expected length of axis, stop.
       homing_error();
      }
  }  
}

/////////////////////////////////////////////////////////
//Z axis homing function
void home_z_axis(){
  enable_Stepper();
TIMER1_INTERRUPTS_OFF


uint32_t homing_checker;
digitalWrite(Z_DIR_PIN, UP);
  
  while(!z_zero){
    //Z_min();
    Z_STEP_HIGH;
    delayMicroseconds(Z_Homing_Speed);
    Z_STEP_LOW;
    delayMicroseconds(Z_Homing_Speed);
    homing_checker++;

        if (homing_checker > z_axis_length){  //If while traveling home we move more than the expected length of axis, stop.
       homing_error();
      }
  }
}

//void z_min_setup() {
//  pinMode(z_min_stop, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(z_min_stop), Z_min, CHANGE);
//}

//void x_min_setup() {
//  pinMode(x_min_stop, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(x_min_stop), X_min, CHANGE);
//}

/////////////////////////////////////////////////////////
//This will move the wipe down until we reach our target force
void touchDown(){
  
  TIMER1_INTERRUPTS_OFF
  double forceCheck  = Cell_1();
  uint32_t homing_checker;
  digitalWrite(Z_DIR_PIN, DOWN);
  
  while (forceCheck < Force_Target){
  forceCheck  = Cell_1();
    Z_STEP_HIGH;
    delayMicroseconds(150);
    Z_STEP_LOW;
    delayMicroseconds(150);
    homing_checker++;
    
    if (homing_checker > x_axis_length){  //If while traveling home we move more than the expected length of axis, stop.
       homing_error();
      }
  }
}

/////////////////////////////////////////////////////////
//Home Both Axes
void homeBoth(){
  home_z_axis();
  home_x_axis();
}

#endif
