#include "includes.h"

#ifndef SAFEDEF
#define SAFEDEF

// define saftey things here

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
 if(x_max || x_zero || z_zero){
  noInterrupts();
  disable_Stepper();
  Serial.println("Endstop Error");
 }
}

void safety_Check(){
 if(x_max || x_zero){
  noInterrupts();
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
  for(int i; i<10000;){
    i++;
    Serial.print(Play_state);
  }
  
  Serial.print(Play_state);
  
  if(Play_state = false){
  noInterrupts();
  disable_Stepper();
  Serial.println("Motors Disabled");
  while(!Play_state);
  }

  if(Play_state = true){
  interrupts();
  enable_Stepper();
  Serial.println("Motors Enabled");
  }
  Play_state = !Play_state;
}

void safety_setup(){
  
  //data direction of endstops
  pinMode(z_min_stop, INPUT);
  pinMode(x_min_stop, INPUT);
  pinMode(x_max_stop, INPUT);

  digitalWrite(z_min_stop, HIGH);
  digitalWrite(x_min_stop, HIGH);
  digitalWrite(x_max_stop, HIGH);

  pinMode(hard_pause, INPUT_PULLUP);

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
