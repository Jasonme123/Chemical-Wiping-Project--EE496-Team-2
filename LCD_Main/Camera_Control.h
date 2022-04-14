//Hardware Design Info
//https://elliotthilaire.net/how-to-connect-your-camera-to-arduino/

//Camera Info
//https://www.ricoh-imaging.co.jp/english/r_dc/gx/gx200/option.html

//Pulse Info
//http://stereo.jpn.org/eng/sdm/ca1.htm

#include "includes.h"

void Camera_setup() {
  // put your setup code here, to run once:
  // initialize the digital pins as an output.
  pinMode(shutter_control, OUTPUT);
  //pinMode(focus_control, OUTPUT);
}

void Photo() {
  
  TIMER1_INTERRUPTS_OFF
  homeBoth();
  
      delay(1000);
      analogWrite(bright_pin, Photo_Brightness);// 128 //light up enclosure to Photo brightness
      digitalWrite(shutter_control, HIGH);   //Push Buttom
      delay(30);
      digitalWrite(shutter_control, LOW);    //Release Button
      delay(150);               //Full Shoot Mode
      digitalWrite(shutter_control, HIGH);   //Push Buttom
      delay(150);
      digitalWrite(shutter_control, LOW);   //Push Buttom
      delay(1000); 
      analogWrite(bright_pin, Norm_Brightness); //light up enclosure to normal brightness


//move back to intial position
  while (Current_XPos < Init_Pos){
    X_STEP_HIGH;
    delayMicroseconds(150);
    X_STEP_LOW;
    delayMicroseconds(150);
    Current_XPos++;
  }
TIMER1_INTERRUPTS_ON
}
