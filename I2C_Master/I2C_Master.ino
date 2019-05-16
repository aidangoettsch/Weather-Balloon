#include <Wire.h>

const int US_I2C_ADDRESS = 0x40;
const int US_REGISTER_DURATION = 0x01;
const int US_REGISTER_TIME = 0x02;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  readByte(US_I2C_ADDRESS, US_REGISTER_DURATION);
  delay(1000);
}

uint8_t readByte(int i2cAddress, uint8_t read_register) {
  Wire.beginTransmission(i2cAddress); // transmit to device #112
  Wire.write(read_register);      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(i2cAddress, 1);    

  // step 5: receive reading from sensor
  if (1 <= Wire.available()) { // if two bytes were received
    Serial.print("hmm ");
    int avail = Wire.available();
    Serial.print("avail");
    Serial.print(" ");
    uint8_t val = Wire.read();
    Serial.println(val);
  }
}
