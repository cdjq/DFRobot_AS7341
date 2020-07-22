# DFRobot_AS7341

这是一款基于ams的最新的AS7341的可见光传感器，该传感器可以测量8个波长的可见光强度、100Hz或120Hz的环境光闪烁、NIR测量，拥有6个独立的ADC通道，可以并行的处理数据，相比传统的RGB颜色传感器，这款可见光传感器可以识别出真正的橙色。 

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
1.读取各个通道的数值
2.检测光源频闪是否为100HZ或120HZ


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods
```C++
/**
   * @brief init function
   * @return Return 0 if the initialization succeeds, otherwise return non-zero and error code.
   */
  int begin();

  /**
   * @brief 读取传感器的ID
   * @return 读取到的传感器ID,一个字节数据.
   */
  uint8_t readID();
  
  /**
   * @brief 设置寄存器ATIME的值，通过该值可计算Integration time的值，该值表示读取数据过程中必须要消耗的时间
   * @param ATIME寄存器的值.
   */
  void setAtime(uint8_t value);
  void setAstep(uint16_t value);
  /**
   * @brief 设置增益值(0~10对应 X0.5,X1,X2,X4,X8,X16,X32,X64,X128,X256,X512)
   * @param CFG1寄存器的值.
   */
  void setAGAIN(uint8_t value);

  /**
   * @brief 设置WTIME值，通过该值可计算 wite time，该值表示读取数据过程中必须要消耗的时间
   * @param WTIME的值.
   */
  void setWtime(uint8_t value);
  

  //void mapChannel(eChannel_t ADC0,eChannel_t ADC1,eChannel_t ADC2,eChannel_t ADC3,eChannel_t ADC4,eChannel_t ADC5);
  //void setGpio();
  /**
   * @brief 开始光谱的测量.
   * @param 通道映射的模式 :1.eF1F4ClearNIR,2.eF5F8ClearNIR
   */
  void startMeasure(eChChoose_t mode);
  /**
   * @brief 读取传感器数据通道0~5的值，eF1F4ClearNIR模式下.
   * @return sModeOneData_t 的数据
   */
  sModeOneData_t readSpectralDataOne();
  
  /**
   * @brief 读取传感器数据通道0~5的值,eF5F8ClearNIR模式下.
   * @return sModeTwoData_t 的数据
   */
  sModeTwoData_t readSpectralDataTwo();
  
  /**
   * @brief 读取flicker寄存器的值，可据此预计光源的闪烁频率
   * @return flicker寄存器的数据.
   */
  uint8_t readFlickerData();
  void enableLed(bool on);
  void controlLed(uint8_t current);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
ESP8266        |      √       |              |             | 
M0        |      √       |              |             | 


## History

- data 2019-7-31
- version V0.1


## Credits

Written by fengli(li.feng@dfrobot.com), 2019.7.31 (Welcome to our [website](https://www.dfrobot.com/))





