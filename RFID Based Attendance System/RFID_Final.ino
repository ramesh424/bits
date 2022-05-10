#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Wire.h>
#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(21, 22);

// Instantiate an object for the OLED screen

#define SS_PIN 5
#define RST_PIN 27

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader...");
   display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  //set the text size, color, cursor position and displayed text
  display.setTextColor(WHITE);
  display.setTextSize(1.5);
  display.setCursor(0, 0);
 //display.println("Hello World!");
 display.display();
}

void loop() {
  
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
    Serial.println("Sravan Kumar");
    display.setCursor(2, 2);
    display.clearDisplay();
    display.println("Sravan Kumar");
    display.display();
    Serial.println();
    delay(1000);
  }

  else if(content.substring(1) == "AA 29 9A 19"){
    Serial.println("S. Samreen");
    display.setCursor(2, 0);
    display.clearDisplay();
    display.println("S. Samreen");
    display.display();
    Serial.println();
    delay(1000);
  }
else if(content.substring(1) == "79 D0 24 A3"){
    Serial.println("Ganesh");
    Serial.println();
    display.setCursor(2, 0);
    display.clearDisplay();
    display.println("Ganesh");
    display.display();
    
    delay(1000);
  }
  else if(content.substring(1) == "79 D0 24 A3"){
    Serial.println("Sohail");
    Serial.println();
     display.setCursor(2, 2);
    display.clearDisplay();
    display.println("Sohil");
    display.display();
    delay(1000);
  }
  else{
    Serial.println("Ramesh");
     display.setCursor(2, 2);
    display.clearDisplay();
    display.println("Ramesh");
    display.display();
    delay(1000);
  }

}
