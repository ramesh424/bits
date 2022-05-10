#define BLYNK_PRINT Serial
//#define BLYNK_TEMPLATE_ID "**************"      //Paste your credentials here
//#define BLYNK_DEVICE_NAME "*****************************"  //Paste your credentials here
#define BLYNK_TEMPLATE_ID "TMPLbkXVoNAw"
#define BLYNK_DEVICE_NAME "Heart Beat Monitoring System"
//#define BLYNK_AUTH_TOKEN "6N1vaTu6VYqnmIqa780cAwSZzquEqiWp"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//#include "DHT.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6N1vaTu6VYqnmIqa780cAwSZzquEqiWp";//Paste auth token you copied

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOTlab";///Enter your wifi name
char pass[] = "iotlab@p202";// Enter wifi password
BlynkTimer timer;
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
void sendSensor()
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
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0,BPM); // select your virtual pins accordingly
//    Blynk.virtualWrite(V2, moistvalue); // select your virtual pins accordingly
}  

void setup() {
  Serial.begin(115200);
//  pinMode(15,OUTPUT);
delay(1000);
  Blynk.begin(auth, ssid, pass);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  timer.setInterval(1000L, sendSensor);

}
 
 
void loop()
{
  Blynk.run();
  timer.run();  
}
