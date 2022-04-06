
//Hardware Design Info
//https://elliotthilaire.net/how-to-connect-your-camera-to-arduino/

//Camera Info
//https://www.ricoh-imaging.co.jp/english/r_dc/gx/gx200/option.html

//Pulse Info
//http://stereo.jpn.org/eng/sdm/ca1.htm
 

void Camera_setup()
{
// initialize the digital pins as an output.
pinMode(shutter_control, OUTPUT);
//pinMode(focus_control, OUTPUT);
}
 
void Photo()
{
  
  home_x_axis();
  home_z_axis();
  
  analogWrite(bright_pin, Photo_Brightness); //light up enclosure to Photo brightness
  digitalWrite(shutter_control, HIGH);   //Push Buttom
  delay(150);               //Full Shoot Mode
  digitalWrite(shutter_control, LOW);    //Release Button
  analogWrite(bright_pin, Norm_Brightness); //light up enclosure to normal brightness

  TIMER1_INTERRUPTS_ON              //I think this will work... It is supposed to return the wipe back to the intial position before continuing wiping
  prepareMovement( 0,  Init_Pos );
  while(!xPosition_Update);
  Current_Count--;
  
  touchDown();
}
