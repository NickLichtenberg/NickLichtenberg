int sensorValue; // maakt variablen aan
int sensorLow = 1023;
int sensorHigh = 0;
const int ledPin = 13;

void setup() {
// De maakt van de led een output en zet de led aan
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

// kalibreert de eerste vijf seconden nadat het programma is uitgevoerd
  while (millis() < 5000) {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    } 
    // vergelijkt de waarde voor kalibratie
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  // schakel de LED uit, wat het einde van de kalibratieperiode aangeeft
  digitalWrite(ledPin, LOW);
}
// in de loop leest de waarde 
void loop() {
  sensorValue = analogRead(A0);

  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

  tone(8, pitch, 20);

  delay(10);
}
