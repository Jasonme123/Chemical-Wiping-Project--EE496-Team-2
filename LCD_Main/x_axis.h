#include "includes.h"

#ifndef XAXISDEF
#define XAXISDEF

int StepsToTake = 272;   // quarter inch movement  // Controls the speed of the Stepper per Rotary click
   
void move_motor_left(){
  digitalWrite(X_DIR_PIN, LEFT);
  for (int x = 0; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150); 
    x_adjust_position++;    
  }
}

void move_motor_right(){
  digitalWrite(X_DIR_PIN, RIGHT);  
  for (int x = 0; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);   
    if (x_adjust_position >= 1){
       x_adjust_position--;          
    }      
  }
}


void move_motor_left_init(){
  digitalWrite(X_DIR_PIN, LEFT);
  for (int x = 0; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);
    init_position++;          
  }
}

void move_motor_right_init(){
  digitalWrite(X_DIR_PIN, RIGHT);  
  for (int x = 0; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);
    if (init_position >= 1){
       init_position--;          
    }
  }
}

void move_motor_left_dist(){
  digitalWrite(X_DIR_PIN, LEFT);
  for (int x = 0; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);
    wipe_distance++;         
  }
}

void move_motor_right_dist(){
  digitalWrite(X_DIR_PIN, RIGHT);  
  for (int x = 0; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);
    if (wipe_distance >= 1){
      wipe_distance--;
    }           
  }
}

#endif
