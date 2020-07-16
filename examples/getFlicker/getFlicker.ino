/*!
 * @file getFlicker.ino
 * @brief 读取光源的闪烁频率
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
  //检测IIC是否能正常通信
  while (as7341.begin() != 0) {
    Serial.println("IIC初始化失败，请检测连线是否正确");
    delay(1000);
  }
  
}

void loop(void){
  uint8_t freq = 0;
  //设置寄存器ATIME的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
  as7341.setAtime(100);
  //设置ASTEP寄存器的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
  as7341.setAstep(999);
  //设置增益(0~10对应 X0.5,X1,X2,X4,X8,X16,X32,X64,X128,X256,X512)
  as7341.setAGAIN(9);
  
  //读取flicker寄存器的值，可据此预计光源的闪烁频率
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