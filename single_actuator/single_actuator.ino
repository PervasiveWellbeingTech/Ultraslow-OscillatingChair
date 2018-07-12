
const int relay1 =  7;
const int relay2 =  8;
const int sensorPin = 0;    // select the input pin for the potentiometer

// variables will change:
int sensorValue = 0;  // variable to store the value coming from the sensor
int goalPosition = 350; 
int CurrentPosition = 0; 
boolean Extending = false;
boolean Retracting = false;

void setup() { 
  //start serial connection
  Serial.begin(9600);
  
  // initialize the relay pin as an output:
  pinMode(relay1, OUTPUT);    
  pinMode(relay2, OUTPUT);    
  
  //preset the relays to LOW
  digitalWrite(relay1, LOW); 
  digitalWrite(relay2, LOW); 
  
}

void extendLinearActuator(int ms) {
  digitalWrite(relay1, HIGH);  
  digitalWrite(relay2, LOW);  
  Serial.println("Extending");
}

void retractLinearActuator(int ms) {
  digitalWrite(relay1, LOW);  
  digitalWrite(relay2, HIGH);  
  Serial.println("Retracting");
}

void shutRelayOff(int relayPin) {
  digitalWrite(relay1, LOW); 
  Serial.println("IDLE"); 
}

void loop(){
  
  // read the value from the sensor:
  CurrentPosition = analogRead(sensorPin); 
  
  // print the results to the serial monitor:
  Serial.print("Current = " );                       
  Serial.print(CurrentPosition);      
  Serial.print("\t Goal = ");      
  Serial.println(goalPosition);  
  
  if (Extending = true && CurrentPosition > goalPosition) {
    //we have reached our goal, shut the relay off
    digitalWrite(relay1, LOW); 
    boolean Extending = false; 
    Serial.println("IDLE");  
  }
  
  if (Retracting = true && CurrentPosition < goalPosition){
    //we have reached our goal, shut the relay off
    digitalWrite(relay2, LOW); 
    boolean Retracting = false; 
    Serial.println("IDLE");  
  }
  
  
}
