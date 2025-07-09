

#include <Arduino.h>

void printTrigger();

void setup() {
  Serial.begin(115200);
  pinMode(21, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(21), printTrigger, RISING);
}

void printTrigger() {
  Serial.write('1');
}

void loop() {

}