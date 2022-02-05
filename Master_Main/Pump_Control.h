
#define ENA 46
const int directio = 50;     // the number of the pushbutton pin
const int ste =  48;      // the number of the LED pin

// variables will change:
int distance = 0;
int SPEED = 500;
int done = 0;


void setup() {
  // initialize the LED pin as an output:
  pinMode(ste, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(directio, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(ENA, LOW); 
}

void loop() {
//delay(4);
distance = 0;
  
digitalWrite(directio, HIGH);
if (done < 200){
while(distance < 1600){
  digitalWrite(ste, HIGH);
  delayMicroseconds(SPEED);
  digitalWrite(ste, LOW);
  distance = distance + 1;
}
done = done + 1;
 }

 

  
}
