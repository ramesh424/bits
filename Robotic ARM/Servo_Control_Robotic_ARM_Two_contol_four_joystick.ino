#include <Servo.h>
#define SERVO_PIN1 8
#define SERVO_PIN2 9         
#define XJOY_PIN A0                  //X axis reading from joystick will go into analog pin A1           
#define YJOY_PIN A1                  //X axis reading from joystick will go into analog pin A1
#define SERVO_PIN3 10
#define SERVO_PIN4 11         
#define XJOY_PIN A0                  //X axis reading from joystick will go into analog pin A1           
#define YJOY_PIN A1 
#define ZJOY_PIN A2                  //X axis reading from joystick will go into analog pin A1           
#define AJOY_PIN A3
Servo myservo1 ;
Servo myservo2 ;
Servo myservo3 ;
Servo myservo4 ;
void setup()
{
  //Servo 1
 Serial.begin(9600);
 myservo1.attach(8); 
 //Servo 2
 myservo2.attach(9);
  myservo3.attach(10); 
 //Servo 2
 myservo4.attach(11);
}
 
void loop()
{
 delay(200);                    
 int joystickXVal = analogRead(XJOY_PIN) ;  //read joystick input on pin A1
 Serial.print(joystickXVal);                //print the value from A1
 Serial.println(" = input from joystick_1");  //print "=input from joystick" next to the value
 Serial.print((joystickXVal+520)/10);       //print a from A1 calculated, scaled value
 Serial.println(" = output to servo");      //print "=output to servo" next to the value
 Serial.println() ;
 myservo1.write((joystickXVal+520)/10);      //write the calculated value to the servo  
delay(200); 
 int joystickYVal = analogRead(YJOY_PIN) ;  //read joystick input on pin A1
 Serial.print(joystickYVal);                //print the value from A1
 Serial.println(" = input from joystick_2");  //print "=input from joystick" next to the value
 Serial.print((joystickYVal+520)/10);       //print a from A1 calculated, scaled value
 Serial.println(" = output to servo");      //print "=output to servo" next to the value
 Serial.println() ;
  myservo2.write((joystickYVal+520)/10);
 delay(200);
      //write the calculated value to the servo 
 int joystickZVal = analogRead(ZJOY_PIN) ;  //read joystick input on pin A1
 Serial.print(joystickZVal);                //print the value from A1
 Serial.println(" = input from joystick_3");  //print "=input from joystick" next to the value
 Serial.print((joystickZVal+520)/10);       //print a from A1 calculated, scaled value
 Serial.println(" = output to servo");      //print "=output to servo" next to the value
 Serial.println() ;
 myservo3.write((joystickZVal+520)/10);      //write the calculated value to the servo 
 delay(200);
      //write the calculated value to the servo 
 int joystickAVal = analogRead(AJOY_PIN) ;  //read joystick input on pin A1
 Serial.print(joystickAVal);                //print the value from A1
 Serial.println(" = input from joystick_4");  //print "=input from joystick" next to the value
 Serial.print((joystickAVal+520)/10);       //print a from A1 calculated, scaled value
 Serial.println(" = output to servo");      //print "=output to servo" next to the value
 Serial.println() ;
 myservo4.write((joystickAVal+520)/10);      //write the calculated value to the servo 
}
