#pragma once

//Motor Control Pins
#define step_pin     7   // Pin 9 connected to Steps pin
#define dir_pin      6   // Pin 8 connected to Direction pin
#define ENA          52
                  
int StepperPosition = 0; // To store Stepper Motor Position
int StepsToTake = 400;     // Controls the speed of the Stepper per Rotary click
   
////X-motor Config
//double x_Gear = 12;  //X motor gear diameter (mm)
//int rev_Step = 1600; //Steps Per revolution
//double x_circumference = (3.14159 * x_Gear * 0.0393); //x motor gear circumference (inches) 
//volatile int x_movement = (rev_Step * (wipe_Distance / x_circumference)); // X axis movement in steps

void x_axis_setup ()  {
   pinMode(dir_pin, OUTPUT); // Motor control
   pinMode(step_pin, OUTPUT);
   pinMode(ENA, OUTPUT);
   digitalWrite(ENA, LOW);
}

void move_motor_CW(){
  digitalWrite(dir_pin, LOW);  // LOW = clockwise)
  for (int x = 1; x < StepsToTake; x++) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(150);
    digitalWrite(step_pin, LOW); 
    delayMicroseconds(150);         
  }
}

void move_motor_CCW(){
  digitalWrite(dir_pin, HIGH);  // HIGH = anti-clockwise
  for (int x = 1; x < StepsToTake; x++) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(150);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(150);           
  }
}

//void loop2() {
//  Serial.begin(9600);   
//
//  for (int i = 0; i < 10; i++){
//      Serial.println(i); 
//  }            
//}


//void loop1 ()  {
//
//  if (!(digitalRead(PinSW))) {   // check if button is pressed
//  if (StepperPosition == 0) {  // check if button was already pressed
//  } 
//  else {
//      if (StepperPosition > 0) {  // Stepper was moved CW
//        while (StepperPosition != 0){  //  Do until Motor position is back to ZERO
//          digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
//          for (int x = 1; x < StepsToTake; x++) {
//              digitalWrite(step_pin, HIGH);
//              delayMicroseconds(speeds);
//              digitalWrite(step_pin, LOW);
//              delayMicroseconds(speeds);          
//            }
//            StepperPosition=StepperPosition-StepsToTake;
//        }
//      }
//      //if StepperPosition < 0
//      else {
//        while (StepperPosition != 0){ 
//          digitalWrite(dir_pin, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
//              for (int x = 1; x < StepsToTake; x++) {
//              digitalWrite(step_pin, HIGH);
//              delayMicroseconds(speeds);
//              digitalWrite(step_pin, LOW);
//              delayMicroseconds(speeds);           
//            }
//           StepperPosition=StepperPosition+StepsToTake;
//        }
//      }
//      StepperPosition=0; // Reset position to ZERO after moving motor back
//    }
//  }
//
//// Runs if rotation was detected
//  if (TurnDetected)  {
//        TurnDetected = false;  // do NOT repeat IF loop until new rotation detected
//
//// Which direction to move Stepper motor
//        if (rotationdirection) { // Move motor CCW
//            digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
//            for (int x = 1; x < StepsToTake; x++) {
//              digitalWrite(step_pin, HIGH);
//              delayMicroseconds(speeds);
//              digitalWrite(step_pin, LOW);
//              delayMicroseconds(speeds);           
//            }
//            StepperPosition=StepperPosition-StepsToTake;
//        }
//
//        if (!rotationdirection) { // Move motor CW
//            digitalWrite(dir_pin, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
//            for (int x = 1; x < StepsToTake; x++) {
//              digitalWrite(step_pin, HIGH);
//              delayMicroseconds(speeds);
//              digitalWrite(step_pin, LOW); 
//              delayMicroseconds(speeds);         
//            }
//            StepperPosition=StepperPosition+StepsToTake;
//        }
//  }
//} 
