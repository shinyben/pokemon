#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int UP = 2;
int DOWN = 3;
int LEFT = 4;
int RIGHT = 5;
int A = 13;

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

int walk = 2000;

void walkUntil(int lightValue) {
  int walkingTime = 0;
  
  //Walk around while there's no encounter started
  while(sensorValue < lightValue) {
    if(walkingTime < walk/2) {
      hold(RIGHT,1);
    }
    else {
      hold(LEFT,1);
    }
    if(walkingTime > walk) {
      walkingTime = 0;
    }
    walkingTime++;
    sensorValue = analogRead(sensorPin);
  }
}

void timeEncounter() {
  long encounterTime = 0;
  boolean checkOne = false;
  boolean checkTwo = false;
  while(!(checkOne && checkTwo && sensorValue > 400)) {
    sensorValue = analogRead(sensorPin);
    if(sensorValue > 800) checkOne = true;
    if(sensorValue < 350 && checkOne) checkTwo = true;
    encounterTime++;
  }
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(encounterTime);
  Serial.println(encounterTime);
//  if(encounterTime > 135500) { //General purpose (Routes 201, 205)
    /*if((encounterTime > 122500 && encounterTime < 126000) 
    || (encounterTime > 126600 && encounterTime < 127900) 
    || (encounterTime > 128800 && encounterTime < 136300) 
    || encounterTime > 137200) {*/ //Eternea Forest
   if((encounterTime > 132000 && encounterTime < 170000) || encounterTime > 180000) { //Route 203
    while(true) {
      lcd.setCursor(0,1);
      lcd.print(totalEncounters);}
  }
}

void runAway() {
  hold(RIGHT,60);
  hold(RIGHT,60);
  hold(LEFT,60);
  hold(RIGHT,60);
  hold(A,60);
  delay(2000);
}

void loop() {
  highAll();
  sensorValue = analogRead(sensorPin);

  walkUntil(500);
  timeEncounter();
  totalEncounters++;
  lcd.setCursor(0,1);
  lcd.print(totalEncounters);
  delay(1000);
  runAway();
  delay(4000);
  
}
