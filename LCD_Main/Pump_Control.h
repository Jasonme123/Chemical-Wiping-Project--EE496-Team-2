#include "includes.h"

#ifndef PUMPCONTDEF
#define PUMPCONTDEF

void Pump_setup() {

  pinMode(P0_STEP_PIN, OUTPUT);
  pinMode(P0_DIR_PIN, OUTPUT);
  pinMode(P0_ENABLE_PIN, OUTPUT);
  
  pinMode(P1_STEP_PIN, OUTPUT);
  pinMode(P1_DIR_PIN, OUTPUT);
  pinMode(P1_ENABLE_PIN, OUTPUT);
  digitalWrite(P0_ENABLE_PIN, HIGH);
  digitalWrite(P0_ENABLE_PIN, HIGH);
}

//////////////////////////////////////////////////////////////////
void unPriming(){
  wiping = false;
    int Pump_distance = 0; //temp var
  
    digitalWrite(P0_ENABLE_PIN, LOW);
    digitalWrite(P1_ENABLE_PIN, LOW); //Enable Pump Movements

    digitalWrite(P0_DIR_PIN, From_wipe);
    digitalWrite(P1_DIR_PIN, From_wipe);

  while(Pump_distance < Tube_Volume){
   digitalWrite(P1_STEP_PIN, HIGH);
   digitalWrite(P0_STEP_PIN, HIGH);
   delayMicroseconds(Pumping_Speed/2);
   digitalWrite(P1_STEP_PIN, LOW);
   digitalWrite(P0_STEP_PIN, LOW);
    Pump_distance++;
  }

   digitalWrite(P0_ENABLE_PIN, HIGH);
   digitalWrite(P1_ENABLE_PIN, HIGH); //Disable Pump Movements
  }

//////////////////////////////////////////////////////////////////
void Priming(){
  
    int Pump_distance = 0; //temp var
  
    digitalWrite(P0_ENABLE_PIN, LOW);
    digitalWrite(P1_ENABLE_PIN, LOW); //Enable Pump Movements

    digitalWrite(P0_DIR_PIN, To_Wipe);
    digitalWrite(P1_DIR_PIN, To_Wipe);

  if (Pump_Used == 0){               //If pump 0 is used
  while(Pump_distance < Tube_Volume){
   digitalWrite(P0_STEP_PIN, HIGH);
   delayMicroseconds(Pumping_Speed/2);
   digitalWrite(P0_STEP_PIN, LOW);
    Pump_distance++;
  }
}
  else if (Pump_Used == 1){                           //If Pump 1 is used
   while(Pump_distance < Tube_Volume){
   digitalWrite(P1_STEP_PIN, HIGH);
   delayMicroseconds(Pumping_Speed/2);
   digitalWrite(P1_STEP_PIN, LOW);
    Pump_distance++;
  }
  }else {
    while (Pump_distance < Tube_Volume){
      digitalWrite(P0_STEP_PIN, HIGH);
      digitalWrite(P1_STEP_PIN, HIGH);
      delayMicroseconds(Pumping_Speed/2);
      digitalWrite(P0_STEP_PIN, LOW);
      digitalWrite(P1_STEP_PIN, LOW);
      Pump_distance++;
   }

   digitalWrite(P0_ENABLE_PIN, HIGH);
   digitalWrite(P1_ENABLE_PIN, HIGH); //Disable Pump Movements
  }
}  
//////////////////////////////////////////////////////////////////
void Pump(int pump_rate) {
wiping = false;
//TIMER1_INTERRUPTS_OFF
  
  int Pump_distance = 0;

  digitalWrite(P0_ENABLE_PIN, LOW);
  digitalWrite(P1_ENABLE_PIN, LOW); //Enable Pump Movements


  digitalWrite(P0_DIR_PIN, To_Wipe);
  digitalWrite(P1_DIR_PIN, To_Wipe);

if (Pump_Used == 0){               //If Pump 0 is used
while(Pump_distance < pump_rate){
  digitalWrite(P0_STEP_PIN, HIGH);
  delayMicroseconds(Pumping_Speed/2);
  digitalWrite(P0_STEP_PIN, LOW);
  Pump_distance++;
  }
}
  else if (Pump_Used == 1){        //If Pump 1 is used
  while(Pump_distance < pump_rate){
  digitalWrite(P1_STEP_PIN, HIGH);
  delayMicroseconds(Pumping_Speed/2);
  digitalWrite(P1_STEP_PIN, LOW);
  Pump_distance++;
  }
} else {                              // both pumps are used
  while(Pump_distance < pump_rate){
    digitalWrite(P0_STEP_PIN, HIGH);
    digitalWrite(P1_STEP_PIN, HIGH);
    delayMicroseconds(Pumping_Speed/2);
    digitalWrite(P0_STEP_PIN, LOW);
    digitalWrite(P1_STEP_PIN, LOW);
    Pump_distance++;
  }
   digitalWrite(P0_ENABLE_PIN, HIGH);
   digitalWrite(P1_ENABLE_PIN, HIGH); //Disable Pump Movements
}
   
//TIMER1_INTERRUPTS_ON
wiping = true;
}

#endif
