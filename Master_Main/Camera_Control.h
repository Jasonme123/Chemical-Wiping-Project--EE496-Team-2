
//https://elliotthilaire.net/how-to-connect-your-camera-to-arduino/


int led = 13;
int opto = 12;
 
// the setup routine runs once when you press reset:
void setup()
{
// initialize the digital pin as an output.
pinMode(led, OUTPUT);
pinMode(opto, OUTPUT);
}
 
// the loop routine runs over and over again forever:
void loop()
{
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
digitalWrite(opto, HIGH);
delay(1000);               // wait for a second
digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
digitalWrite(opto, LOW);
delay(1000);               // wait for a second
}
//save
