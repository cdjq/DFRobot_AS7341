/*!
 * @file getData.ino
 * @brief 通过syns模式读取光谱数据,每次测量时都需要一个电平脉冲激活芯片的测量功能，
    测量结束后芯片进入idle模式，可以节省电量
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
  while (as7341.begin(as7341.eSyns) != 0) {
    Serial.println("IIC初始化失败，请检测连线是否正确");
    delay(1000);
  }
  //设置寄存器ATIME的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
  as7341.setAtime(100);
  //设置ASTEP寄存器的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
  as7341.setAstep(999);
  //设置增益(0~10对应 X0.5,X1,X2,X4,X8,X16,X32,X64,X128,X256,X512)
  as7341.setAGAIN(9);
 // as7341.config(as7341.eSyns);
  pinMode(AS7341_GPIO, OUTPUT);
  digitalWrite(AS7341_GPIO, HIGH);
  //开始光谱的测量.
  //通道映射的模式 :1.eF1F4ClearNIR,2.eF5F8ClearNIR
  as7341.startMeasure(as7341.eF1F4ClearNIR);
 // as7341.startMeasure(as7341.eF5F8ClearNIR);
}
void loop(void)
{
  DFRobot_AS7341::sModeOneData_t data1;
  DFRobot_AS7341::sModeTwoData_t data2;
  
  //通过gpio脉冲使传感器进入测量模式
  while(!as7341.measureComplete()){
     digitalWrite(AS7341_GPIO, LOW);
     delay(15);
     digitalWrite(AS7341_GPIO, HIGH);
    }
    

  
  //读取传感器数据通道0~5的值，eF1F4ClearNIR模式下.
  data1 = as7341.readSpectralDataOne();
  
  Serial.print("ADC0/F1-(紫色) ");
  Serial.println(data1.ADF1);
  Serial.print("ADC1/F2-(靛)");
  Serial.println(data1.ADF2);
  Serial.print("ADC2/F3-(蓝紫)");
  Serial.println(data1.ADF3);
  Serial.print("ADC3/F4-(蓝)");   
  Serial.println(data1.ADF4);
  //Serial.print("ADC4/Clear-(红外)");
  //Serial.println(data1.ADCLEAR);
  //Serial.print("ADC5/NIR-");
  //Serial.println(data1.ADNIR);
  //delay(1000);
  /*
  //as7341.startMeasure(as7341.eF5F8ClearNIR);
  //读取传感器数据通道0~5的值,eF5F8ClearNIR模式下.
  data2 = as7341.readSpectralDataTwo();
  Serial.print("ADC0/F5-(绿色) ");
  Serial.println(data2.ADF5);
  Serial.print("ADC1/F6-(黄)");
  Serial.println(data2.ADF6);
  Serial.print("ADC2/F7-(橙)");
  Serial.println(data2.ADF7);
  Serial.print("ADC3/F8-(红)");   
  Serial.println(data2.ADF8);
  Serial.print("ADC4/Clear-(红外)");
  Serial.println(data2.ADCLEAR);
  Serial.print("ADC5/NIR-");
  Serial.println(data2.ADNIR);
*/
  delay(1000);
  
}