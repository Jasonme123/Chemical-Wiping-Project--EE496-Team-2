#include "includes.h"

#ifndef SAFEDEF
#define SAFEDEF

// define saftey things here

void disable_Stepper(){
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);
}

void enable_Stepper(){
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
}

/////////////////////////////////////////////////////////
//when endstop is triggered
void X_min(){
  if(digitalRead(x_min_stop) ==  LOW){
  delay(100);
  x_zero = true; //if at zero position
  Current_XPos = 0;
  }
  else{
    x_zero = false;
  }
}

/////////////////////////////////////////////////////////
//when endstop is triggered
void Z_min(){
  if(digitalRead(z_min_stop) ==  LOW){
  delay(100);
  z_zero = true; //if at zero position
  Current_ZPos = 0; 
  }
  else{
  z_zero = false;
  }
}

/////////////////////////////////////////////////////////
//when endstop is triggered
void X_max(){
  if(digitalRead(x_max_stop) ==  LOW){
  delay(250);
  x_max = true; //if at zero position
  Current_ZPos = 0; 
  }
  else{
  x_max = false;
  }
}

void endstop_Check(){
  X_min();
  X_max();
  Z_min();
  
 if((x_max || x_zero || z_zero ) && wiping){
  TIMER1_INTERRUPTS_OFF
  disable_Stepper();
  Serial.println("Endstop Error");
 }
}

void safety_Check(){
 if(x_max || x_zero){
   TIMER1_INTERRUPTS_OFF
  disable_Stepper();
  Serial.println("Endstop Error");
 }
 
// //If loadcell not found
// if (scale.wait_ready_retry(10)){
//   Serial.println("HX711 not found.");
// }
  

}

//////////////////////////////////////////////////////////////////////////////
////Hard Pause Button
void Interrupt_test(){
  Serial.println("test");
}
void HardPause(){
 

  Play_state = !Play_state;
  
  if(Play_state == false){
  TIMER1_INTERRUPTS_OFF
  disable_Stepper();
  Serial.println("Motors Disabled");
  }

  if(Play_state == true){
  TIMER1_INTERRUPTS_ON
  enable_Stepper();
  Serial.println("Motors Enabled");
  }
 }


void safety_setup(){
  
  //data direction of endstops
  pinMode(z_min_stop, INPUT);
  pinMode(x_min_stop, INPUT);
  pinMode(x_max_stop, INPUT);

  digitalWrite(z_min_stop, HIGH);
  digitalWrite(x_min_stop, HIGH);
  digitalWrite(x_max_stop, HIGH);

  pinMode(hard_pause, INPUT);
  digitalWrite(hard_pause, HIGH);
  //detachInterrupt(digitalPinToInterrupt(hard_pause));

  //attachInterrupt(digitalPinToInterrupt(hard_pause), HardPause, FALLING);

  pinMode(Main_Status_LED, OUTPUT);
  digitalWrite(Main_Status_LED, HIGH);
  
}

wipe_blink(){
  
  digitalWrite(Main_Status_LED, LOW);
  delay(20);
  digitalWrite(Main_Status_LED, HIGH);
}


#endif
