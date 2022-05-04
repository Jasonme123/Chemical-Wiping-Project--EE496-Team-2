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
    uint32_t Pump_distance = 0; //temp var
  
    digitalWrite(P0_ENABLE_PIN, LOW);
    digitalWrite(P1_ENABLE_PIN, LOW); //Enable Pump Movements

    digitalWrite(P0_DIR_PIN, From_wipe);
    digitalWrite(P1_DIR_PIN, From_wipe);

  while(Pump_distance < Tube_Volume){
   digitalWrite(P1_STEP_PIN, HIGH);
   digitalWrite(P0_STEP_PIN, HIGH);
   delayMicroseconds(Priming_Speed);
   byte value = digitalRead(hard_pause);
    if (value != Prev_state && value == LOW) {
      HardPause();
      Prev_state = value;
      return;
    }
    Prev_state = value;
   digitalWrite(P1_STEP_PIN, LOW);
   digitalWrite(P0_STEP_PIN, LOW);
    Pump_distance++;
  }

   digitalWrite(P0_ENABLE_PIN, HIGH);
   digitalWrite(P1_ENABLE_PIN, HIGH); //Disable Pump Movements
  }

//////////////////////////////////////////////////////////////////
void Priming(){
  
    uint32_t Pump_distance = 0; //temp var
  
    digitalWrite(P0_ENABLE_PIN, LOW);
    digitalWrite(P1_ENABLE_PIN, LOW); //Enable Pump Movements

    digitalWrite(P0_DIR_PIN, To_Wipe);
    digitalWrite(P1_DIR_PIN, !To_Wipe);

  if (Pump_Used == 1){               //If pump 1 is used
  while(Pump_distance < Tube_Volume){
   digitalWrite(P0_STEP_PIN, HIGH);
   delayMicroseconds(Priming_Speed);
   byte value = digitalRead(hard_pause);
   if (value != Prev_state && value == LOW) {
     HardPause();
     Prev_state = value;
     return;
   }
   Prev_state = value;
   digitalWrite(P0_STEP_PIN, LOW);
    Pump_distance++;
  }
}
  else if (Pump_Used == 2){                           //If Pump 2 is used
   while(Pump_distance < Tube_Volume){
   digitalWrite(P1_STEP_PIN, HIGH);
   delayMicroseconds(Priming_Speed);
   byte value = digitalRead(hard_pause);
    if (value != Prev_state && value == LOW) {
      HardPause();
      Prev_state = value;
      return;
    }
    Prev_state = value;
   digitalWrite(P1_STEP_PIN, LOW);
    Pump_distance++;
  }
  }else {
    while (Pump_distance < Tube_Volume){
      digitalWrite(P0_STEP_PIN, HIGH);
      digitalWrite(P1_STEP_PIN, HIGH);
      delayMicroseconds(Priming_Speed);
      byte value = digitalRead(hard_pause);
      if (value != Prev_state && value == LOW) {
        HardPause();
        Prev_state = value;
        return;
      }
      Prev_state = value;
      digitalWrite(P0_STEP_PIN, LOW);
      digitalWrite(P1_STEP_PIN, LOW);
      Pump_distance++;
   }

   digitalWrite(P0_ENABLE_PIN, HIGH);
   digitalWrite(P1_ENABLE_PIN, HIGH); //Disable Pump Movements
  }
}

unsigned long time_now = 0;

//////////////////////////////////////////////////////////////////
void Pump(int pump_rate) {
wiping = false;
// TIMER1_INTERRUPTS_OFF
// TIMER2_INTERRUPTS_OFF
  
  uint32_t Pump_distance = 0;

  digitalWrite(P0_ENABLE_PIN, LOW);
  digitalWrite(P1_ENABLE_PIN, LOW); //Enable Pump Movements


  digitalWrite(P0_DIR_PIN, To_Wipe);
  digitalWrite(P1_DIR_PIN, !To_Wipe);

if (Pump_Used == 0){               //If Pump 0 is used
while(Pump_distance < pump_rate){
  digitalWrite(P0_STEP_PIN, HIGH);
  Serial.print("h");
  byte value = digitalRead(hard_pause);
  if (value != Prev_state && value == LOW) {
    HardPause();
    Prev_state = value;
    return;
  }
  Prev_state = value;
  // time_now = millis();
  // while(millis() <  time_now + Pumping_Speed);
//delayMicroseconds(Priming_Speed);
  digitalWrite(P0_STEP_PIN, LOW);
  Pump_distance++;
  }
}
  else if (Pump_Used == 1){        //If Pump 1 is used
  while(Pump_distance < pump_rate){
  digitalWrite(P1_STEP_PIN, HIGH);

  Serial.print("h");
  byte value = digitalRead(hard_pause);
  if (value != Prev_state && value == LOW) {
    HardPause();
    Prev_state = value;
    return;
  }
  Prev_state = value;
  // time_now = millis();
  // while(millis() <  time_now + Pumping_Speed);
  // //delayMicroseconds(Priming_Speed);
  digitalWrite(P1_STEP_PIN, LOW);
  Pump_distance++;
  }
} else {                              // both pumps are used
  while(Pump_distance < pump_rate){
    digitalWrite(P0_STEP_PIN, HIGH);
    digitalWrite(P1_STEP_PIN, HIGH);
    // time_now = millis();
    // while(millis() <  time_now + Pumping_Speed);

    // //delayMicroseconds(Priming_Speed);
    Serial.print("h");
    byte value = digitalRead(hard_pause);
    if (value != Prev_state && value == LOW) {
      HardPause();
      Prev_state = value;
      return;
    }
    Prev_state = value;
    digitalWrite(P0_STEP_PIN, LOW);
    digitalWrite(P1_STEP_PIN, LOW);
    Pump_distance++;
  }
   digitalWrite(P0_ENABLE_PIN, HIGH);
   digitalWrite(P1_ENABLE_PIN, HIGH); //Disable Pump Movements
}
  
//  unsigned long interrupt_time = millis();
//  
//  while (interrupt_time < wipe_Delay){
//  interrupt_time = millis();   
//  }

wiping = true;
}

#endif
