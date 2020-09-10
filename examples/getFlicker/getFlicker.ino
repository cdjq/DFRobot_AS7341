/*!
 * @file getFlicker.ino
 * @brief Read the flicker frequency of light source 
 * 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-07-16
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_AS7341
 */
#include "DFRobot_AS7341.h"
/*!
 * @brief Construct the function
 * @param pWire IC bus pointer object and construction device, can both pass or not pass parameters, Wire in default.
 */
DFRobot_AS7341 as7341;


void setup(void)
{
  Serial.begin(115200);
  //Detect if IIC can communicate properly
  while (as7341.begin() != 0) {
    Serial.println("IIC init failed, please check if the wire connection is correct");
    delay(1000);
  }
  
}

void loop(void){
  uint8_t freq = 0;
  //Set the value of register ATIME, through which the value of Integration time can be calculated. The value represents the time that must be spent during data reading.
  as7341.setAtime(100);
  //Set the value of register ASTEP, through which the value of Integration time can be calculated. The value represents the time that must be spent during data reading.
  as7341.setAstep(999);
  //Set gain value(0~10 corresponds to X0.5,X1,X2,X4,X8,X16,X32,X64,X128,X256,X512)
  as7341.setAGAIN(9);
  
  //Read the value of register flicker, through which the flicker frequency of the light source can be predicted
  freq = as7341.readFlickerData();
  //Serial.println(freq);
  if (freq == 44) {
    Serial.println("Unknown frequency");

  } else if (freq == 45) {
    Serial.println("100 Hz ");

  } else if (freq == 46) {
    Serial.println("120 Hz ");
  } else {
    Serial.println("An unknown error");
  }
 



}
