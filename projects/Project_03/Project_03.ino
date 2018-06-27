const int sensorPin = A0; // Var aan de sensor geven
const float baselineTemp = 25.0;

void setup() {
  Serial.begin(9600); // stuur 9600 bits van ardiuno naar computer

  for(int pinNumber = 2; pinNumber<5; pinNumber++){ // een loop door pinNumber 2 tm 4
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW); // zet het lampje met de bijbehorende pinNumber uit
  }

}

void loop() {
  int sensorVal = analogRead(sensorPin);
  
  // zet text op de computer neer met de waarde van de hittesensor
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  float voltage = (sensorVal/1024.0) * 5.0; // de hitte omzetten in een aantal volts
  
  // weergeven op computer hoeveel volt
  Serial.print(", Volts: ");
  Serial.print(voltage);
  
  // aantal graden berekenen en weergeven in computer
  Serial.print(", degrees C: ");
  float temperature = (voltage - .5) * 100;
  Serial.print(temperature);
// als temperatuur lager is dan de van tevoren baslineTemp graden gaat er geen lampje branden
  if(temperature < baselineTemp){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if(temperature >= baselineTemp+2 && temperature < baselineTemp+4){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if(temperature >= baselineTemp+4 && temperature < baselineTemp+6){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if(temperature >= baselineTemp+6){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(1);
}
