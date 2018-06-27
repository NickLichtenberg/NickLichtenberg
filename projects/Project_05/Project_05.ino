
#include <Servo.h>

Servo myServo;  // Maakt een servo object

int const potPin = A0; //Maakt een variable aan
int potVal; 
int angle;   

  // stuurt van poort 9 9600 bytes naar de servo motor
void setup() {
  myServo.attach(9); 
  Serial.begin(9600); 
}
// leest de analoog input 
void loop() {
  potVal = analogRead(potPin); 

  Serial.print("potVal: ");
  Serial.print(potVal);

  angle = map(potVal, 0, 1023, 0, 179);
  // hij print het naar de serial motor
  Serial.print(", angle: ");
  Serial.println(angle);

  myServo.write(angle);

  delay(15);
}
