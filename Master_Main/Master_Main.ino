#include "Config.h"
#include "Motor_Control.h"
#include "Safety_Check.h"

int count = 1;
void setup() {
  Serial.begin(9600);
  Motorsetup();
  safety_Check();

  xPosition_Update = true;
}

void loop() {
//////////////////////////////////////////////////////////
//X-Axis Wiping Cycle

volatile stepperInfo& s = steppers[0];
if(s.movementDone){ // if wipe half cycle is complete one way is complete
x_movement = (-1*x_movement);
 //Serial.println(s.stepCount);
 //Serial.println(xPosition_Update);
 xPosition_Update = true;
 //Serial.println(xPosition_Update);
}
  
//////////////////////////////////////////////////////////
//Motor Command Sender

     TIMER1_INTERRUPTS_ON //Allows motor steps to by called
     
//if x motor target changes, tell the motor to move to the new target     
     if(xPosition_Update){  
     xPosition_Update = false;
     prepareMovement( 0,  x_movement );
     runAndWait();
     Serial.println(count);
     Serial.println(x_movement);
     Serial.println(s.movementDone);
     count++;
     }
     
//if z motor target changes, tell the motor to move to the new target
     if(zPosition_Update){
     prepareMovement( 1,  z_movement );
     zPosition_Update = false;
    
     }
///////////////////////////////////////////////////////////

}
