#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

// Instantiate an object for the OLED screen
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Instantiate an object for the sensor
// SCL -> GPIO22 (D1 on a D1 Mini)
// SDA -> GPIO21 (D2 on a D1 Mini)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  Serial.println("MLX90614 Test");
  
  // Initialize the screen
  u8g2.setBusClock(100000);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  // Initialize the sensor
  if(!mlx.begin()) {
    Serial.println("Failed to initialize MLX90614");
    while(1);
  }
}

void loop() {
  // Declare variables for storing the sensor data
  double temp_obj, temp_amb;
  // Get the sensor data
  Serial.print("Reading a measurement...");
  temp_amb = mlx.readAmbientTempF(); //temperature of the sensor itself
  temp_obj = mlx.readObjectTempF();  //temperature of what it's measuring in the 90-degree field of view
  Serial.print("Ambient = "); 
  Serial.print(temp_amb); 
  Serial.print("*F\tObject = "); 
  Serial.print(temp_obj); Serial.println("*F");

  String output = String(temp_amb) + " *F";
  // Make sure the screen is clear
  u8g2.clearBuffer();
  // Display a header
  u8g2.drawStr(4,10,"Ambient:");
  // Display the data
  u8g2.drawStr(4,20,output.c_str());




  
  // Display a header
  u8g2.drawStr(4,30,"Object:");
  output = String(temp_obj) + " *F";  
  // Display the data
  u8g2.drawStr(4,40,output.c_str());  
  u8g2.sendBuffer();

  // Wait a bit before the next measurement
  delay(500);
}
