//For arduino Mega
#include "includes.h"

#ifndef CONFIGDEF
#define CONFIGDEF

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

//Wiping Movement Timer
#define TIMER1_INTERRUPTS_ON    TIMSK1 |=  (1 << OCIE1A);
#define TIMER1_INTERRUPTS_OFF   TIMSK1 &= ~(1 << OCIE1A);

#define TIMER2_INTERRUPTS_ON    TIMSK2 |=  (1 << OCIE2A);
#define TIMER2_INTERRUPTS_OFF   TIMSK2 &= ~(1 << OCIE2A);

//////////////////////////////////////////////////////////////////
//pump1 motor
#define P0_DIR_PIN          44
#define P0_STEP_PIN         42
#define P0_ENABLE_PIN       40

//pump2 motor
#define P1_DIR_PIN          34
#define P1_STEP_PIN         38
#define P1_ENABLE_PIN       36

//////////////////////////////////////////////////////////////////
//Load Cell Reading
// HX711 circuit wiring
#define LOADCELL_DOUT_PIN  20
#define LOADCELL_SCK_PIN   21

//////////////////////////////////////////////////////////////////
// Camera Control
#define shutter_control    30
//#define focus_control    31

//////////////////////////////////////////////////////////////////
//LED PCB
#define bright_pin         5

//////////////////////////////////////////////////////////////////
//Endstops
#define x_min_stop         17  //X-Endstop 1
#define x_max_stop         16  //X-Endstop 2

#define z_min_stop         18  //Z-Endstop 2

#define X_Homing_Speed       150
#define Z_Homing_Speed       150

boolean wiping = false;
boolean photo_taken = false;
boolean is_empty = false;


boolean x_zero = false;
boolean z_zero = false;
boolean x_max = false;

boolean endstopError = false;

uint32_t x_axis_length = 11600; //ADJUST THIS LATER
uint32_t z_axis_length = 9999999; //ADJUST THIS LATER

//////////////////////////////////////////////////////////////////
//Pause Button
#define hard_pause         19 //Z-Endstop 1
volatile boolean Play_state = true;
volatile byte Prev_state = HIGH;

///////////////////////////////////////////////////////////////////
//Status LEDs
#define Main_Status_LED    12 //on main board Status LED
//////////////////////////////////////////////////////////////////
//AUX PINS (unused but availble)

//#define (anything)         4; //(PWM/Digital)
//#define (anything)         14; //(TX3/Digital)
//#define (anything)         15; //(RX3/Digital)
#define RED         27; //Status LED
#define GREEN        29; //Status LED
//#define (anything)         33; //(Digital)
//#define (anything)         35; //(Digital)

#define AnalogInPin0         A8 //Tank1 Reading 
#define AnalogInPin1         A9 //Tank2 Reading

//#define (anything)         A10; //(Analog)
//#define (anything)         A11; //(Analog)
//#define (anything)         A12; //(Analog)
//#define (anything)         A13; //(Analog)
//#define (anything)         A14; //(Analog)
//#define (anything)         A15; //(Analog)


//////////////////////////////////////////////////////////////////
//X-motor Config
#define RIGHT HIGH
#define LEFT LOW

double x_Gear = 12;  //X motor gear diameter (mm)
int rev_Step = 1600; //Steps Per revolution
double x_circumference = (3.14159 * x_Gear * 0.0393); //x motor gear circumference (inches)

boolean xPosition_Update = false;
int xcelleraion = 250;
int xMin_Interval = 75;
uint32_t x_adjust_position = 0;
float x_adjust_position_in_inches = 0.0;


//////////////////////////////////////////////////////////////////
//Z-motor Config
#define DOWN HIGH
#define UP LOW

boolean zPosition_Update = false;
int z_movement = 1000;
int zcelleration = 1000;
int zMin_Interval = 150;
uint32_t z_adjust_position = 0;
float z_adjust_position_in_inches = 0.0;


//////////////////////////////////////////////////////////////////
//Pumping Parameters
#define To_Wipe LOW //defining direction for liquid movement (may need to change)
#define From_wipe HIGH

int Pumping_Speed = 1; //delay between steps in microseconds
int Priming_Speed = 300; //delay between steps in microseconds
uint32_t Tube_Volume = 49812; //((volume inside length of tube * (1600 / 1.06)) NOTE: trunctated but still good enough
boolean Pumping_Needed = false;

//////////////////////////////////////////////////////////////////
//Dynamic Parmaters
uint32_t wipe_distance = 0;
uint32_t init_position = 0;
float wipe_distance_in_inches = 0.0;
float init_position_in_inches = 0.0;

int16_t wipe_force = 1;
uint32_t Cycle_Target = 100;
uint32_t Photo_Interval = 0;
uint32_t flow_rate = 0;
float real_flow_rate = 0.0;
uint8_t wipe_speed = 10;  // Used For User Input as sprintf formatting of floating point values is not supported in Arduino
float real_wipe_speed = 1.0;  // Used For Actual Calculations
uint8_t pump = 0;
uint32_t increase_interval = 1;  // For setting Cycle Number
uint8_t Brightness = 0;
uint8_t delay_ = 0;
uint8_t Photo_Brightness;
uint32_t wipe_Delay = 0;

uint8_t Enclosure_Brightness = 0;
uint8_t real_Enclosure_Brightness;


//////////////////////////////////////////////////////////////////
//Parameter Input Assignment For Use of Wiping Cycle

int16_t Wipe_Dist = 3264;
uint32_t Init_Pos = 2176;
uint32_t Pump_Rate;
uint8_t Wiping_Speed;
uint8_t Pump_Used;
uint8_t Norm_Brightness = 128;


//////////////////////////////////////////////////////////////////
//Wipe Cycle Global

volatile uint32_t Current_Count = 0; //Wipe cycle countcvolatile uint32_t Current_XPos; //Current X
volatile uint32_t Current_XPos; //Current Z position
volatile uint32_t Current_ZPos; //Current Z position

//////////////////////////////////////////////////////////////////
//Force Controllers

boolean Z_direction;
int16_t Force_Target;
int16_t Force_Reading;
int16_t K_Const = 8;

double Force_Target_PID;
double Force_Reading_PID;

double Output_Position_PID;

// variables will change:
int distance;
int SPEED;
int done = 0;
int8_t M_direction;
uint32_t Output_Position;

#endif
