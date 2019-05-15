#include <Wire.h>

const int I2C_ADDRESS = 0x40;
const int REGISTER_VALUE = 0x01;

uint8_t opcode;
uint8_t value;

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
}

void receiveEvent(int bytes) {
  // Read the first byte to determine which register is concerned
  opcode = Wire.read();

  // If there are more than 1 byte, then the master is writing to the slave
  if (bytes > 1) {
    if (opcode == REGISTER_VALUE) {
      value = Wire.read();
    }
  }
}

void requestEvent() {
  // Read from the register variable to know what to send back
  if (opcode == REGISTER_VALUE) {
    Wire.write((uint8_t *)&value, sizeof(value));
  } else {
    Wire.write(0);
  }
}
