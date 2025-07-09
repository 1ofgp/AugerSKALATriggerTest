#include <Arduino.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

#define NOP __asm__ ("nop\n\t")
#define NOP5 __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\t")
#define NOP10 __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t")

#define TAXI_EXT_TRIGGER  33
#define LOW_PIN_0         28
#define LOW_PIN_1         32
#define HIGH_PIN          30
#define TX_ON_PIN         29
#define TFT_ON_PIN        31
#define TRIGGER_LED_PIN   2
#define TFT_SCLK          13  // SCLK can also use pin 14
#define TFT_MOSI          11  // MOSI can also use pin 7
#define TFT_CS            10  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC            9  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST           8  // RST can use any pin
#define SD_CS             6  // CS for SD card, can use any pin

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

const int timeY = 10;
const int triggerY = 50;
const int frequencyY = 90;
const int TxStatusY = 140;
const int headerX = 5;
const int valueX = 120;
const int headerOffsetY = 2;
const int tftOffy = 70;

int count = 0;
String TX_status; 
uint32_t timeStart, timeElapsed, timeForTFT, timeForTFTStart;
float frequency;
boolean tftOn = false;

void printTrigger();
void generateTrigger(); 
void checkTx();
void drawfastlines(uint16_t color1, uint16_t color2);
void drawStart();
void drawTxStatus();
void drawHeaders();
void drawTime();
void drawTrigger();
void drawFrequency();
void drawTFTOff();

void setup() {
  
  pinMode(LOW_PIN_0, OUTPUT);
  digitalWrite(LOW_PIN_0, LOW);
  pinMode(LOW_PIN_1, OUTPUT);
  digitalWrite(LOW_PIN_1, LOW);
  pinMode(HIGH_PIN, OUTPUT);
  digitalWrite(HIGH_PIN, HIGH);
  pinMode(21, INPUT_PULLDOWN);
  pinMode(26, INPUT_PULLDOWN);
  pinMode(TRIGGER_LED_PIN, OUTPUT);
  
  Serial.begin(115200);

  pinMode(TAXI_EXT_TRIGGER, OUTPUT);
  pinMode(TX_ON_PIN, INPUT);
  pinMode(TFT_ON_PIN, INPUT);


  tft.init(172, 320);           // Init ST7789 172x320
  tft.setRotation(3);

  drawfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);
  drawStart();
  delay(2000);

  if (digitalRead(TFT_ON_PIN)){
    tftOn = true;
    drawHeaders();
  } 

  else{
    tftOn = false;
    drawTFTOff();
  }
 
  checkTx();
  drawTxStatus();
  attachInterrupt(digitalPinToInterrupt(21), printTrigger, RISING);
  attachInterrupt(digitalPinToInterrupt(26), printTrigger, RISING);
  timeStart = millis();
  timeForTFTStart = millis();

  count = 0;

}



void loop() {
  checkTx();
  //drawTxStatus();
  timeElapsed = millis() - timeStart;
  timeForTFT = millis() - timeForTFTStart;
 
 
}


void printTrigger() {
  digitalWriteFast(TRIGGER_LED_PIN, HIGH);
  Serial.write('1'); // for doTimestamps.py 
  count ++;
  delay(1);
  digitalWriteFast(TRIGGER_LED_PIN, LOW);

  if ((timeForTFT > 2000) and (tftOn)){
    drawHeaders();
    drawTime();
    drawTrigger();
    drawFrequency();
    drawTxStatus();
    timeForTFT = 0;
    timeForTFTStart = millis();
  }
}

void generateTrigger() {

  // put your main code here, to run repeatedly:
  int period = random(2, 20); // period in miliseconds, can be constant
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

void checkTx(){
  if (digitalRead(TX_ON_PIN))
  {
    generateTrigger();
    TX_status = "TX ON";
  }
  else TX_status = "TX OFF";
 
  drawTxStatus();

}

void drawfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void drawStart(){
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(4);
  tft.setCursor(35, 40);
  tft.print("Auger SKALA"); 
  tft.setCursor(25, 100);
  tft.print("Trigger Test");
}

 void drawTxStatus(){
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(4);
  tft.setCursor(headerX, TxStatusY);
  tft.print(TX_status);
 }

 void drawHeaders(){
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(3);
  tft.setCursor(headerX, timeY + headerOffsetY);
  tft.print("t[s] :");
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(3);
  tft.setCursor(headerX,triggerY + headerOffsetY);
  tft.print("Trig :");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(3);
  tft.setCursor(headerX, frequencyY + headerOffsetY);
  tft.print("f[Hz]:");
 }

 void drawTime(){
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.setCursor(valueX, timeY);
  tft.print(float(timeElapsed/1000.0));
 }

 void drawTrigger(){
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(4);
  tft.setCursor(valueX, triggerY);
  tft.print(count);
 }

 void drawFrequency(){
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(4);
  tft.setCursor(valueX, frequencyY);
  frequency = float(count/(timeElapsed/1000.0));
  tft.print(frequency);
 }

 void drawTFTOff(){
   tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(4);
  tft.setCursor(headerX +30, tftOffy);
  tft.print("Screen OFF");
 }