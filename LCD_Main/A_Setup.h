//This is where we can call all of our setup functions


void function_setup(){
//x_min_setup(); //min endstop setup
Pump_setup(); //Pump Setup
Camera_setup(); //Camera Setup
LoadCell_setup(); //Force feedback load cell setup
Control_setup(); //force controller setup 
}
