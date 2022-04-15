//This is where we can call all of our setup functions
#include "includes.h"

void function_setup(){

Pump_setup(); //Pump Setup
Camera_setup(); //Camera Setup
LoadCell_setup(); //Force feedback load cell setup
Control_setup(); //force controller setup 
homingSetup(); //endstop pinmode setup
disable_Stepper();
}
