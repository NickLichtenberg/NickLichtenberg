import processing.serial.*;
Serial myPort;

PImage logo;

int bgcolor = 0;

 void setup() {
  frameRate(1000);
  colorMode(HSB, 255);
  logo = loadImage("http://arduino.cc/logo.png");
  size (170,116);

  println("availble serial; ports:");
  println(Serial.list());

  myPort = new Serial(this,  Serial.list()[2], 9600);
  }

  void draw() {
    if (myPort.available() > 0) {
      bgcolor = myPort.read();
      println(bgcolor);
    }
      background (bgcolor, 255, 255);
     image (logo, 0, 0);
  }
