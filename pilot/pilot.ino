const int numOfActuators = 4;
const int relay1Pins[] = {9, 5, 10, 4};
const int relay2Pins[] = {7, 6, 11, 8};

void setup() { 
  //start serial connection
  Serial.begin(9600);

  for (int i = 0; i < numOfActuators; ++i) {
    // initialize each relay pin as an output
    pinMode(relay1Pins[i], OUTPUT);    
    pinMode(relay2Pins[i], OUTPUT);    
    
    // set the relay to low
    digitalWrite(relay1Pins[i], LOW); 
    digitalWrite(relay2Pins[i], LOW); 
  }

  down();
  delay(15000);
}

void extendLinearActuator(int actuatorNum) {
  digitalWrite(relay1Pins[actuatorNum - 1], HIGH);
  digitalWrite(relay2Pins[actuatorNum - 1], LOW);
  Serial.println("Extending");
}

void retractLinearActuator(int actuatorNum) {
  digitalWrite(relay1Pins[actuatorNum - 1], HIGH);
  digitalWrite(relay2Pins[actuatorNum - 1], HIGH);
  Serial.println("Retracting");
}

void stopLinearActuator(int actuatorNum) {
  digitalWrite(relay1Pins[actuatorNum - 1], LOW);
  digitalWrite(relay2Pins[actuatorNum - 1], LOW);
  Serial.println("Stopped");
}

void up() {
  extendLinearActuator(1);
  extendLinearActuator(2);
  extendLinearActuator(3);
  extendLinearActuator(4);
}

void down() {
  retractLinearActuator(1);
  retractLinearActuator(2);
  retractLinearActuator(3);
  retractLinearActuator(4);
}

void stopAll() {
  stopLinearActuator(1);
  stopLinearActuator(2);
  stopLinearActuator(3);
  stopLinearActuator(4);
}

void oscillate(int duration) {
  int startTime = millis();
  up();
  while(millis() <= startTime + duration) {
    // Wait
  }
  startTime = millis();
  down();
  while(millis() <= startTime + duration) {
    // Wait
  }
  stopAll();
}

void rockChair(int duration, int count, bool infinite) {
  for (int i = 0; i < count; ++i) {
    // Left up
    extendLinearActuator(1);
    extendLinearActuator(2);
    retractLinearActuator(3);
    retractLinearActuator(4);
    
    delay(duration);
  
    // Right up
    retractLinearActuator(1);
    retractLinearActuator(2);
    extendLinearActuator(3);
    extendLinearActuator(4);

    delay(duration);

    if (infinite) {
      i -= 1;
    }
  }
}

void takeSerialInput() {
  while (Serial.available() == 0) {
    // Wait for user input  
  }
  String input = Serial.readString();
  int actuatorNum = input.substring(0, 1).toInt();
  String mode = input.substring(1);
  Serial.println(String(actuatorNum) + " : " + mode);
  if (actuatorNum >= 1 && actuatorNum <= numOfActuators &&
    (mode == String("u\n") || mode == String("d\n") || mode == String("s\n"))) {
    // int actuatorNum = 1;
    if (mode == String("u\n")) {
      stopLinearActuator(actuatorNum);
      extendLinearActuator(actuatorNum);
    } else if (mode == String("d\n")) {
      stopLinearActuator(actuatorNum);
      retractLinearActuator(actuatorNum);
    } else if (mode == String("s\n")) {
      Serial.println("Stopping");
      stopLinearActuator(actuatorNum);
    }
  }
}

void takeSerialInput2() {
  while (Serial.available() == 0) {
    // Wait for user input  
  }
  String input = Serial.readString();
  int pinNum = input.substring(1).toInt();
  String mode = input.substring(0, 1);

//  Serial.println(String(pinNum) + " : " + mode);

  if (mode == String("u")) {
    Serial.println(String(pinNum) + " going up.");
    digitalWrite(pinNum, HIGH);
  } else if (mode == String("d")) {
    Serial.println(String(pinNum) + " going down.");
    digitalWrite(pinNum, LOW);
  }
}

void callibrate() {
  retractLinearActuator(1);
  retractLinearActuator(2);
  retractLinearActuator(3);
  retractLinearActuator(4);

  delay(10000);

  stopLinearActuator(1);
  stopLinearActuator(2);
  stopLinearActuator(3);
  stopLinearActuator(4);

  delay(5000);
}

void controlledRockChair(int rockDuration, int intervalDuration) {
  // Left up
  extendLinearActuator(2);
  retractLinearActuator(4);
  delay(rockDuration);

  stopLinearActuator(2);
  stopLinearActuator(4);
  delay(intervalDuration);

  // Right up
  retractLinearActuator(2);
  extendLinearActuator(4);
  delay(rockDuration);

  stopLinearActuator(2);
  stopLinearActuator(4);
  delay(intervalDuration);
}

void pilot() {
  down();
  delay(15000);
  rockChair(3000, 5, true);
}

void loop() {
//  takeSerialInput2();
//  oscillate(3000);
//  rockChair(3000, 5, true);
//  callibrate();

//  pilot();
  controlledRockChair(1500, 2000);
}

