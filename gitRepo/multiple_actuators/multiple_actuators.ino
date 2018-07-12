const int numOfActuators = 4;
const int relay1Pins[] = {3, 4, 5, 6};
const int relay2Pins[] = {7, 8, 9, 10};

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
}

void extendLinearActuator(int actuatorNum, int duration) {
  int startTime = millis();
  while (millis() < startTime + duration) {
    digitalWrite(relay1Pins[actuatorNum - 1], HIGH);
    digitalWrite(relay2Pins[actuatorNum - 1], LOW);
    Serial.println("Extending");
  }
  shutRelayOff(relay1Pins[actuatorNum - 1]);
}

void retractLinearActuator(int actuatorNum, int duration) {
  int startTime = millis();
  while (millis() < startTime + duration) {
    digitalWrite(relay1Pins[actuatorNum - 1], LOW);
    digitalWrite(relay2Pins[actuatorNum - 1], HIGH);
    Serial.println("Retracting");
  }
  shutRelayOff(relay2Pins[actuatorNum - 1]);
}

void shutRelayOff(int relayPin) {
  digitalWrite(relayPin, LOW);
  Serial.println("IDLE");
}

void loop(){
  while (Serial.available() == 0) {
    // Wait for user input  
  }
  String mode = Serial.readString();
  if (mode == String("e\n") || mode == String("r\n")) {
    int duration = -1;
    while (duration <= 0) {
      while (Serial.available() == 0) {
        // Wait for user input  
      }
      duration = Serial.readString().toInt();
    }
    int actuatorNum = 1;
    if (mode == String("e\n")) {
      Serial.println("Extending for " + String(duration) + " ms.");
      extendLinearActuator(actuatorNum, duration);
    } else if (mode == String("r\n")) {
      Serial.println("Retracting for " + String(duration) + " ms.");
      retractLinearActuator(actuatorNum, duration);
    }
  }
}

