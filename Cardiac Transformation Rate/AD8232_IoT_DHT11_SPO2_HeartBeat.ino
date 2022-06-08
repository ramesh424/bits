#include <Wire.h>
#include "MAX30100_PulseOximeter.h"




#include <WiFi.h>
#include <PubSubClient.h>
 
#include "DHT.h"

#define REPORTING_PERIOD_MS     1000

#define WIFISSID "WEP" // Put your WifiSSID here
#define PASSWORD "wep@p015" // Put your wifi password here
#define TOKEN "BBFF-nNchyAXUJLve69VahV5IGpB9e65aVA" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "zabeen" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices
 
/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL "sensor" // Assing the variable label
#define VARIABLE_LABEL1 "temperature"
#define VARIABLE_LABEL2 "humidity"
#define VARIABLE_LABEL3 "HeartBeat"
#define VARIABLE_LABEL4 "sp02"
#define DEVICE_LABEL "esp32" // Assig the device label
 
#define SENSOR A0 // Set the A0 as SENSOR


#define DHTPIN 13         // What digital pin we're connected to select yours accordingly

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char topic1[150];
char topic2[150];
char topic3[150];
char topic4[150];
// Space to store values to send
char str_sensor[10];
char str_h[10]; 
char str_t[10];
char str_hb[10];
char str_s[10];
/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);
 
void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.write(payload, length);
  Serial.println(topic);
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

PulseOximeter pox;

uint32_t tsLastReport = 0;
void onBeatDetected()
{
    Serial.println("Beat!");
}
/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
  pinMode(SENSOR, INPUT);
 
  Serial.println();
  Serial.print("Waiting for WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);  

if (!pox.begin()) {
        Serial.println("FAILED");
  //      for(;;);
    } else {
        Serial.println("SUCCESS");
    }
}
 
void loop() {
  if (!client.connected()) {
    reconnect();
  }
 
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
  
  float sensor = analogRead(SENSOR); 
   
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  
  DHT dht(DHTPIN, DHTTYPE);
   float h = dht.readHumidity();
  float t = dht.readTemperature();
  dtostrf(h,4,2,str_h);
  dtostrf(t,4,2,str_t);

  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
// Temperature and Humidity 

sprintf(topic1, "%s", ""); // Cleans the topic content
  sprintf(topic1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload content
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1); // Adds the variable label
  sprintf(payload, "%s {\"value\": %s", payload,  str_t); // Adds the value
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic1, payload);
 // Humidity 
  sprintf(topic2, "%s", ""); // Cleans the topic content
  sprintf(topic2, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

  sprintf(payload, "%s", ""); // Cleans the payload content
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL2); // Adds the variable label
  sprintf(payload, "%s {\"value\": %s", payload,  str_h); // Adds the value
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

  client.publish(topic2, payload);

pox.update();
    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
        tsLastReport = millis();
    
    
float hb = pox.getHeartRate();
float s = pox.getSpO2();
dtostrf(hb,4,2,str_hb);
dtostrf(s,4,2,str_s);


// Heart Beat
 sprintf(topic1, "%s", ""); // Cleans the topic content
  sprintf(topic1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload content
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL3); // Adds the variable label
  sprintf(payload, "%s {\"value\": %s", payload,  str_hb); // Adds the value
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic3, payload);

// sp02

 sprintf(topic1, "%s", ""); // Cleans the topic content
  sprintf(topic1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload content
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL4); // Adds the variable label
  sprintf(payload, "%s {\"value\": %s", payload,  str_s); // Adds the value
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic4, payload);
}
  client.loop();
  delay(500);
 
}
