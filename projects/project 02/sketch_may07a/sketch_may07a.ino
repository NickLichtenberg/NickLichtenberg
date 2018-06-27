int switchState = 0;

void setup (){
    pinMode (3,OUTPUT);
    pinMode (4,OUTPUT);
    pinMode (5,OUTPUT);
    pinMode (2,INPUT);
}

void loop (){
  switchState = digitalRead (2);
  
  if (switchState == LOW) {
  
    digitalWrite(3, HIGH); // groene led
    digitalWrite(4,LOW); // rode led
    digitalWrite(5,LOW); // rode led
  } else { // als het knopje ingedrukt is
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    
    delay (250); // led 4 gaat aan en led 5 gaat de led uit.
    digitalWrite (4,HIGH);
    digitalWrite (5,LOW);
    delay (250);
  }
}

