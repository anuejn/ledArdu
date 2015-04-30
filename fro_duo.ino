#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <math.h>

#define PIN A0
#define NUMPIXELS 20
#define GOALTIME 20000.0
#define PI 3.1415936
#define MOTORPIN 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
float proces = 0;
int starttime = 0;
long vcc = 0;

void setup() {
  vcc = readVcc();
  pixels.begin();
  pinMode(MOTORPIN, OUTPUT);
  Serial.begin(9600);
} 

void loop() {
  Serial.println(vcc);
  if(vcc < 4900) { //this is an evil hack ;)
                   //wehn you reset the arduwino the voltage is lower becouse the leds are glowing and taking current
    digitalWrite(MOTORPIN, HIGH);
    starttime = millis();
    while(millis() - starttime < 512) {
      fillWith((millis() - starttime) / 2,0,255- ((millis() - starttime) / 2));
      pixels.show();
      Serial.println(vcc);
    }

    starttime = millis();
    while(proces <= 1) {
      proces = ((millis() - starttime) / GOALTIME);
      //Serial.println(proces);
      fillWithTo(0, 255, 0, 255, 0, 0, proces);
      pixels.show();
      Serial.println(vcc);
    }

    starttime = millis();
    while(millis() - starttime < 1*PI * 1000) {
      fillWith(0, (cos((millis() - starttime) / 250.0) + 1) * 127.5, 0);
      pixels.show();
      Serial.println(vcc);
    }
    
    digitalWrite(MOTORPIN, LOW);
    
    starttime = millis();
    while(millis() - starttime < 2550) {
      fillWith(0, 255 - ((millis() - starttime) / 10), (millis() - starttime) / 10);
      pixels.show();
      Serial.println(vcc);
    }
  } else {
    starttime = millis();
    while(millis() - starttime < 2550) {
      fillWith(0, 0, (millis() - starttime) / 10);
      pixels.show();
      Serial.println(vcc);
    }
  }
  
  while(true) {
    fillWith(0, 0, 255);
      pixels.show();
  }
}



