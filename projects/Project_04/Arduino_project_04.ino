const int greenLEDPin = 9; //set up constants for the pins youre using for input and output
const int redLEDPin = 11;
const int blueLEDPin = 10;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

int redValue = 0; // add variables for the incoming sensor and for the output values
int greenValue = 0; 
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() {
  // begin serial comminucation at 9600bps. you will use this to see the value of the sensors in the serial motor.
  Serial.begin(9600);

  
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}
// reading the value of each light sensor
void loop() {
  
  redSensorValue = analogRead(redSensorPin);

  delay(5);
 
  greenSensorValue = analogRead(greenSensorPin);
  
  delay(5);
  
  blueSensorValue = analogRead(blueSensorPin);
  
  // report the sensor readings to the computer.
  
  Serial.print("raw sensor Values \t red: ");
  Serial.print(redSensorValue);
  Serial.print("\t green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);
  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;

 //report the calculated led levels
  
  Serial.print("Mapped sensor Values \t red: ");
  Serial.print(redValue);
  Serial.print("\t green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

 // set the light levels
 
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}
