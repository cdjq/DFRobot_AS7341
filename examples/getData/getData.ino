/*!
 * @file getData.ino
 * @brief 读取光谱传感器10个光通道的数值，光源的某波长的光越多，对应通道的数值越大
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
  //Integration time = (ATIME + 1) x (ASTEP + 1) x 2.78µs
  //设置寄存器ATIME的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
  as7341.setAtime(29);
  //设置ASTEP寄存器的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
  as7341.setAstep(599);
  //设置增益(0~10对应 X0.5,X1,X2,X4,X8,X16,X32,X64,X128,X256,X512)
  as7341.setAGAIN(7);
  //使能LED
  //as7341.enableLed(true);
  //设置引脚电流控制亮度(0~20对应电流 4mA,6mA,8mA,10mA,12mA,......,42mA)
  //as7341.controlLed(0);

}
void loop(void)
{
  DFRobot_AS7341::sModeOneData_t data1;
  DFRobot_AS7341::sModeTwoData_t data2;


  //开始光谱的测量.
  //通道映射的模式 :1.eF1F4ClearNIR,2.eF5F8ClearNIR
  as7341.startMeasure(as7341.eF1F4ClearNIR);
  //读取传感器数据通道0~5的值，eF1F4ClearNIR模式下.
  data1 = as7341.readSpectralDataOne();
  
  Serial.print("F1(405-425nm):");
  Serial.println(data1.ADF1);
  Serial.print("F2(435-455nm):");
  Serial.println(data1.ADF2);
  Serial.print("F3(470-490nm):");
  Serial.println(data1.ADF3);
  Serial.print("F4(505-525nm):");   
  Serial.println(data1.ADF4);
  //Serial.print("ADC4/Clear-(红外)");
  //Serial.println(data1.ADCLEAR);
  //Serial.print("ADC5/NIR-");
  //Serial.println(data1.ADNIR);
  //delay(1000);
  as7341.startMeasure(as7341.eF5F8ClearNIR);
  //读取传感器数据通道0~5的值,eF5F8ClearNIR模式下.
  data2 = as7341.readSpectralDataTwo();
  Serial.print("F5(545-565nm):");
  Serial.println(data2.ADF5);
  Serial.print("F6(580-600nm):");
  Serial.println(data2.ADF6);
  Serial.print("F7(620-640nm):");
  Serial.println(data2.ADF7);
  Serial.print("F8(670-690nm):");
  Serial.println(data2.ADF8);
  Serial.print("Clear:");
  Serial.println(data2.ADCLEAR);
  Serial.print("NIR:");
  Serial.println(data2.ADNIR);
  delay(1000);
}