#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>           //https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h>       //https://github.com/adafruit/Adafruit_SSD1306
#include <SPI.h>
#include <Wire.h>

//RFID
#include <SPI.h>
#include <MFRC522.h>

// 
#define SS_PIN 5
#define RST_PIN 27

MFRC522 mfrc522(SS_PIN, RST_PIN);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// Icon of Fingerprint
#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
static const unsigned char PROGMEM logo_bmp[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x83, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x03, 0xff, 0xc0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0xff, 0xf8, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xff, 0xff, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe1, 0xff, 0x00, 0xff, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc7, 0xf0, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x8f, 0xc0, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x03, 0xff, 0xc1, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x0f, 0xff, 0xf0, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3f, 0xff, 0xfc, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xf8, 0x00, 0x1f, 0x8f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe3, 0xf0, 0x18, 0x0f, 0xc7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc7, 0xc1, 0xff, 0x83, 0xe3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc7, 0x87, 0xff, 0xe1, 0xf1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x8f, 0x1f, 0xff, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x1e, 0x3f, 0x01, 0xf8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x1e, 0x7e, 0x00, 0x7c, 0x79, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x3e, 0x3d, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xf0, 0xff, 0x1f, 0x3d, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xe1, 0xff, 0x8f, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xff, 0xc7, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe3, 0xc7, 0xc3, 0xc7, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xe3, 0x8f, 0x01, 0xe7, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xc7, 0x8f, 0x00, 0xe3, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x9e, 0x18, 0xf3, 0x9e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0x1e, 0x38, 0xf3, 0x9e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x3c, 0x38, 0xf3, 0x9e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x78, 0xf7, 0x9c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x78, 0x78, 0xe7, 0x9c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf0, 0xf1, 0xe7, 0x9c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xe1, 0xf1, 0xe1, 0xe7, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xc3, 0xe3, 0xe3, 0xc7, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x87, 0xc3, 0xc3, 0xcf, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x87, 0x87, 0x8f, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x0f, 0x0f, 0x8f, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x1f, 0x1f, 0x0f, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3e, 0x1e, 0x0f, 0x3d, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x7c, 0x3c, 0xcf, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0xf8, 0x79, 0xcf, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xc1, 0xf0, 0xf9, 0xcf, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x07, 0xe1, 0xf1, 0xc7, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0xc3, 0xe3, 0xc7, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x07, 0xc3, 0xc7, 0x87, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x1f, 0x83, 0xc3, 0xc3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3e, 0x01, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x7c, 0x01, 0xc1, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf8, 0x01, 0xe0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc3, 0xf3, 0xf8, 0xf0, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe7, 0xfc, 0xf8, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xcf, 0xfe, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x1e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3e, 0x0f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
const char* NAME;
const char* ID;


String Event_Name = "fingerprint";

String Key = "b5Db42gn0LDLLml_I89Nbmxy7Sv2wl_3GwtXwz6Oi-u";

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
const char* ssid     = "WEP";
const char* password = "wep@p015";

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
// RFID BEGIN
  SPI.begin();
  mfrc522.PCD_Init();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  display.clearDisplay();
 display.drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
 display.display();
  Serial.println("\n\nAdafruit finger detect test");
  delay(1000);
 display.clearDisplay();
 
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(25, 0);            // Start at top-left corner
   display.println(("Sensor"));
   display.setCursor(5, 35);
   display.println("Connected");
   display.display();
   delay(3000); 
  } else {
    display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(25, 0);            // Start at top-left corner
   display.println(("Sensor"));
   display.setCursor(5, 35);
   display.println("Not Found");
   display.display();
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }

  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");

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
 display.clearDisplay();
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
display.clearDisplay();
display.drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
display.display();
  if (finger.fingerID == 1) {
    display.clearDisplay();
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "M.Sravan Kumar";
    ID = "182K1A0415";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      // digital write - open the door
      display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("M. Sravan Kumar"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Atendance"));
   display.setCursor(20, 40);
   display.println("marked");
   display.display();
   delay(1000);
   
    }
display.clearDisplay();
  }

  if (finger.fingerID == 2) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "S. Samreen";
    ID = "182k1A0422";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("S. Samreen"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Atendance"));
   display.setCursor(20, 40);
   display.println("marked");
   display.display();
   delay(1000);
      // digital write - open the door
    }      //don't ned to run this at full speed.

  }

//  3rd finger print 
if (finger.fingerID == 3) {
    display.clearDisplay();
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "E. Ganesh Goud";
    ID = "182K1A0404";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      // digital write - open the door
      display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("E. Ganesh Goud"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Atendance"));
   display.setCursor(20, 40);
   display.println("marked");
   display.display();
   delay(1000);
   
    }
display.clearDisplay();
  }
// 4th Finger Print 
if (finger.fingerID == 4) {
    display.clearDisplay();
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "S. Sohail";
    ID = "182K1A0424";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      // digital write - open the door
      display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("S.Sohail"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Atendance"));
   display.setCursor(20, 40);
   display.println("marked");
   display.display();
   delay(1000);
   
    }
display.clearDisplay();
  }
// Fifth finger print 
if (finger.fingerID == 5) {
    display.clearDisplay();
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "S. Khader Vali";
    ID = "Faculty-1";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      // digital write - open the door
      display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("S. Khader Vali Sir"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Atendance"));
   display.setCursor(20, 40);
   display.println("marked");
   display.display();
   delay(1000);
   
    }
display.clearDisplay();
}
if (finger.fingerID == 6) {
    display.clearDisplay();
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Ravi Shankar Sir";
    ID = "HOD";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      // digital write - open the door
      display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("Ravi Shankar Sir"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Atendance"));
   display.setCursor(20, 40);
   display.println("marked");
   display.display();
   delay(1000);
   
    }

display.clearDisplay();
  }

  finger.fingerID = 0;
//  display.clearDisplay();
//   display.setTextSize(2);             // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE);        // Draw white text
//   display.setCursor(40, 0);            // Start at top-left corner
//   display.println(("Place "));
//   display.setCursor(15, 20);            // Start at top-left corner
//   display.println(("Your"));
//   display.setCursor(20, 40);
//   display.println("Finger");
//   display.display();
//   delay(1000);
//   display.clearDisplay();
if( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag :");
  String content = "";
  byte letter;

  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  //Serial.print("Name : ");
  //display.println("Name : ");
  display.display();
  content.toUpperCase();

  if(content.substring(1) == "7A 3A 95 19"){
     NAME = "M.Sravan kumar";
    ID = "182k1A0415";
    makeIFTTTRequest();
    Serial.println("M.Sravan kumar");
    display.setCursor(2, 2);
    display.clearDisplay();
    display.println("M.Sravan kumar-182k1A0415");
    display.display();
    Serial.println();
    delay(1000);
  }

  else if(content.substring(1) == "AA 29 9A 19"){
    NAME = "S. Samreen";
    ID = "182k1A0422";
    makeIFTTTRequest();
    Serial.println("Prashanth");
    display.setCursor(2, 0);
    display.clearDisplay();
    display.println("S. Samreen - 182k1A0422 ");
    display.display();
    Serial.println();
    delay(1000);
  }
else if(content.substring(1) == "7A 6D A6 1A"){
    NAME = "E.Ganesh Goud";
    ID = "182k1A0404";
    makeIFTTTRequest();
    Serial.println("E.Ganesh Goud");
    Serial.println();
    display.setCursor(2, 0);
    display.clearDisplay();
    display.println("E.Ganesh goud-182k1A0404");
    display.display();
    
    delay(1000);
  }
  else if(content.substring(1) == "FA D2 9C 1A"){
    NAME = "S.Sohail";
    ID = "182K1A0424";
    makeIFTTTRequest();
    Serial.println("S.Sohail-182K1A0424");
    Serial.println();
     display.setCursor(2, 2);
    display.clearDisplay();
    display.println("S.Sohail-182K1A0424");
    display.display();
    delay(1000);
  }
 else if(content.substring(1) == "2A 1D A5 1A"){
    NAME = "S.Khader vali";
    ID = "Faculty-1";
    makeIFTTTRequest();
    Serial.println("S. Khader Vali");
     display.setCursor(2, 2);
    display.clearDisplay();
    display.println("S. Khader Vali  - Faculty-1");
    display.display();
    delay(1000);
  }
else if(content.substring(1) == "BA D7 AE 1A"){
    NAME = "Ravi Shankar Sir ";
    ID = "HOD";
    makeIFTTTRequest();
    Serial.println("Ravi Shankar Sir");
     display.setCursor(2, 2);
    display.clearDisplay();
    display.println("Ravi Shankar -- HOD");
    display.display();
    delay(1000);
  }


}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
     display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(20, 0);            // Start at top-left corner
   display.println(("Invalid"));
   display.setCursor(25, 20);
   display.println("Finger");
   display.setCursor(10, 40);
   display.println("Try Again");
   display.display();
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  display.clearDisplay();

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

// Make an HTTP request to the IFTTT web service
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
  String jsonObject = String("{\"value1\":\"") + NAME + "\",\"value2\":\"" + ID
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
