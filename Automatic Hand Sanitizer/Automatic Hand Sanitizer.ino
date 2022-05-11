#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
//defines the I2C pins to which the display is connected
#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(21, 22);
const int trigPin = 5;
const int echoPin = 18;
const int Relay=23;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
int distanceCm;
int distanceInch;
void setup()   {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(Relay, OUTPUT);
  //define the type of display used and the I2C address
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  //set the text size, color, cursor position and displayed text
  display.setTextColor(WHITE);
   display.setTextSize(2);
  //display.setCursor(0, 0);
 // display.println("Hello World!");
 // display.display();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
//  Serial.print("Distance (cm): ");
//  Serial.println(distanceCm);
//  Serial.print("Distance (inch): ");
//  Serial.println(distanceInch);
    display.clearDisplay(); 
    display.setCursor(0,0);
    delay(1000);
    display.print("Place Your Hand for Sanitizer");
    display.display();
     delay(1000);
  display.clearDisplay();
//  display.setCursor(0, 5);
//  //Display distance in cm
//  display.print(distanceCm);
//  display.print(" cm");
  
  // Display distance in inches
  /* display.print(distanceInch);
  display.print(" in");*/
  display.display(); 

  delay(500); 
  if (distanceCm <10)
  {
    digitalWrite(Relay,HIGH);
    delay(2000);
    digitalWrite(Relay,LOW);
    display.clearDisplay(); 
    display.setCursor(0,0);
    display.print("Remove    Your Hand");
    display.display();
    delay(5000);
    
    display.clearDisplay(); 
    display.setCursor(0,0);
    display.print("Remove Your Hand");
    display.display();
    delay(1000);
    } 
    else
    digitalWrite(Relay,LOW);
}
