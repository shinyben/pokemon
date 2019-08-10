int UP = 2;
int DOWN = 3;
int LEFT = 4;
int RIGHT = 5;
int X = 12;
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
  pinMode(X,OUTPUT);
  pinMode(A,OUTPUT);
}

void press(int button) {
  digitalWrite(button,LOW);
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
  digitalWrite(X,LOW);
  digitalWrite(A,LOW);
}

void highAll() {
  digitalWrite(UP,HIGH);
  digitalWrite(DOWN,HIGH);
  digitalWrite(LEFT,HIGH);
  digitalWrite(RIGHT,HIGH);
  digitalWrite(X,HIGH);
  digitalWrite(A,HIGH);
}

int holdTime = 500;

void loop() {
  highAll(); //This may be causing problems
  sensorValue = analogRead(sensorPin);
  //Trigger Horde Encounter
  hold(X,holdTime);
  hold(A,holdTime);  
  delay(1500);
  hold(UP,40); delay(50);
  hold(UP,40);
  hold(LEFT,50);
  hold(A,50);  delay(1200);
  for(int i=0;i<5;i++)  {
    hold(UP,50); delay(50);
  }
  hold(A,50); delay(50);
  hold(A,50);
  Serial.println(1);
  
  //Test blackout
  long blackoutTime = 0;
  boolean checkOne = false;
  while(!(checkOne && sensorValue < 500)) {
    sensorValue = analogRead(sensorPin);
    blackoutTime++;
    Serial.println(sensorValue);
    if(sensorValue > 900) checkOne = true;
  }
  Serial.println(blackoutTime);

  //Run
  hold(LEFT,50);
  hold(RIGHT,5000);
  hold(A,50);
  while(true) {}
}
