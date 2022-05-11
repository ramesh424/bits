#define BLYNK_PRINT Serial
//#define BLYNK_TEMPLATE_ID "**************"      //Paste your credentials here
//#define BLYNK_DEVICE_NAME "*****************************"  //Paste your credentials here
#define BLYNK_TEMPLATE_ID "TMPL5tUQiHze"
#define BLYNK_DEVICE_NAME "Home Security System"
//#define BLYNK_AUTH_TOKEN "5VaxCy8AeaMoEJrI23rAEnoGN0YHuzBj"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "5VaxCy8AeaMoEJrI23rAEnoGN0YHuzBj";//Paste auth token you copied

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOTlab";///Enter your wifi name
char pass[] = "iotlab@p202";// Enter wifi password
BlynkTimer timer;
#define magSW 16
void sendSensor()
{
  int sw_status;
 // char o = 'intrusion alert';
 // char c = 'Door Locked';
  sw_status = digitalRead(magSW);
  if (sw_status)
  {
  Serial.println("Switch open");
  Blynk.virtualWrite(V0,sw_status);
  }
  else
{
  Serial.println("Switch closed");
Blynk.virtualWrite(V0,sw_status);
}
  delay(1000);
  
}


void setup() {
  // put your setup code here, to run once:
pinMode(magSW,INPUT_PULLUP);
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  

}
