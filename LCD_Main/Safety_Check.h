

  

void safety_Check(){
 
 
 if (scale.wait_ready_retry(10)){
   Serial.println("HX711 not found.");
 }
  

}
