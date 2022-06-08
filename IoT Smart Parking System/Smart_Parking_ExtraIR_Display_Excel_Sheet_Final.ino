#include <HardwareSerial.h>
#include <WiFi.h>



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
//defines the I2C pins to which the display is connected
#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(21, 22);




#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

//web hooks 
const char* gate;
const char* parking_lot;


String Event_Name = "parking";

String Key = "gaDU7l3maFw6moAP4BDmWvUD6ccWccS_iD8ePz3TplG";

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
const char* ssid     = "WEP";
const char* password = "wep@p015";



void setup() {
  // Web Hooks 
  Serial.begin(9600);
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  int timeout = 10 * 4; // 10 seconds
  while (WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
  
  myservo.attach(19);  // attaches the servo on pin 13 to the servo object
  //pinMode(36,INPUT);
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  //set the text size, color, cursor position and displayed text
  display.setTextColor(WHITE);
   display.setTextSize(2);
   display.print("Smart Parking");
   display.display();  
}

void loop() {
  int s1=analogRead(36);
  int s2=analogRead(39);
  int s3=analogRead(34);
  int s4=analogRead(33);
  Serial.print("s1=");
  Serial.println(s1);
  Serial.print("s2=");
  Serial.println(s2);
  Serial.print("s3=");
  Serial.println(s3);
   Serial.print("s4=");
  Serial.println(s4);
 
// if(s1==4095 && (s2 == 0 || s3 == 0))
   if(s1 == 4095)
    gate = "Open";
    parking_lot = "-";
// if(s1 == 4095 || s4==4095)
//if(s1 == 4095 || s4 == 4095)
  
   { 
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(500);                       // waits 15ms for the servo to reach the position
//    display.clearDisplay();
//  display.setCursor(0, 5);
//  //Display Gate Open 
//
//  display.print("Gate open");
//  display.display();
//  delay(500);
    
 //   makeIFTTTRequest();
 Serial.println("HIGH");
   }
 
// else if(s1==4095 && s2==4095 && s3==4095)
  if(s1 <= 50 || s4 <= 50)  {
   display.clearDisplay();
   display.setCursor(0, 5);
  //Display Gate close 

  display.print("Gate Open");
  display.display();
    myservo.write(90);
    delay(1000);
  display.clearDisplay(); 
  display.setCursor(0, 5);
  display.print("Gate Close");
  display.display();
    myservo.write(90);
    delay(500);
  display.clearDisplay();
     Serial.println("LOW");
    }

// if(s4 == 4095)
//   { myservo.write(180);              // tell servo to go to position in variable 'pos'
//    delay(500);                       // waits 15ms for the servo to reach the position
  //display.clearDisplay();
 // display.setCursor(0, 5);
  //Display Gate Open 

 // display.print("Gate Close");
 // display.display();
 // delay(500);
  
  
 //  }
 
// else if(s1==4095 && s2==4095 && s3==4095)
// else  {
//    display.clearDisplay();
//    display.setCursor(0, 5);
  //Display Gate close 
 // display.print("Gate open");
 // display.display();
 //   myservo.write(90);
  //  delay(1000);
 //  display.clearDisplay(); 
 //  display.setCursor(0, 5);

 // display.print("Gate Close");
 // display.display();
 //   myservo.write(90);
 //   delay(500);
 // display.clearDisplay();
  //  }
 
    if (s1==4095 && s2 <= 45 && s3 == 4095)
    {
    Serial.println("Parking LOT -1 Occupied"); 
    Serial.println("Parking LOT -2 Free");
      display.clearDisplay();
  display.setCursor(0, 5);
  //Display Gate Open 

  display.print("P1-Occupied,P2-Free");

  display.display();
  delay(500);

  gate = "Open";
    parking_lot = "P1-Occupied,P2-free";
      makeIFTTTRequest();
      }
      else if(s1==4095 && s2 == 4095 && s3 <= 45)
        {
        Serial.println("Parking LOT -1 Free"); 
        Serial.println("Parking LOT -2 Occupied"); 
        display.clearDisplay();
  display.setCursor(0, 5);
  //Display Gate Open 

  display.print("P1-Free,P2-Occupied");

  display.display();
  delay(500);
  gate = "close";
    parking_lot = "P1-Free,P2-Occupied";
      makeIFTTTRequest();
  }
  else if(s1==4095 && s2==4095 && s3==4095)
        {
        Serial.println("All Parking lots are available"); 
            display.clearDisplay();
  display.setCursor(0, 5);
  //Display Gate Open 

  display.print("Parking Lots Free");

  display.display();
  delay(500);
    gate = "Close";
    parking_lot = "P1,P2 Free";
      makeIFTTTRequest();    
  }
   else if(s1==4095 && s2<45 && s3<45)
        {
        Serial.println("Parking Full Move to Next Basement"); 
         display.clearDisplay();
  display.setCursor(0, 5);
  //Display Gate Open 

  display.print("Parking Full");

  display.display();
  delay(500);
   gate = "Close";
    parking_lot = "Parking Lots Full";
      makeIFTTTRequest();     
  }
delay(1000);
display.clearDisplay();
}

void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);

  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") + gate + "\",\"value2\":\"" + parking_lot
                      + "\"}";

  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}
