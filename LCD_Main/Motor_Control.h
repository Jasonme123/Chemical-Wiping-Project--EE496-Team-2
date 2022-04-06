  // For Senior Design

//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////

struct stepperInfo {
  // externally defined parameters
  float acceleration;
  volatile unsigned int minStepInterval;   // ie. max speed, smaller is faster
  void (*dirFunc)(int);
  void (*stepFunc)();

  // derived parameters
  unsigned int c0;                // step interval for first step, determines acceleration
  long stepPosition;              // current position of stepper (total of all movements taken so far)

  // per movement variables (only changed once per movement)
  volatile int dir;                        // current direction of movement, used to keep track of position
  volatile unsigned int totalSteps;        // number of steps requested for current movement
  volatile bool movementDone = false;      // true if the current movement has been completed (used by main program to wait for completion)
  volatile unsigned int rampUpStepCount;   // number of steps taken to reach either max speed, or half-way to the goal (will be zero until this number is known)

  // per iteration variables (potentially changed every interrupt)
  volatile unsigned int n;                 // index in acceleration curve, used to calculate next interval
  volatile float d;                        // current interval length
  volatile unsigned long di;               // above variable truncated
  volatile unsigned int stepCount;         // number of steps completed in current movement
};

void xStep() {
  X_STEP_HIGH
  X_STEP_LOW
}
void xDir(int dir) {
  digitalWrite(X_DIR_PIN, dir);
}

void zStep() {
  Z_STEP_HIGH
  Z_STEP_LOW
}
void zDir(int dir) {
  digitalWrite(Z_DIR_PIN, dir);
}

void disable_Stepper(){
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);
}

void enable_Stepper(){
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
}

void resetStepperInfo( stepperInfo& si ) {
  si.n = 0;
  si.d = 0;
  si.di = 0;
  si.stepCount = 0;
  si.rampUpStepCount = 0;
  si.totalSteps = 0;
  si.stepPosition = 0;
  si.movementDone = false;
}

#define NUM_STEPPERS 2

volatile stepperInfo steppers[NUM_STEPPERS];

void Motorsetup() {

  pinMode(X_STEP_PIN,   OUTPUT);
  pinMode(X_DIR_PIN,    OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN,   OUTPUT);
  pinMode(Z_DIR_PIN,    OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  //enables motors
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  
////////////////////////////////////////////
  noInterrupts(); // Timing protection
//Timer 1 (to send motor movemment commands)
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 1000;                             // compare value
  TCCR1B |= (1 << WGM12);                   // CTC mode
  TCCR1B |= ((1 << CS11) | (1 << CS10));    // 64 prescaler
//////////////////////////////////////////////////////////////////////////
//Timer 2 (to check if the motor position target needs to be updated)
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  
  OCR2A = 1000;                             // compare value
  TCCR2B |= (1 << WGM12);                   // CTC mode
  TCCR2B |= ((1 << CS11) | (1 << CS10));    // 64 prescaler
  interrupts();
///////////////////////////////////////////////

//x motor
  steppers[0].dirFunc = xDir;
  steppers[0].stepFunc = xStep;
  steppers[0].acceleration = xcelleraion;
  steppers[0].minStepInterval = xMin_Interval;
  
//z motor
  steppers[1].dirFunc = zDir;
  steppers[1].stepFunc = zStep;
  steppers[1].acceleration = zcelleration;
  steppers[1].minStepInterval = zMin_Interval;
}

/////////////////////////////////////////////////
void resetStepper(volatile stepperInfo& si) {
  si.c0 = si.acceleration;
  si.d = si.c0;
  si.di = si.d;
  si.stepCount = 0;
  si.n = 0;
  si.rampUpStepCount = 0;
  si.movementDone = false;
}
////////////////////////////////////////////////

volatile byte remainingSteppersFlag = 0;

////////////////////////////////////////////////
void prepareMovement(int whichMotor, int steps) {
  volatile stepperInfo& si = steppers[whichMotor];
  si.dirFunc( steps < 0 ? HIGH : LOW );
  si.dir = steps > 0 ? 1 : -1;
  si.totalSteps = abs(steps);
  resetStepper(si);
  remainingSteppersFlag |= (1 << whichMotor);
}
////////////////////////////////////////////////

volatile byte nextStepperFlag = 0;
volatile int ind = 0;
volatile unsigned int intervals[100];

////////////////////////////////////////////////
void setNextInterruptInterval() {
  
  bool movementComplete = true;

  unsigned int mind = 999999;
  for (int i = 0; i < NUM_STEPPERS; i++) {
    if ( ((1 << i) & remainingSteppersFlag) && steppers[i].di < mind ) {
      mind = steppers[i].di;
    }
  }

  nextStepperFlag = 0;
  for (int i = 0; i < NUM_STEPPERS; i++) {
    if ( ! steppers[i].movementDone )
      movementComplete = false;

    if ( ((1 << i) & remainingSteppersFlag) && steppers[i].di == mind )
      nextStepperFlag |= (1 << i);
  }

  if ( remainingSteppersFlag == 0 ) {
    OCR1A = 65500;
  }

  OCR1A = mind;
}

//////////////////////////////////////////////
//Interrrupt Service Routine

ISR(TIMER1_COMPA_vect)
{
  unsigned int tmpCtr = OCR1A;

  OCR1A = 65500;

  for (int i = 0; i < NUM_STEPPERS; i++) {    //If there are steps a motor still needs to take
    if (! ((1 << i) & remainingSteppersFlag))
      continue;

    if ( ! (nextStepperFlag & (1 << i)) ) {   //If the motor selected is not next update wait interval
      steppers[i].di -= tmpCtr;               // next sepper interval equal to delay minus current interval per step length
      continue;
    }

    volatile stepperInfo& s = steppers[i];

    if ( s.stepCount < s.totalSteps ) { 
      s.stepFunc();
      s.stepCount++;
      s.stepPosition += s.dir;
      if ( s.stepCount >= s.totalSteps ) {
        s.movementDone = true;
        remainingSteppersFlag &= ~(1 << i);
      }
    }

    if ( s.rampUpStepCount == 0 ) {
      s.n++;
      s.d = s.d - (2 * s.d) / (4 * s.n + 1);
      if ( s.d <= s.minStepInterval ) {
        s.d = s.minStepInterval;
        s.rampUpStepCount = s.stepCount;
      }
      if ( s.stepCount >= s.totalSteps / 2 ) {
        s.rampUpStepCount = s.stepCount;
      }
    }
    else if ( s.stepCount >= s.totalSteps - s.rampUpStepCount ) {
      s.d = (s.d * (4 * s.n + 1)) / (4 * s.n + 1 - 2);
      s.n--;
    }

    s.di = s.d; // long delay value for next step of the motor
  }

  setNextInterruptInterval();
  
  TCNT1  = 0;
}

void runAndWait() {
  setNextInterruptInterval();
  //while ( remainingSteppersFlag );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TIMER2_INTERRUPTS_ON    TIMSK2 |=  (1 << OCIE2A);
#define TIMER2_INTERRUPTS_OFF   TIMSK2 &= ~(1 << OCIE2A);

 //////////////////////////////////////////////////////////
ISR(TIMER2_COMPA_vect){
 //X-Axis Wiping Cycle

volatile stepperInfo& sx = steppers[0];
if(sx.movementDone){    
 xPosition_Update = true;
 Current_Count++;
 Pump(Pump_Rate); //Pumping done per wipe 
 //x_movement = (x_movement * -1);
}

//////////////////////////////////////////////////////////
//Motor Command Sender
  
//if x motor target changes, tell the motor to move to the new target  
   
     if(xPosition_Update){  
       xPosition_Update = false;
      // prepareMovement( 0,  x_movement); //xmotor
       runAndWait();
     }
     
//if z motor target changes, tell the motor to move to the new target

     if(zPosition_Update){
      zPosition_Update = false;
      prepareMovement( 1,  z_movement ); //zmotor
      runAndWait();
     }
   
}
