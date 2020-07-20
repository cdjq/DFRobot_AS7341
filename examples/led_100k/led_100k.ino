//100HZ

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5);
  digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(5);
}