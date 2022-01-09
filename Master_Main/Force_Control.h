#include <PID_v1.h>

 double Force_Reading;
 static boolean newDataReady = 0;
/////////////////////////////////////////////////////////////////////////

//PID parameters
double Kp=.1, Ki=1.25, Kd=10; 

         //sensor input,  Controller output, Setpoint ,coefficents         
PID myPID(&Force_Reading, &Output_Position, &Force, Kp, Ki, Kd, DIRECT);

///////////////////////////////////////////////////////////////////////// 
//PID Controller Type Config
void Control_setup()
{
 
  //Turn the PID on
  myPID.SetMode(AUTOMATIC);
  //Adjust PID values
  myPID.SetTunings(Kp, Ki, Kd);
}

/////////////////////////////////////////////////////////////////////

void Control_loop()
{

  if (Force_Reading > Force){ // this will change the motor direction up on down
    M_direction = LOW;        // depending on if we are above or below our target force
  }
  else{
    M_direction = HIGH;
  }  
  
  if (LoadCell.update()) newDataReady = true;
  if (newDataReady) {
      Force_Reading = LoadCell.getData();
      
      Serial.print(Force_Reading);
      Serial.print(',');
      Serial.print(Output_Position);
      Serial.print(',');  
      Serial.print(M_direction);
      Serial.print(',');  
      Serial.print(SPEED);      
      Serial.print(',');   
      Serial.println();
      newDataReady = 0;
  }
  //PID calculation to determine new output
   myPID.Compute();
  

  //Serial.println(Output_Position);
  //Serial.print(" ");  
  //Serial.println(Force);
  delay(10);
}
