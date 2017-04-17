// define a constant value named stepPin and assign the value 9 to it - this value will not change during our code
// this assumes digital pin 9 of your Arduino is attached to the step input of your driver
#define stepPinOne 54
#define stepPinTwo 60
#define stepPinThree 46
 
// define a constant value named dirPin and assign the value 8 to it - this value will not change during our code
// this assumes digital pin 8 of your Arduino is attached to the step input of your driver
#define dirPinOne 55
#define dirPinTwo 61
#define dirPinThree 48

#define enableOne 38
#define enableTwo 56
#define enableThree 62

#define stepDelay 200


int axis,dist;
String inputString="";
bool newCmd=false;

void setup() {
  // digital pins on the Arduino can only be either set as an output or input - in our case we want to send data to the driver, so we choose output
  pinMode(stepPinOne , OUTPUT);
  pinMode(dirPinOne , OUTPUT);
  pinMode(stepPinTwo, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);
  pinMode(stepPinThree, OUTPUT);
  pinMode(dirPinThree, OUTPUT);
  pinMode(enableOne, OUTPUT);
  pinMode(enableTwo, OUTPUT);
  pinMode(enableThree, OUTPUT);

  digitalWrite(enableOne, LOW);
  digitalWrite(enableTwo, LOW);
  digitalWrite(enableThree, LOW);
  
  Serial.begin(9600); //open serial communcations at 9600 baud
  inputString.reserve(200); //reserve 200 bytes for the input
}

void loop() {
  if(newCmd){
    Serial.print("Axis: ");
    Serial.println(axis);
    Serial.print("Distance: ");
    Serial.println(dist);
    goStep(dist,axis);
    newCmd=false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar==' '){
      axis = inputString.toInt();
      inputString ="";
    }
    if(inChar=='\n'){
      dist = inputString.toInt();
      inputString ="";
      newCmd=true;
    }
  }
}

void goStep(int nStep, int axis){
  if(axis==1){
        if(nStep > 0){
            digitalWrite(dirPinOne, HIGH);
            accelStep(nStep,stepPinOne);
        } else if(nStep < 0){
            digitalWrite(dirPinOne, LOW);
            accelStep(nStep*-1,stepPinOne);
        }
    }else if(axis==2){
        if(nStep > 0){
            digitalWrite(dirPinTwo, HIGH);
            accelStep(nStep,stepPinTwo);
        } else if(nStep < 0){
            digitalWrite(dirPinTwo, LOW);
            accelStep(nStep*-1,stepPinTwo);
        }
    }else if(axis==3){
        if(nStep > 0){
            digitalWrite(dirPinThree, HIGH);
            accelStep(nStep,stepPinThree);
        } else if(nStep < 0){
            digitalWrite(dirPinThree, LOW);
            accelStep(nStep*-1,stepPinThree);
        }
    }
}

void accelStep(int nStep, int stepPin){
  for(int i=0; i<nStep; i++){
    digitalWrite(stepPin , HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin , LOW);
    delayMicroseconds(stepDelay);
  }
}

