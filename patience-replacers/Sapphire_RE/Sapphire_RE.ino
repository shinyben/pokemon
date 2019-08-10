#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int UP = 2;
int DOWN = 3;
int LEFT = 4;
int RIGHT = 5;
int A = 12;

int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
int blackoutwalkingTime = 0;

int totalEncounters = 0;

void setup() {
  Serial.begin(9600);
  pinMode(UP,OUTPUT);
  pinMode(DOWN,OUTPUT);
  pinMode(LEFT,OUTPUT);
  pinMode(RIGHT,OUTPUT);
  pinMode(A,OUTPUT);
  lcd.begin(16, 2);
}

void press(int button) {
  digitalWrite(button,LOW);
  delay(1);
  digitalWrite(button, HIGH);
 
}

void hold(int button, int time) {
  digitalWrite(button,LOW);
  delay(time);
  digitalWrite(button,HIGH);
}

void lowAll() {
  digitalWrite(UP,LOW);
  digitalWrite(DOWN,LOW);
  digitalWrite(LEFT,LOW);
  digitalWrite(RIGHT,LOW);
  digitalWrite(A,LOW);
}

void highAll() {
  digitalWrite(UP,HIGH);
  digitalWrite(DOWN,HIGH);
  digitalWrite(LEFT,HIGH);
  digitalWrite(RIGHT,HIGH);
  digitalWrite(A,HIGH);
}

int walk = 100;

void walkUntilGreaterThan(int lightValue) {
  int walkingTime = 0;
  
  //Walk around while there's no encounter started
  while(sensorValue < lightValue) {
    if(walkingTime < walk/2) {
      hold(RIGHT,5);
    }
    else {
      hold(LEFT,5);
    }
    if(walkingTime > walk) {
      walkingTime = 0;
    }
    walkingTime++;
    sensorValue = analogRead(sensorPin);
//    Serial.println(sensorValue);
  }
}

void walkUntilLessThan(int lightValue) {
  int walkingTime = 0;
  
  //Walk around while there's no encounter started
  while(sensorValue > lightValue) {
    if(walkingTime < walk/2) {
      hold(RIGHT,5);
    }
    else {
      hold(LEFT,5);
    }
    if(walkingTime > walk) {
      walkingTime = 0;
    }
    walkingTime++;
    sensorValue = analogRead(sensorPin);
//    Serial.println(sensorValue);
  }
}

void timeEncounter() {
  long encounterTime = 0;
  while(sensorValue > 450) { //Fiery path
    sensorValue = analogRead(sensorPin);
    encounterTime++;
//    Serial.println(sensorValue);
  }
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(encounterTime);
  Serial.println(encounterTime);
}

void runAway() {
  hold(A,60); //A wild NAME appeared! 
  delay(3500);
  hold(RIGHT,60);
  hold(DOWN,60);
  sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
  hold(A,60); //Run
  delay(400);
  hold(A,60); //You got away safely!
}

void loop() {
  highAll();
  sensorValue = analogRead(sensorPin);

  walkUntilGreaterThan(750); //Fiery path and Meteor Falls
//  walkUntilLessThan(750); //Granite cave
  Serial.println(0);
  timeEncounter();
  totalEncounters++;
  lcd.setCursor(0,1);
  lcd.print(totalEncounters);
  delay(2400); //Fiery path
  runAway();
  delay(3000);
  Serial.println(0);
//  while(true){}
//  while(sensorValue < 750) {} //Granite Cave
  
}
