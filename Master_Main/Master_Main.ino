#include "Motor_Control.h"

void setup() {
  // put your setup code here, to run once:
Motorsetup();
}

void loop() {

  TIMER1_INTERRUPTS_ON
  

      prepareMovement( 0,  2000 );
      runAndWait();

      prepareMovement( 0, -2000 );
      runAndWait();
      
  while (true);


}
