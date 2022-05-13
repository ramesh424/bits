 /*Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLEPRlNqAS"
#define BLYNK_DEVICE_NAME "IoT based Home appliance Control"
#define BLYNK_AUTH_TOKEN "ikELHK-tZHtUBIrPPm4hEWHDQvBJ0tBE"



#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "ikELHK-tZHtUBIrPPm4hEWHDQvBJ0tBE";//Paste auth token you copied


char ssid[] = "IOTlab";///Enter your wifi name
char pass[] = "iotlab@p202";// Enter wifi password

BlynkTimer timer;

BLYNK_WRITE(V0)
{
  int relay1 = param.asInt();
  digitalWrite(19,relay1);
  }
  BLYNK_WRITE(V1)
{
  int realy2 = param.asInt();
  digitalWrite(21,realy2);
  }
   BLYNK_WRITE(V2)
{
  int realy3 = param.asInt();
  digitalWrite(22,realy3);
  }
   BLYNK_WRITE(V3)
{
  int realy4 = param.asInt();
  digitalWrite(23,realy4);
  }


void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(19,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
delay(1000);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
} 
