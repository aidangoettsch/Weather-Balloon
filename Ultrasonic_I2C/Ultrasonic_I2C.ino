#include <SoftwareSerial.h>
#include <Wire.h>

const int I2C_ADDRESS = 0x40;
const int REGISTER_DURATION = 0x01;
const int REGISTER_TIME = 0x02;

const int US_TRIG = 11;
const int US_ECHO = 12;

uint8_t opcode;
uint8_t duration;
uint8_t readingTime;

SoftwareSerial OpenLog(2, 3);

void setup() {
  Serial.begin(9600);
  OpenLog.begin(9600);

  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   readingTime = millis();
   
   Serial.print("time ");
   Serial.print(readingTime);
   Serial.print(" duration ");
   Serial.print(duration);
   Serial.println();

   OpenLog.print(readingTime);
   OpenLog.print(",");
   OpenLog.print(duration);
   OpenLog.println();
   
   delay(100);
}

void requestEvent() {
  // Read from the register variable to know what to send back
  if (opcode == REGISTER_DURATION) {
    Wire.write((uint8_t *)&duration, sizeof(duration));
  } if (opcode == REGISTER_TIME) {
    Wire.write((uint8_t *)&readingTime, sizeof(readingTime));
  } else {
    Wire.write(0);
  }
}
