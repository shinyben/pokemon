#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Initalize LCD
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//pins for buttons
int UP = 2;
int DOWN = 3;
int LEFT = 4;
int RIGHT = 5;
int A = 12;

int sensorPin = A0; //input pin for LDR
int sensorValue = 0; //value coming from the sensor
int totalEncounters = 0; //amount of encounters
int WALK = 500; //length of L/R walk 

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

void highAll() {
  digitalWrite(UP,HIGH);
  digitalWrite(DOWN,HIGH);
  digitalWrite(LEFT,HIGH);
  digitalWrite(RIGHT,HIGH);
  digitalWrite(A,HIGH);
}

void walkUntilLessThan(int lightValue) {
  int walkingTime = 0;
  
  //Walk around until encounter started
  while(sensorValue > lightValue) {
    if(walkingTime < WALK/2) {hold(RIGHT,1);}
    else {hold(LEFT,1);}
    if(walkingTime > WALK) {walkingTime = 0;}
   
    walkingTime++;
    
    sensorValue = analogRead(sensorPin);
//    Serial.println(sensorValue);
  }
}

void timeEncounter() {
  long encounterTime = 0;
  boolean checkOne = false;
  boolean checkTwo = false;
  while(!(checkOne && checkTwo && sensorValue < 500)) {
    sensorValue = analogRead(sensorPin);
    if(sensorValue < 400) checkOne = true;
    if(checkOne && sensorValue > 700) checkTwo = true;
    encounterTime++;
//    Serial.println(sensorValue);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(encounterTime);
  Serial.println(encounterTime);
  if((encounterTime > 104500 && encounterTime < 117000) || encounterTime > 122000) {
    while(true) {
      lcd.setCursor(0,1);
      lcd.print(totalEncounters);}
  }
}

void runAway(boolean first) {
  hold(LEFT,50);
  hold(LEFT,50);
  delay(500);
  if(first) hold(LEFT,50);
  hold(A,50);
  delay(50);
  hold(A,60);
}

boolean first = true;

void loop() {
  highAll();
  sensorValue = analogRead(sensorPin);

  walkUntilLessThan(750); //Walk until encounter starts
  timeEncounter();
  totalEncounters++;
  
  lcd.setCursor(0,1);
  lcd.print(totalEncounters);
  
  delay(2000); //Wait for run option
  runAway(first);
  delay(4500); //Wait for walking screen
  first = false;
}
