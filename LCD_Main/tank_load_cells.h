#ifndef TANKLOADCELLS
#define TANKLOADCELLS

#include "includes.h"

int16_t emptyTankWeight; 
int16_t fullTankWeight;
int16_t curr_weight;    

void check_containers(){

    if (Pump_Used == 0 || Pump_Used == 2){
      curr_weight = analogRead(AnalogInPin0);
      if (curr_weight <= fullTankWeight*0.05 + emptyTankWeight){
        is_empty = true;
      }
    } else if (Pump_Used == 1 || Pump_Used == 2) {
      curr_weight = analogRead(AnalogInPin1);
      if (curr_weight <= fullTankWeight*0.05 + emptyTankWeight){
        is_empty = true;
      }
    } 
}

#endif
