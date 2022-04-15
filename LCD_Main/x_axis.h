#include "includes.h"

#ifndef XAXISDEF
#define XAXISDEF

int StepsToTake = 400;     // Controls the speed of the Stepper per Rotary click
   

void move_motor_left(){
  digitalWrite(X_DIR_PIN, LEFT);
  for (int x = 1; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);         
  }
}

void move_motor_right(){
  digitalWrite(X_DIR_PIN, RIGHT);  
  for (int x = 1; x < StepsToTake; x++) {
    X_STEP_HIGH
    delayMicroseconds(150);
    X_STEP_LOW
    delayMicroseconds(150);           
  }
}

#endif
