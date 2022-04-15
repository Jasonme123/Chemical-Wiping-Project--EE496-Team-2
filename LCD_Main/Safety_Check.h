#include "includes.h"

#ifndef SAFEDEF
#define SAFEDEF

// define saftey things here

void safety_setup(){
  
  //data direction of endstops
  pinMode(z_min_stop, INPUT);
  pinMode(x_min_stop, INPUT);
  pinMode(x_max_stop, INPUT);

  digitalWrite(z_min_stop, HIGH);
  digitalWrite(x_min_stop, HIGH);
  digitalWrite(x_max_stop, HIGH);
}

/////////////////////////////////////////////////////////
//when endstop is triggered
void X_min(){
  if(digitalRead(x_min_stop) ==  LOW){
  delay(250);
  x_zero = true; //if at zero position
  Current_XPos = 0;
  }
}

/////////////////////////////////////////////////////////
//when endstop is triggered
void Z_min(){
  if(digitalRead(z_min_stop) ==  LOW){
  delay(250);
  z_zero = true; //if at zero position
  Current_ZPos = 0; 
  }
}

/////////////////////////////////////////////////////////
//when endstop is triggered
void X_max(){
  if(digitalRead(x_max_stop) ==  LOW){
  delay(250);
  z_zero = true; //if at zero position
  Current_ZPos = 0; 
  }
}


void safety_Check(){
 
 //If loadcell not found
 if (scale.wait_ready_retry(10)){
   Serial.println("HX711 not found.");
 }
  

}

//////////////////////////////////////////////////////////////////////////////
////Hard Pause Button

//void HardPause(){
//  delayMicroseconds(1000);
//  int Play_state = !Play_state;
//  
//  if(Play_state = false){
//  TIMER1_INTERRUPTS_OFF;
//  TIMER2_INTERRUPTS_OFF;
//  digitalWrite(X_ENABLE_PIN, HIGH);
//  }
//
//  if(Play_state = true){
//  TIMER1_INTERRUPTS_ON;
//  TIMER2_INTERRUPTS_ON;
//  digitalWrite(X_ENABLE_PIN, LOW);
//  }
//}
//
//void Pause_Button_Setup() {
//  pinMode(hard_pause, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(hard_pause), HardPause, CHANGE);
//}

#endif
