
#ifndef PUMPCONTDEF
#define PUMPCONTDEF

void Pump_setup() {

  pinMode(P1_STEP_PIN, OUTPUT);
  pinMode(P1_DIR_PIN, OUTPUT);
  pinMode(P1_ENABLE_PIN, OUTPUT);
  
  pinMode(P2_STEP_PIN, OUTPUT);
  pinMode(P2_DIR_PIN, OUTPUT);
  pinMode(P2_ENABLE_PIN, OUTPUT);
  digitalWrite(P1_ENABLE_PIN, HIGH);
  digitalWrite(P1_ENABLE_PIN, HIGH);
}

//////////////////////////////////////////////////////////////////
void unPriming(){
  
    int Pump_distance = 0; //temp var
  
    digitalWrite(P1_ENABLE_PIN, LOW);
    digitalWrite(P2_ENABLE_PIN, LOW); //Enable Pump Movements

    digitalWrite(P1_DIR_PIN, From_wipe);
    digitalWrite(P2_DIR_PIN, From_wipe);

  while(Pump_distance < Tube_Volume){
   digitalWrite(P2_STEP_PIN, HIGH);
   digitalWrite(P1_STEP_PIN, HIGH);
   delayMicroseconds(Pumping_Speed/2);
   digitalWrite(P2_STEP_PIN, LOW);
   digitalWrite(P1_STEP_PIN, LOW);
   delayMicroseconds(Pumping_Speed/2);
    Pump_distance++;
  }

   digitalWrite(P1_ENABLE_PIN, HIGH);
   digitalWrite(P2_ENABLE_PIN, HIGH); //Disable Pump Movements
  }

//////////////////////////////////////////////////////////////////
void Priming(){
  
    int Pump_distance = 0; //temp var
  
    digitalWrite(P1_ENABLE_PIN, LOW);
    digitalWrite(P2_ENABLE_PIN, LOW); //Enable Pump Movements

    digitalWrite(P1_DIR_PIN, To_Wipe);
    digitalWrite(P2_DIR_PIN, To_Wipe);

  if (Pump_Used == 2){               //If Pump 2 is used
  while(Pump_distance < Tube_Volume){
   digitalWrite(P2_STEP_PIN, HIGH);
   delayMicroseconds(Pumping_Speed/2);
   digitalWrite(P2_STEP_PIN, LOW);
   delayMicroseconds(Pumping_Speed/2);
    Pump_distance++;
  }
}
  else{                           //If Pump 1 is used
   while(Pump_distance < Tube_Volume){
   digitalWrite(P1_STEP_PIN, HIGH);
   delayMicroseconds(Pumping_Speed/2);
   digitalWrite(P1_STEP_PIN, LOW);
   delayMicroseconds(Pumping_Speed/2);
    Pump_distance++;
  }

   digitalWrite(P1_ENABLE_PIN, HIGH);
   digitalWrite(P2_ENABLE_PIN, HIGH); //Disable Pump Movements
  }
}  
//////////////////////////////////////////////////////////////////
void Pump(int pump_rate) {

TIMER1_INTERRUPTS_OFF
  
  int Pump_distance = 0;

  digitalWrite(P1_ENABLE_PIN, LOW);
  digitalWrite(P2_ENABLE_PIN, LOW); //Enable Pump Movements


  digitalWrite(P1_DIR_PIN, To_Wipe);
  digitalWrite(P2_DIR_PIN, To_Wipe);

if (Pump_Used == 2){               //If Pump 2 is used
while(Pump_distance < pump_rate){
  digitalWrite(P2_STEP_PIN, HIGH);
  delayMicroseconds(Pumping_Speed/2);
  digitalWrite(P2_STEP_PIN, LOW);
  delayMicroseconds(Pumping_Speed/2);
  Pump_distance++;
  }
}
  else{                           //If Pump 1 is used
  while(Pump_distance < pump_rate){
  digitalWrite(P1_STEP_PIN, HIGH);
  delayMicroseconds(Pumping_Speed/2);
  digitalWrite(P1_STEP_PIN, LOW);
  delayMicroseconds(Pumping_Speed/2);
  Pump_distance++;
  }

}
   digitalWrite(P1_ENABLE_PIN, HIGH);
   digitalWrite(P2_ENABLE_PIN, HIGH); //Disable Pump Movements
   
TIMER1_INTERRUPTS_ON
}

#endif
