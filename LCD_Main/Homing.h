


void home_x_axis(){
TIMER1_INTERRUPTS_OFF

digitalWrite(X_DIR_PIN, LOW);
  
  while(!x_zero){
    X_STEP_HIGH;
    delayMicroseconds(150);
    X_STEP_LOW;
  }
  
}

void home_z_axis(){
TIMER1_INTERRUPTS_OFF

digitalWrite(Z_DIR_PIN, LOW);
  
  while(!z_zero){
    Z_STEP_HIGH;
    delayMicroseconds(150);
    Z_STEP_LOW;
  }
  
}

void X_min(){
  delay(15);
  x_zero = true; //if at zero position
  Current_XPos = 0;
}

void Z_min(){
  delay(15);
  z_zero = true; //if at zero position
  Current_ZPos = 0; 
}

void z_min_setup() {
  pinMode(z_min_stop, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(z_min_stop), Z_min, CHANGE);
}

void x_min_setup() {
  pinMode(x_min_stop, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(x_min_stop), X_min, CHANGE);
}

//If we detect an error while homing
void homing_error(){
  while(1);
  }
