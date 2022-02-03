//For arduino Mega
////////////////////////////////////////////////////////////////////
#define X_STEP_HIGH             PORTH |=  0b00010000; //D6
#define X_STEP_LOW              PORTH &= ~0b00010000;

//z - motor step pin
//#define Z_STEP_HIGH             PORTL |=  0b00000010; //D48
//#define Z_STEP_LOW              PORTL &= ~0b00000010;

//x motor pins
#define X_DIR_PIN          6
#define X_STEP_PIN         7
#define X_ENABLE_PIN       52

//z motor pins
//#define Z_DIR_PIN          50
//#define Z_STEP_PIN         48
//#define Z_ENABLE_PIN       46

//////////////////////////////////////////////////////////////////
//pump1 motor test
#define Z_DIR_PIN          44
#define Z_STEP_PIN         42
#define Z_ENABLE_PIN       40

//pump1 motor test
#define Z_STEP_HIGH             PORTL |=  0b10000000; //D42
#define Z_STEP_LOW              PORTL &= ~0b10000010;
//////////////////////////////////////////////////////////////////
//LCD User defined Parameters
double wipe_Distance = 4; // (inches)
int num_Cycles = 10; //number of cycles

//////////////////////////////////////////////////////////////////
//X-motor Config
double x_Gear = 12;  //X motor gear diameter (mm)
int rev_Step = 1600; //Steps Per revolution
double x_circumference = (3.14159 * x_Gear * 0.0393); //x motor gear circumference (inches) 
volatile int x_movement = (rev_Step * (wipe_Distance / x_circumference)); // X axis movement in steps

boolean xPosition_Update = false;

//////////////////////////////////////////////////////////////////
//Z-motor Config
boolean zPosition_Update = false;
int z_movement = 10000;
