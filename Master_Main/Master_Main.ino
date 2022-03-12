#include "Config.h"
#include "Motor_Control.h"
#include "Safety_Check.h"

int count = 1;

void setup() {
  Serial.begin(9600);
  Motorsetup();
  //safety_Check();

  xPosition_Update = true;
  zPosition_Update = true;
  disable_Stepper();  //comment out to enable steppers
  
   TIMER1_INTERRUPTS_ON //Allows motor steps to by called
   TIMER2_INTERRUPTS_ON //Allows motor steps to by called
}

void loop() {

  Force_Reading = Cell_1();
  
///////////////////////////////////////////////////////////
 while(count<100){
  //Serial.print(count);
  //Serial.print(":    ");
  delay(10);
  count++; 
 
 volatile stepperInfo& sxx = steppers[0];
 int i = sxx.stepPosition;

 Serial.println(i);
 count = 0;
}
}
