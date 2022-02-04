#include "Config.h"
#include "Motor_Control.h"
#include "Safety_Check.h"

int count = 1;
int i = 0;

void setup() {
  Serial.begin(9600);
  Motorsetup();
  safety_Check();

  xPosition_Update = true;
  zPosition_Update = true;
  //disable_Stepper();  //comment out to enable steppers
  
   TIMER1_INTERRUPTS_ON //Allows motor steps to by called
   TIMER2_INTERRUPTS_ON //Allows motor steps to by called
}

void loop() {
  
///////////////////////////////////////////////////////////
 while(count<100){
  Serial.println(count);
  delay(1000);
  count++; 
 }
}
