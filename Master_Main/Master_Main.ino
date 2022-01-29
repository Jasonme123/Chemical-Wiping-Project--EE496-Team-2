#include "Config.h"
#include "Motor_Control.h"
#include "Safety_Check.h"

int count = 1;
void setup() {
  Serial.begin(9600);
  Motorsetup();
  safety_Check();
  
}

void loop() {

  TIMER1_INTERRUPTS_ON
  
   for (int i = 0; i < num_Cycles; i++) { 
    //x_Movements();
    //z_Movements();
     prepareMovement( 1,  8000 );
     prepareMovement( 0,  x_movement );
     runAndWait();
     
     prepareMovement( 1,  -8000 );
     prepareMovement( 0,  -1*x_movement );
     runAndWait();
     
 }
     count++;
     delay(10);
     Serial.println(count);

  while(1);

}

//////////////////////////////////////////////////
//x motor wiping motion
void x_Movements(){

  int half_Move = x_movement;
     prepareMovement( 0,  half_Move );
     runAndWait();
     
     prepareMovement( 0,  -half_Move );
     runAndWait(); 
}
//////////////////////////////////////////////////
//z motor wiping motion
void z_Movements(){
     prepareMovement( 1,  8000 );
     runAndWait();
     
     prepareMovement( 1,  -8000 );
     runAndWait(); 
}
