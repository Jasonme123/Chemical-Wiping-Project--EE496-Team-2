//For arduino Mega

//Motor Control
////////////////////////////////////////////////////////////////////
#define X_STEP_HIGH             PORTH |=  0b00010000; //D7
#define X_STEP_LOW              PORTH &= ~0b00010000;

//z - motor step pin
#define Z_STEP_HIGH             PORTL |=  0b00000010; //D48
#define Z_STEP_LOW              PORTL &= ~0b00000010;

//x motor pins
#define X_DIR_PIN          6
#define X_STEP_PIN         7
#define X_ENABLE_PIN       52

//z motor pins
#define Z_DIR_PIN          50
#define Z_STEP_PIN         48 
#define Z_ENABLE_PIN       46

//////////////////////////////////////////////////////////////////
//pump1 motor 
#define Z_DIR_PIN          44
#define Z_STEP_PIN         42
#define Z_ENABLE_PIN       40

//pump2 motor 
#define Z_DIR_PIN          34
#define Z_STEP_PIN         38
#define Z_ENABLE_PIN       36

//////////////////////////////////////////////////////////////////
//Load Cell Reading
// HX711 circuit wiring
#define LOADCELL_DOUT_PIN  20;
#define LOADCELL_SCK_PIN   21;

//////////////////////////////////////////////////////////////////
// Camera Control
#define shutter_control    30;
//#define focus_control    31;

//////////////////////////////////////////////////////////////////
//LED PCB
#define bright_pin         5;

//////////////////////////////////////////////////////////////////
//Endstops
#define x_min_stop         17;
#define x_max_stop         16;    

#define z_min_stop         18;

//////////////////////////////////////////////////////////////////
//Endstops
#define hard_pause         19;

//////////////////////////////////////////////////////////////////
//AUX PINS (unused but availble)

//#define (anything)         4; //(PWM/Digital)
//#define (anything)         14; //(TX3/Digital)
//#define (anything)         15; //(RX3/Digital)
//#define (anything)         27; //(Digital)
//#define (anything)         29; //(Digital)
//#define (anything)         33; //(Digital)
//#define (anything)         35; //(Digital)

//#define (anything)         A8; //(Analog)
//#define (anything)         A9; //(Analog)
//#define (anything)         A10; //(Analog)
//#define (anything)         A11; //(Analog)
//#define (anything)         A12; //(Analog)
//#define (anything)         A13; //(Analog)
//#define (anything)         A14; //(Analog)
//#define (anything)         A15; //(Analog)

//////////////////////////////////////////////////////////////////
//LCD User defined Parameters
double wipe_Distance = 3; // (inches)
int num_Cycles = 10; //number of cycles

//////////////////////////////////////////////////////////////////
//X-motor Config
double x_Gear = 12;  //X motor gear diameter (mm)
int rev_Step = 1600; //Steps Per revolution
double x_circumference = (3.14159 * x_Gear * 0.0393); //x motor gear circumference (inches) 
volatile int x_movement = (rev_Step * (wipe_Distance / x_circumference)); // X axis movement in steps

boolean xPosition_Update = false;
int xcelleraion = 100;
int xMin_Interval = 15;

//////////////////////////////////////////////////////////////////
//Z-motor Config
boolean zPosition_Update = false;
int z_movement = 1000;
int zcelleration = 1000;
int zMin_Interval = 50;

//////////////////////////////////////////////////////////////////
//Force Controller

double Force;

// variables will change:
int distance;
int SPEED;
int done = 0;
boolean M_direction;
double Output_Position;
