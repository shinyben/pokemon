#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Initalize LCD
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//pins for buttons
int UP = 2;
int DOWN = 3;
int LEFT = 4;
int RIGHT = 5;
int A = 13;

int sensorPin = A0; //input pin for LDR
int sensorValue = 0; //value coming from the sensor
int totalEncounters = 0; //amount of encounters
int WALK = 2000; //length of L/R walk 

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
    if(random(50000) == 250) {hold(A,50);delay(100);hold(A,50);Serial.println(1);}
    walkingTime++;
    
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
  }
}

void timeEncounter() {
  long encounterTime = 0;
  boolean checkOne = false;
  boolean checkTwo = false;
  while(!(checkOne && sensorValue < 550)) {
    sensorValue = analogRead(sensorPin);
    if(sensorValue < 700) checkOne = true;
    encounterTime++;
    Serial.println(sensorValue);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(encounterTime);
  Serial.println(encounterTime);
//  if((encounterTime > 81000 && encounterTime < 94000) || encounterTime > 101000) {
//For Chargestone Cave
//    if(encounterTime > 75000) {
//    while(true) {
//      lcd.setCursor(0,1);
//      lcd.print(totalEncounters);}
//  }
}

void runAway() {
  hold(RIGHT,60);
  hold(LEFT,60);
  hold(RIGHT,60);
  hold(A,60);
}

void loop() {
  highAll();
  sensorValue = analogRead(sensorPin);

  walkUntilLessThan(750); //Walk until encounter starts
  timeEncounter();
  totalEncounters++;
  
  lcd.setCursor(0,1);
  lcd.print(totalEncounters);
  
  delay(200); //Wait for run option
  runAway();
  delay(4500); //Wait for walking screen
}
