// define a constant value named stepPin and assign the value 9 to it - this value will not change during our code
// this assumes digital pin 9 of your Arduino is attached to the step input of your driver
#define stepPinOne 7
#define stepPinTwo 5
#define stepPinThree 3
 
// define a constant value named dirPin and assign the value 8 to it - this value will not change during our code
// this assumes digital pin 8 of your Arduino is attached to the step input of your driver
#define dirPinOne 6
#define dirPinTwo 4
#define dirPinThree 2

int customDelay,customDelayMapped, action; // Defines variables
String inputString = "";         // a string to hold incoming data
boolean stateComplete = false;  // whether the string is complete

void setup() {
  // digital pins on the Arduino can only be either set as an output or input - in our case we want to send data to the driver, so we choose output
  pinMode(stepPinOne , OUTPUT);
  pinMode(dirPinOne , OUTPUT);
  pinMode(stepPinTwo, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);
  pinMode(stepPinThree, OUTPUT);
  pinMode(dirPinThree, OUTPUT);

  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

// Function for reading the Potentiometer
int speedUp() {
  int customDelay = analogRead(A0); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1023, 300,4000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  return newCustom;  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      action = inputString.toInt(); 
      inputString = "";
      stateComplete = true;
    }
  }
}
void loop() {
  //customDelayMapped = speedUp();
  
  if (stateComplete) {
    if(action==3){
      digitalWrite(dirPinTwo, LOW);
      digitalWrite(stepPinTwo,HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPinTwo , LOW);
      delayMicroseconds(1000);  
    }
    else if(action==6){
      digitalWrite(dirPinThree, HIGH);
      digitalWrite(stepPinThree , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinThree , LOW);
      delayMicroseconds(customDelayMapped);  
    }
    else if(action==5){
      digitalWrite(dirPinThree, LOW);
      digitalWrite(stepPinThree , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinThree , LOW);
      delayMicroseconds(customDelayMapped);
    }
    else if(action==2){
      digitalWrite(dirPinOne, HIGH);
      digitalWrite(stepPinOne , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinOne , LOW);
      delayMicroseconds(customDelayMapped);
    }
    else if(action==1){
      digitalWrite(dirPinOne, LOW);
      digitalWrite(stepPinOne , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinOne , LOW);
      delayMicroseconds(customDelayMapped);
    }
    else if(action==4){
      digitalWrite(dirPinTwo, HIGH);
      digitalWrite(stepPinTwo , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinTwo , LOW);
      delayMicroseconds(customDelayMapped); 
    }

    stateComplete = false;
  }
}



