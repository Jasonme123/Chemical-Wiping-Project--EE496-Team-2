
double Force = 1500;

#include "Excel_Data_Streamer.h"
#include "Control_System.h"
#include "x_axis.h"



void setup() {
 calibration_setup();
 Control_setup();
 Motor_setup();
 xsetup();
}

void loop() {
 Calibration(); 
 Control_loop();
 Motor_loop();
 xloop();
 
    distance3 = 0;
    if (done1 % 16 == 0){
        digitalWrite(directio, HIGH);
      }
    if (done1 % 16 == 8){
        digitalWrite(directio, LOW);
      }
    while(distance3 < 600){
      digitalWrite(ste, HIGH);
      delayMicroseconds(SPEED1);
      digitalWrite(ste, LOW);
      distance3 = distance3 + 1;
    }
    done1 = done1 + 1;
  

}
