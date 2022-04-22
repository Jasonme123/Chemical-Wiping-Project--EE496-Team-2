#include <PID_v1.h>

#include "includes.h"

#ifndef FORCEDEF
#define FORCEDEF

//#include <PID_v1.h>

/////////////////////////////////////////////////////////////////////////

//PID parameters
double Kp=.1, Ki=1.25, Kd=10; 

         //sensor input,  Controller output, Setpoint ,coefficents         
PID myPID(&Force_Reading_PID, &Output_Position_PID, &Force_Target_PID, Kp, Ki, Kd, DIRECT);

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
//PID Controller
void Controller_1()
{

  if (Force_Reading > Force_Target){ // this will change the motor direction up on down
    Z_direction = -1;        // depending on if we are above or below our target force
  }
  else{
    Z_direction = 1;
  }  

  
  //PID calculation to determine new output
   myPID.Compute();
   Output_Position = Output_Position * Z_direction;
  zPosition_Update = true;
}

/////////////////////////////////////////////////////////////////////
//Error Controller
void Controller_2(){

  int16_t error = Force_Target - Force_Reading;
     
      int16_t dist = (error/K_Const);
      Output_Position = dist / .089;
      zPosition_Update = true;
      
      Serial.println(Force_Reading);
}

/////////////////////////////////////////////////////////////////////

void Controller_3(){

  double error = Force_Target - Force_Reading;
     
      
      zPosition_Update = true;
}

#endif
