#include <Servo.h>

Servo servoA;
Servo servoLeft;
Servo servoSR;

int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
int blackoutTime = 0;

void setup() {
  Serial.begin(9600); //sets serial port for communication
  servoA.attach(9);
  servoSR.attach(10);
}

void SR() {
  servoSR.write(0);
  delay(300);
  servoSR.write(50);
}

//Press button A and then wait N milliseconds
void delayA(int N) {
  servoA.write(0); //Press button
  delay(300);
  servoA.write(110); //Back to resting position
  delay(N-300);
}

//Nintendo screen
//Star screen
//Black version screen
//Continue screen
//Summer screen
//Open gift
//Dialogue
//Gift note
//Choose Tepig
//Confirm
//Misc. Dialogue
void dialogue(int in[]) {
  for(int i=0;i<sizeof(in);i++) {
    delayA(in[i]);
  }
}

void bottomScreen() {
   while(sensorValue<400) {
    blackoutTime++;
    delay(100);
    if(blackoutTime > 2000) break;
    sensorValue = analogRead(sensorPin);
  }
  Serial.println(blackoutTime);
  if(blackoutTime > 193) {
    while(true) {}
  }
}

void loop() {
  
  SR();
  int blackoutTime = 0;
  int times[] = {4500,2500,2900,6000,1000,1000,4000,6000,1000,1000,8000,
  2000,2000,1000,4000,1000,1000,1000,1000,1000,1000,1000,1000};
  
  delay(5000); //Wait for Nintendo screen to pop up
  dialogue(times);
  delay(2000);
  sensorValue = analogRead(sensorPin);
  bottomScreen();
   
}
