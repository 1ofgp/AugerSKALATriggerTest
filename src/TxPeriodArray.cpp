
#include <Arduino.h>

#define NOP __asm__ ("nop\n\t")
#define NOP5 __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\t")
#define NOP10 __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t")

#define TAXI_EXT_TRIGGER  13

#include "periodUUB_10min.c"

int i;
int eventsNb = sizeof(periodArray)/sizeof(int);
void setup() {
  // put your setup code here, to run once:
  pinMode(TAXI_EXT_TRIGGER, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  //int period = 500; //random(2, 20);

  
  for (i = 0; i< eventsNb; i ++){
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
  delayMicroseconds(periodArray[i]);

  // Serial.println(eventsNb);
  // Serial.print(i); 
  // Serial.print(": "); 
  // Serial.println(periodArray[i]);
  }

  while (true)
  {
    delay(1000);
  }
  
}
