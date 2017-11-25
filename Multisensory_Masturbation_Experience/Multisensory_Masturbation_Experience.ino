#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <neotimer.h>

Adafruit_DRV2605 drv;

//set up on+off vibrators and timer
Neotimer timer = Neotimer(1000);
int pinOne = 5;
int pinTwo = 6;
int pinThree = 9;
int pinFour = 10;
int pinFive = 11;
int pinSix = 12;
bool second = true;

void setup() {
  //set up DRV2605
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  drv.selectLibrary(1);
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 

  // on+off vibrators
  pinMode(pinOne, OUTPUT);
  pinMode(pinTwo, OUTPUT);
  pinMode(pinThree, OUTPUT);
  pinMode(pinFour, OUTPUT);
  pinMode(pinFive, OUTPUT);
  pinMode(pinSix, OUTPUT);
  
}

uint8_t effect = 1;

void loop() {
  //DRV2605 PWH EFFECTS #1-117
  Serial.print("Effect #"); Serial.println(effect);

  // set the effect to play
  drv.setWaveform(0, effect);  // play effect 
  drv.setWaveform(1, 0);       // end waveform

  // play the effect!
  drv.go();

  // wait a bit
  delay(500);

  effect++;
  if (effect > 117) effect = 1;

  // on+off vibrators
  if (timer.repeat(1000)) {
    if (second == true){
      digitalWrite(pinOne, HIGH);   // turn the vibrator on (HIGH is the voltage level)
      digitalWrite(pinTwo, HIGH);
      digitalWrite(pinThree, HIGH);
      digitalWrite(pinFour, HIGH);
      digitalWrite(pinFive, HIGH);
      digitalWrite(pinSix, HIGH);
      second = false;
    } else {
      digitalWrite(pinOne, LOW);    // turn the vibrator off by making the voltage LOW
      digitalWrite(pinTwo, LOW);
      digitalWrite(pinThree, LOW);
      digitalWrite(pinFour, LOW);
      digitalWrite(pinFive, LOW);
      digitalWrite(pinSix, LOW);
      second = true;
    }
  }

}
