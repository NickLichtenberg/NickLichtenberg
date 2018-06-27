#include <LiquidCrystal.h>
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

// Hoe veel tijd kost het voordat de obstakels moeten bewegen
long int interval = 200;
long int gameTime = 0;
long int endTime = 0;
// De vorige tijd dat de obstakels bewogen hebben, in het begin is deze waarde 0
long int previousTime;
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
bool playing = true;
// Een blauwdruk voor objecten, van het Player type (onze speler)
class Player {
  public:
    int x;
    int y; // als speler.jumping true is, dan moet je y - 1 gebruiken als positie van de speler
    bool jumping;
    long int jumpTime;

  Player() {
    x = 0;
    y = 1;
    jumping = false;
  }

  void draw() {
    if(jumping) {
      lcd.setCursor(x, y - 1);
      lcd.write((uint8_t)0);
      lcd.setCursor(x, y);
      lcd.write((uint8_t)2);
    } else {
      lcd.setCursor(x, y);
      lcd.write((uint8_t)0);
      lcd.setCursor(x, y - 1);
      lcd.write((uint8_t)2);
    }
  }

  void update() {
    // Als de speler aan het springen is en al 2 * de interval in de lucht zweeft, dan landen we weer
    if(jumping && (millis() - jumpTime) > (2 * interval)) {
      jumping = false;
    }
  }

  void jump() {
    jumping = true;
    jumpTime = millis();
  }
};

// Een blauwdruk voor objecten, van het Obstacle type (de obstakels)
class Obstacle {
  public:
    int x;
    int y;

  Obstacle() {
    x = 0;
    y = 0;
  }

  void draw() {
    lcd.setCursor(x, y);
    lcd.write((uint8_t)1);
  }

  void update() {
    x -= 1;
    if(x < 0) {
      x = 20;
      y = random(0, 2);
    }
  }
};

byte playerChar[8] = {
  0b00000,
  0b00010,
  0b00011,
  0b11110,
  0b01110,
  0b00000,
  0b00000,
  0b00000
};
byte obstacleChar[8] = {
  0b11111,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b11111
};

byte clearChar[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// Player object, de speler
Player speler;

// Aantal obstakels
const int nObstakels = 5;

// Een array van 5 obstakel objecten maken
Obstacle obstakels[nObstakels];

void setup() {
  Serial.begin(9600);
  
  pinMode(switchPin, INPUT);

  // Maak nieuwe karakters in het karakterset van het scherm, zodat je die met lcd.write((uint8_t)<nummer>) op het scherm kan tonen
  lcd.createChar(0, playerChar);
  lcd.createChar(1, obstacleChar);
  lcd.createChar(2, clearChar);
  lcd.begin(16, 2);

  // De formule voor het berekenen van willekeurige getallen voeren met een willekeurig getal uit analoge poort 5
  randomSeed(analogRead(A5));

  // In elk van de obstakels de randomPosition() methode aanroepen
  for(int i = 0; i < nObstakels; i += 1) {
    obstakels[i].x = 8 + (i * 4);
    obstakels[i].y = random(0, 2);
  }

  gameTime = millis();
}

void loop() { 
  // Hoe veel milliseconden staat de arduino al aan
  long int currentTime = millis();
  if (playing) {
    // Knop afvangen
    switchState = digitalRead(switchPin);
    if(switchState != prevSwitchState) {
      if(switchState == HIGH) {
        // knop ingedrukt, speler springt!
        speler.jump();
        speler.draw();
      }
      
      prevSwitchState = switchState;
    }
  
    // Als de huidige tijd MINUS de vorige tijd groter is dan onze interval van 1000, doe ons ding.
    if((currentTime - previousTime) >= interval) {
      lcd.clear();
  
      // Speler updaten, als hij springt moet hij weer naar beneden
      speler.update();
  
      // Speler tekenen
      speler.draw();
  
      // Alle obstakels van positie updaten en tekenen
      for(int i = 0; i < nObstakels; i += 1) {
        obstakels[i].update();
        obstakels[i].draw();
      } 
  
      // Controleren of speler botst met obstakel door een for loop te maken en voor ELK obstakel 
      // de x en y (obstakels[i].x) vergelijken met speler.x en speler.y. Als deze overeenkomen, dan ben je af.
  
      // We hebben ons ding gedaan, dus nu de huidige tijd opslaan in previousTime voor de volgende keer
      previousTime = currentTime;
    }
      // als de speler een object raakt is die af.
    if (isDead()) {
      playing = false;
      delay(10);
      lcd.setCursor(0,0);
      lcd.write("  Game over!!!  ");
      long int totalTime = (endTime - gameTime) / 1000;
      Serial.print(totalTime);
      lcd.setCursor(0,1);
      lcd.print("    Tijd: " /*+ (totalTime)*/);
      lcd.print(totalTime);
      lcd.print("s");
      
    }
  }
}

bool isDead(){
  for(int i = 0; i < nObstakels; i += 1) {
    int spelerX = speler.x;
    int spelerY = speler.y;
    if(speler.jumping) {
      spelerY -= 1;
    }
    if(obstakels[i].x == spelerX && obstakels[i].y == spelerY) {
      if (endTime == 0) {
        endTime = millis();
      }
      int gameOverBlink = 0;
      for (int j = 0; j < 10; j++) {
        gameOverBlink = !gameOverBlink;
        lcd.setCursor(spelerX, spelerY);
        if (gameOverBlink) {
          lcd.write((uint8_t)0);
        } else {
          lcd.write((uint8_t)1);
        }
        delay(300);
      }
      lcd.clear();
      return true;
    }
  }
  return false;
}

