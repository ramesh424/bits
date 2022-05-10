#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
//defines the I2C pins to which the display is connected
#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(21, 22);


 
int x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
 
#define UpperThreshold 2000
#define LowerThreshold 500
 
void setup() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
}
 
 
void loop()
{
  if(x>127)  
  {
    display.clearDisplay();
    x=0;
    lastx=x;
  }
 
  int value=analogRead(36);
  display.setTextColor(WHITE);
  int y=60-(value/16);
  display.writeLine(lastx,lasty,x,y,WHITE);
  lasty=y;
  lastx=x;
  // calc bpm
 
  if(value>UpperThreshold)
  {
    if(BeatComplete)
    {
      BPM=millis()-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  if((value<LowerThreshold)&(BPMTiming))
    BeatComplete=true;
    // display bpm
  display.writeFillRect(0,50,128,16,BLACK);
  display.setCursor(0,50);
  display.print(BPM);
  display.print(" BPM");
  display.display();
  x++;
}

--
