
#define ENA1 40
#define ENA2 36

const int directio1 = 44;     // the number of the pushbutton pin
const int ste1 = 42;  // the number of the LED pin


const int directio2 = 34;     // the number of the pushbutton pin
const int ste2 =  38;  

// variables will change:
int distance = 0;
int SPEED = 300;
int done = 0;

// setup Variable
int Direct = HIGH;
double Rotations = 10;
int distance2 = Rotations*1600;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ste1, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(directio1, OUTPUT);
   // initialize the LED pin as an output:
  pinMode(ste2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(directio2, OUTPUT);

  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);

  digitalWrite(ENA1, LOW);
  digitalWrite(ENA2, LOW);
}

void loop() {

  
digitalWrite(directio1, Direct);
digitalWrite(directio2, Direct);

while(distance < distance2){
  digitalWrite(ste1, HIGH);
  digitalWrite(ste2, HIGH);
  delayMicroseconds(SPEED);
  digitalWrite(ste1, LOW);
  digitalWrite(ste2, LOW);
  distance = distance + 1;
}


}
