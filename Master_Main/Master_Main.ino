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
}

void loop() {
//////////////////////////////////////////////////////////
//X-Axis Wiping Cycle

volatile stepperInfo& sx = steppers[0];
if(sx.movementDone){ // if wipe half cycle is complete one way is complete
 xPosition_Update = true;
 x_movement = (x_movement * -1);
}

//////////////////////////////////////////////////////////
//Z-Axis Wiping Cycle
volatile stepperInfo& sz = steppers[1];
if(sz.movementDone){ // if wipe half cycle is complete one way is complete
 zPosition_Update = true;
 z_movement = (z_movement * -1);
}
  
//////////////////////////////////////////////////////////
//Motor Command Sender

TIMER1_INTERRUPTS_ON //Allows motor steps to by called
     
//if x motor target changes, tell the motor to move to the new target  
   
     if(xPosition_Update){  
       xPosition_Update = false;
       prepareMovement( 0,  x_movement );
       runAndWait();
     }
     
//if z motor target changes, tell the motor to move to the new target

     if(zPosition_Update){
      zPosition_Update = false;
      prepareMovement( 1,  z_movement );
      runAndWait();
     }
     
///////////////////////////////////////////////////////////
 
  Serial.println(count);
  delay(10);
  count++; 

}
