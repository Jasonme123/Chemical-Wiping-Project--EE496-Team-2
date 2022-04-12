// define saftey things here

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
