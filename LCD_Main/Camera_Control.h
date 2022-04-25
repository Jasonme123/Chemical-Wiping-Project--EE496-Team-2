//Hardware Design Info
//https://elliotthilaire.net/how-to-connect-your-camera-to-arduino/

//Camera Info
//https://www.ricoh-imaging.co.jp/english/r_dc/gx/gx200/option.html

//Pulse Info
//http://stereo.jpn.org/eng/sdm/ca1.htm

#include "includes.h"

void Camera_setup() {

  pinMode(shutter_control, OUTPUT);  //Data direction Output the digital pin as an output

}

void Photo() {

  TIMER1_INTERRUPTS_OFF
  TIMER2_INTERRUPTS_OFF
  wiping = false;

  //Move wipe back to the home position to take photo
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

  digitalWrite(shutter_control, HIGH);   //Push Buttom
  delay(30);
  digitalWrite(shutter_control, LOW);    //Release Button
  delay(150);               //Full Shoot Mode
  digitalWrite(shutter_control, HIGH);   //Push Buttom
  delay(150);
  digitalWrite(shutter_control, LOW);   //Push Buttom
  delay(1000);
  
  analogWrite(bright_pin, Norm_Brightness); //light up enclosure to normal brightness

  intial_x_axis();
  touchDown();

  photo_taken = true;
  wiping = true;
  TIMER1_INTERRUPTS_ON
  TIMER2_INTERRUPTS_ON

}
