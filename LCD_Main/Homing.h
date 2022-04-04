


void home_x_axis(){
TIMER1_INTERRUPTS_OFF

digitalWrite(X_DIR_PIN, LOW);
  
  while(!x_zero){
    X_STEP_HIGH;
    delayMicroseconds(150);
    X_STEP_LOW;
  }
}


attachInterrupt(digitalPinToInterrupt(x_min_stop), X_min(), RISING);
void X_min(){
  delay(15);
  x_zero = true; //if at zero position
  Current_XPos = 0;
  
}

attachInterrupt(digitalPinToInterrupt(z_min_stop), Z_min(), RISING);
void Z_min(){
  delay(15);
  z_zero = true; //if at zero position
  Current_ZPos = 0;
}


//If we detect an error while homing
void homing_error(){
  while(1);
  }
