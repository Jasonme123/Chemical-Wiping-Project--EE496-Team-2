double high_dist = 9;
double low_distance = 0.5;
void wipe_distance_error(){
  Serial.println("OH shit");
  Serial.print("Wipe Distance set to :  ");
  Serial.print(wipe_Distance);
  
  while(1);
}

void safety_Check(){
if((0.5 > wipe_Distance)|| (wipe_Distance > high_dist)){
wipe_distance_error();
}
}
