
#define ENA 46
const int directio = 50;     // the number of the pushbutton pin
const int ste =  48;      // the number of the LED pin

// variables will change:
int distance3 = 0;
int SPEED1 = 500;
int done1 = 0;


void xsetup() {
  // initialize the LED pin as an output:
  pinMode(ste, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(directio, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(ENA, LOW); 
} 

void xloop() {

    while(distance3 < 1){
      digitalWrite(ste, HIGH);
      delayMicroseconds(SPEED1);
      digitalWrite(ste, LOW);
      distance3 = distance3 + 1;
    }

  
}
