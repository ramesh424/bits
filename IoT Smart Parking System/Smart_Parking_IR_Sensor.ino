#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(21);  // attaches the servo on pin 13 to the servo object
  //pinMode(36,INPUT);
  Serial.begin(9600);
}

void loop() {
  int s1=analogRead(36);
  int s2=analogRead(39);
  int s3=analogRead(34);
  Serial.print("s1=");
  Serial.println(s1);
  Serial.print("s2=");
  Serial.println(s2);
  Serial.print("s3=");
  Serial.println(s3);
 
 if(s1==4095)
   { myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(2000);                       // waits 15ms for the servo to reach the position
   }
 
   else{
    myservo.write(90);
    delay(1000);
    }
    if (s1==4095 && s2 <= 20 && s3 == 4095)
    {
    Serial.println("Parking LOT -1 Occupied"); 
    Serial.println("Parking LOT -2 Free");
      
      }
      else if(s1==4095 && s2 == 4095 && s3 <= 20)
        {
        Serial.println("Parking LOT -1 Free"); 
        Serial.println("Parking LOT -2 Occupied"); 
  }
  else if(s1==4095 && s2==4095 && s3==4095)
        {
        Serial.println("All Parking lots are available"); 
       
  }
   else if(s1==4095 && s2<20 && s3<20)
        {
        Serial.println("Parking Full Move to Next Basement"); 
       
  }
}
