
double Force = 1500;

#include "Excel_Data_Streamer.h"
#include "Control_System.h"


void setup() {
 calibration_setup();
 Control_setup();
 Motor_setup();
}

void loop() {
 Calibration(); 
 Control_loop();
 Motor_loop();

}
