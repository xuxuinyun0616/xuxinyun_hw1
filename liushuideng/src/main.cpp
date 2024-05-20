#include <Arduino.h>

uint8_t Pin[6] = {A2,A3,A4,A5,A0,A1};

void setup() {
  for(int i = 0;i<6;i++)
    pinMode(Pin[i],OUTPUT);
 digitalWrite(A6,HIGH);
}

void loop() {
 for(int i=0;i<6;i++)
 {
    digitalWrite(Pin[i],HIGH);
    delay(500);
    digitalWrite(Pin[i],LOW);
 }
 for(int i=5;i>=0;i--)
 {
  digitalWrite(Pin[i],HIGH);
  delay(500);
  digitalWrite(Pin[i],LOW);
 }
}
