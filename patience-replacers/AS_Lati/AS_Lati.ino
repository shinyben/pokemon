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

void loop() {
  highAll(); //This may be causing problems
  sensorValue = analogRead(sensorPin);
  int walkingTime = 0;
  
  //Walk around while there's no encounter started
  while(sensorValue < 850) {
    if(walkingTime < walk/2) {
      hold(UP,1);
    }
    else {
      hold(DOWN,1);
    }
    if(walkingTime > walk) {
      walkingTime = 0;
    }
    walkingTime++;
    sensorValue = analogRead(sensorPin);
  }

  Serial.println(totalEncounters); //Notes that encounter blackout has started

  
  long encounterTime = 0;
  boolean checkOne = false;
  while(!(checkOne && sensorValue < 600)) {
    sensorValue = analogRead(sensorPin);
    if(sensorValue > 900) checkOne = true;
    encounterTime++;
//    Serial.println(sensorValue);
  }
  Serial.println(encounterTime);
  if(encounterTime > 102000) {
    while(true) {}
  }
  delay(4000);
  hold(DOWN,60);
  delay(100);
  hold(DOWN,60);
  hold(A,50);
  delay(2000);
  totalEncounters++;
}
