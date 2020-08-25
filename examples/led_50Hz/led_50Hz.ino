//50HZ
//请将此代码烧录到另一块主控上，在数字10引脚上接上LED灯，为getFlicker.ino提供50HZ的环境光源

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5);
  digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(5);
}