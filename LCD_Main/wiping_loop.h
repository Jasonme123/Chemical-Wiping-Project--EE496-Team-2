
// Function For Z-Axis Homing 
void testing_cycle(uint8_t param) {
// ****** SETUP *********
   if(LCDML.FUNC_setup())   
  {
    
   //Reset Wipe Counter
   Current_Count = 0; 

  //Take user parmaeters and assign them to useful varibles
   Wipe_Dist = (rev_Step * (wipe_distance / x_circumference)); //Wipe Distance in steps
   Init_Pos = (rev_Step * (init_position / x_circumference)); //Inital Position in steps
   Force_Target = wipe_force; //Force we are attempting to Achieve with the Z-axis
   Cycle_Target = cycle_num; //Number of wipes per each test
   Photo_Int = photo_interval; //number of wipes between a Photo is taken
   Pump_Rate = ((flow_rate/(1.06)) * 1600); // Flow rate in Steps/Wipe
   Wipe_Speed = wipe_speed;
   Pump_Used = pump;

//If you don't want photos
    if(Photo_Int == 0){
    Photo_Int = 4294967295;
  }

  //light up enclosure to normal brightness
   analogWrite(bright_pin, Norm_Brightness); 
   
    LCDML_UNUSED(param);// remove compiler warnings when the param variable is not used:
  }  


  uint32_t position_ = 0 ;

  if(LCDML.FUNC_loop())   // ****** LOOP *********
  {   


  if((Current_Count % Photo_Int) == 0){
    Photo();
  }

  if(Pumping_Needed){
    pump(Pump_Rate); //Pumping done per wipe 
  }
    

      while (position_ != init_position) {
          if (position_ < init_position) {
         
              position_++;
              Serial.print("position:  ");
              Serial.println(position_);

              char string[20];         
              itoa(position_, string , 10);
              
              u8g.firstPage();
              do {
                u8g.setFont(u8g_font_ncenB10);
                u8g.drawStr(10, 50, string);
              } while(u8g.nextPage());
          }        
      }
      
      while (cycle_num != 0) {
        
            for (int i = 0; i < wipe_distance; i++){
                move_motor_CW();
                Serial.print("position:  ");
                Serial.println(i);
                if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
                {
                  LCDML.FUNC_goBackToMenu(1);  // leave this function
                }
            }
            for (int i = wipe_distance; i > 0; i--){
                move_motor_CCW();
                Serial.print("position:  ");
                Serial.println(i);
                if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
                {
                  LCDML.FUNC_goBackToMenu(1);  // leave this function
                }
            }
              cycle_num--;
              Serial.print("Cycles Left:  ");
              Serial.println(cycle_num);

              char string[20];         
              itoa(cycle_num, string , 10);

              char string2[20];         
              itoa(cycle_num_, string2 , 10);

              u8g.firstPage();
              do {
                u8g.drawFrame(1,1,126,62);
                u8g.drawFrame(0,0,128,64);
                u8g.drawFrame(19,35,90,24);
                u8g.setFont(u8g_font_ncenB10);
                u8g.drawStr( 5, 16, F("CYCLES LEFT:"));
                u8g.drawStr(ALIGN_CENTER(string), 31, string);
                u8g.drawStr(70 , 31, "/");
                u8g.drawStr(80 , 31, string2);
//                u8g.setFont(u8g_font_ncenB08);
//                u8g.drawStr(ALIGN_CENTER("Rotate Or Click"), 46, F("Rotate Or Click"));
//                u8g.drawStr(ALIGN_CENTER("To Pause"), 56, F("To Pause"));
              } while(u8g.nextPage());
             

              if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
              {
                LCDML.FUNC_goBackToMenu(1);  // leave this function
              }
          }        
      }
      LCDML.FUNC_goBackToMenu(0);
//      u8g.setFont(u8g_font_ncenB08);
//      u8g.drawStr(ALIGN_CENTER("Z Axis is homed"), 58, F("Z Axis is homed"));
   }  
