#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 2);    // request 2 bytes from slave device #8

  if(Wire.available() >= 2) {
    bool boolValue = Wire.read(); // receive a byte as boolean
    Serial.print("Boolean value: ");
    Serial.println(boolValue);

    int intValue = Wire.read(); // receive a byte as integer
    Serial.print("Integer value: ");
    Serial.println(intValue);
  }

  delay(500);
}