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
 
// define the pins on which we've put our N.O. buttons
#define buttonOne 13
#define buttonTwo 12
#define buttonThree 11

#define stepDelay 200

void setup() {
  // digital pins on the Arduino can only be either set as an output or input - in our case we want to send data to the driver, so we choose output
  pinMode(stepPinOne , OUTPUT);
  pinMode(dirPinOne , OUTPUT);
  pinMode(stepPinTwo, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);
  pinMode(stepPinThree, OUTPUT);
  pinMode(dirPinThree, OUTPUT);
 
  // define our button pins as input pullup type - see http://arduino.cc/en/Tutorial/DigitalPins#.Uyphr4WN7q4
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
}

int axis=0;

void loop() {
  if(digitalRead(buttonOne)==HIGH){
    axis = (axis+1)%3;
    while(digitalRead(buttonOne)==HIGH){}
  }

      if(digitalRead(buttonTwo)==HIGH){
          goStep(1000,axis);
          while(digitalRead(buttonTwo)==HIGH){}
      } else if(digitalRead(buttonThree)==HIGH){
          goStep(-1000,axis);
          while(digitalRead(buttonThree)==HIGH){}
      }
}

void goStep(int nStep, int axis){
  if(axis==0){
        if(nStep > 0){
            digitalWrite(dirPinOne, HIGH);
            accelStep(nStep,stepPinOne);
        } else if(nStep < 0){
            digitalWrite(dirPinOne, LOW);
            accelStep(nStep*-1,stepPinOne);
        }
    }else if(axis==1){
        if(nStep > 0){
            digitalWrite(dirPinTwo, HIGH);
            accelStep(nStep,stepPinTwo);
        } else if(nStep < 0){
            digitalWrite(dirPinTwo, LOW);
            accelStep(nStep*-1,stepPinTwo);
        }
    }else if(axis==2){
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

