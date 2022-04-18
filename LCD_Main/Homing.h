
#include "includes.h"

#ifndef HOMEDEF
#define HOMEDEF

//Homing Cycle Functions

/////////////////////////////////////////////////////////
//If we detect an error while homing
void homing_error(){
  disable_Stepper();
  Serial.println("Homing Error");
  }
  
/////////////////////////////////////////////////////////
//X axis homing function
void home_x_axis(){
  X_min();
  uint16_t homing_checker;
  digitalWrite(X_DIR_PIN, RIGHT);
  
    while(!x_zero){
      X_min();
      X_STEP_HIGH;
      delayMicroseconds(X_Homing_Speed);
      X_STEP_LOW;
      delayMicroseconds(X_Homing_Speed);
      homing_checker++;

      if(homing_checker % 1600 == 0){
        Serial.println("Homing X");
      }
  
      if (homing_checker > x_axis_length){  //If while traveling home we move more than the expected length of axis, stop.
       homing_error();
      }
    }  
}

/////////////////////////////////////////////////////////
//Z axis homing function
void home_z_axis(){
Z_min();
uint16_t homing_checker;
digitalWrite(Z_DIR_PIN, UP);
  
  while(!z_zero){
    Z_min();
    Z_STEP_HIGH;
    delayMicroseconds(Z_Homing_Speed);
    Z_STEP_LOW;
    delayMicroseconds(Z_Homing_Speed);
    homing_checker++;

    if(homing_checker % 1600 == 0){
      Serial.println("Homing Z");
    }

    if(homing_checker > z_axis_length){  //If while traveling home we move more than the expected length of axis, stop.
      homing_error();
    }
  }
}

/////////////////////////////////////////////////////////
//This will move the wipe down until we reach our target force
void touchDown(){

  uint16_t forceCheck  = Cell_1();
  uint16_t homing_checker;
  digitalWrite(Z_DIR_PIN, DOWN);
  
    while (forceCheck < Force_Target){
      Z_STEP_HIGH;
      delayMicroseconds(Z_Homing_Speed);
      Z_STEP_LOW;
      delayMicroseconds(Z_Homing_Speed);
      homing_checker++;
  
      if(homing_checker % 800 == 0){
        forceCheck  = Cell_1();
        Serial.println("Td");
      }
      
      if (homing_checker > x_axis_length){  //If while traveling home we move more than the expected length of axis, stop.
         homing_error();
        }
    }
}

/////////////////////////////////////////////////////////
//X axis inital position
void intial_x_axis(){
  
  uint16_t homing_checker;
  digitalWrite(X_DIR_PIN, LEFT);

    while(Current_XPos < Init_Pos){
      X_STEP_HIGH;
      delayMicroseconds(X_Homing_Speed);
      X_STEP_LOW;
      delayMicroseconds(X_Homing_Speed);
      Current_XPos++; 
      homing_checker++;
      
      if(homing_checker % 1600 == 0){
        Serial.println("Inital Position Travel");
      }
  
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
