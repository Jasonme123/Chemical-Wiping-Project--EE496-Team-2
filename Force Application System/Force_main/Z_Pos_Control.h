#define ENA1 40
#define ENA2 36

//#include "Control_System.h"
const int directio1 = 44;     // Motor_1 Direction
const int ste1 =  42;      // Motor_2 Step

const int directio2 = 34;     //Motor_2 Direction
const int ste2 =  38;         //Motor_2 Step


// variables will change:
int distance;
int SPEED;
int done = 0;
boolean M_direction;
double Output_Position;


void Motor_setup() {

  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);

  digitalWrite(ENA1, LOW);
  digitalWrite(ENA2, LOW);
  
  //Motor 1
  pinMode(ste1, OUTPUT);
  pinMode(directio1, OUTPUT);
  //Motor 2
  pinMode(ste2, OUTPUT);
  pinMode(directio2, OUTPUT);

 //SPEED = map(Output_Position, 0, 255, 1200, 500);
 
}

void Motor_loop() {
  distance = 0;
   SPEED = map(Output_Position, 0, 255, 1200, 500);
digitalWrite(directio1, M_direction);
digitalWrite(directio2, M_direction);

while(distance < Output_Position){
  digitalWrite(ste1, HIGH);
  digitalWrite(ste2, HIGH);
  delayMicroseconds(SPEED);
  digitalWrite(ste1, LOW);
  digitalWrite(ste2, LOW);
  distance = distance + 1;

}
 }
