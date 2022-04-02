//Motor Control Pins
#define step_pin 7  // Pin 9 connected to Steps pin
#define dir_pin 6   // Pin 8 connected to Direction pin
#define ENA 52
                    
volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation

// Rotary Encoder Module connections
const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=3;    // Reading DT signal
const int PinSW=32;    // Reading Push Button switch

int StepperPosition=0;    // To store Stepper Motor Position
int StepsToTake=400;      // Controls the speed of the Stepper per Rotary click

int speeds = 150;

int direction;   // Variable to set Rotation (CW-CCW) of stepper


// Interrupt routine runs if CLK goes from HIGH to LOW
void rotarydetect ()  {
delay(2);  // delay for Debouncing
if (digitalRead(PinCLK))
rotationdirection= digitalRead(PinDT);
else
rotationdirection= !digitalRead(PinDT);

TurnDetected = true;
}


void setup ()  {

   ///////////////////////////
   pinMode(dir_pin, OUTPUT); // Motor control
   pinMode(step_pin, OUTPUT);
   pinMode(ENA, OUTPUT);
   digitalWrite(ENA, LOW);

   
  pinMode(PinCLK,INPUT);  // Set Pin to Input
  pinMode(PinDT,INPUT);  
  pinMode(PinSW,INPUT);
  digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch
  attachInterrupt (0,rotarydetect,FALLING); // interrupt 0 always connected to pin 2
}

void loop ()  {

  if (!(digitalRead(PinSW))) {   // check if button is pressed
  if (StepperPosition == 0) {  // check if button was already pressed
  } 
  else {
      if (StepperPosition > 0) {  // Stepper was moved CW
        while (StepperPosition != 0){  //  Do until Motor position is back to ZERO
          digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
          for (int x = 1; x < StepsToTake; x++) {
              digitalWrite(step_pin, HIGH);
              delayMicroseconds(speeds);
              digitalWrite(step_pin, LOW);
              delayMicroseconds(speeds);          
            }
            StepperPosition=StepperPosition-StepsToTake;
        }
      }
      //if StepperPosition < 0
      else {
        while (StepperPosition != 0){ 
          digitalWrite(dir_pin, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
              for (int x = 1; x < StepsToTake; x++) {
              digitalWrite(step_pin, HIGH);
              delayMicroseconds(speeds);
              digitalWrite(step_pin, LOW);
              delayMicroseconds(speeds);           
            }
           StepperPosition=StepperPosition+StepsToTake;
        }
      }
      StepperPosition=0; // Reset position to ZERO after moving motor back
    }
  }

// Runs if rotation was detected
  if (TurnDetected)  {
        TurnDetected = false;  // do NOT repeat IF loop until new rotation detected

// Which direction to move Stepper motor
        if (rotationdirection) { // Move motor CCW
            digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
            for (int x = 1; x < StepsToTake; x++) {
              digitalWrite(step_pin, HIGH);
              delayMicroseconds(speeds);
              digitalWrite(step_pin, LOW);
              delayMicroseconds(speeds);           
            }
            StepperPosition=StepperPosition-StepsToTake;
        }

        if (!rotationdirection) { // Move motor CW
            digitalWrite(dir_pin, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
            for (int x = 1; x < StepsToTake; x++) {
              digitalWrite(step_pin, HIGH);
              delayMicroseconds(speeds);
              digitalWrite(step_pin, LOW); 
              delayMicroseconds(speeds);         
            }
            StepperPosition=StepperPosition+StepsToTake;
        }
  }
} 
