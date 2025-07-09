
#include <Arduino.h>

#define NOP __asm__ ("nop\n\t")
#define NOP5 __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\t")
#define NOP10 __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t")

#define TAXI_EXT_TRIGGER  13
void setup() {
  // put your setup code here, to run once:
  pinMode(TAXI_EXT_TRIGGER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int period = random(2, 20);
  digitalWriteFast(TAXI_EXT_TRIGGER, HIGH);
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  NOP10;
  digitalWriteFast(TAXI_EXT_TRIGGER, LOW);
  delay(period);
}
