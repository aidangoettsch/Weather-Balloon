#include <Wire.h>

const int I2C_ADDRESS = 0x40;
const int REGISTER_DURATION = 0x01;
const int REGISTER_TIME = 0x02;

const int US_TRIG = 11;
const int US_ECHO = 12;

uint8_t opcode;
uint8_t duration;
uint8_t readingTime;

void setup() {
  Serial.begin(9600);

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
   pinMode(US_TRIG, OUTPUT);
   digitalWrite(US_TRIG, LOW);
   delayMicroseconds(2);
   digitalWrite(US_TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(US_TRIG, LOW);
   pinMode(US_ECHO, INPUT);
   duration = pulseIn(US_ECHO, HIGH);
   readingTime = millis();
   
   Serial.print("time ");
   Serial.print(readingTime);
   Serial.print(" duration ");
   Serial.print(duration);
   Serial.println();
   
   delay(100);
}

void receiveEvent(int howMany) {
  if (Wire.available() == 1) opcode = Wire.read();
}

void requestEvent() {
  // Read from the register variable to know what to send back
  Serial.println(opcode == REGISTER_DURATION);
  if (opcode == REGISTER_DURATION) {
    uint8_t * send = (uint8_t *) &duration;
    Serial.println(*send);
    int size = sizeof(duration);
    Wire.write(send, size);
  } if (opcode == REGISTER_TIME) {
    Serial.println(readingTime);
    Wire.write((uint8_t *) &readingTime, sizeof(readingTime));
  } else {
    Wire.write(0);
  }
}
