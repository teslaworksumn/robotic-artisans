#include <string.h>
#include <ctype.h>

#define OPTO_PULLUPS_INTERNAL 1

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

#define home1pin 3
#define home2pin 14
#define home3pin 18


int dist;
String inputString="";
bool newCmd=false;

#define angle_per_16_step 0.0275
#define unit_angle 0.0275

#define stepDelay 200
#define movestep 10

boolean stateComplete = false;  // whether the string is complete
float curr1, curr2, curr3, new1, new2, new3, triggerHome; // current and target angles for each motor
int newcoor[3];
int axis=0;
int dir = 1; //used to switch direction
float error = angle_per_16_step*movestep/2;
int degree = 3;

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
  pinMode(home1pin, INPUT);
  pinMode(home2pin, INPUT);
  pinMode(home3pin, INPUT);

  digitalWrite(enableOne, LOW);
  digitalWrite(enableTwo, LOW);
  digitalWrite(enableThree, LOW);


  Serial.begin(9600); //open serial communcations at 9600 baud
  inputString.reserve(200); //reserve 200 bytes for the input
  //goHome();
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean changed = true;
  int steps;
  
  if(stateComplete == true){
    
      steps = (newcoor[0])/unit_angle;
      goStep(-1*dir*steps,1);
     
      steps = (newcoor[1])/unit_angle;
      goStep(-1*dir*steps,2);
     
      steps = (newcoor[2])/unit_angle;
      goStep(dir*steps,3);
    if(digitalRead(home1pin)==LOW){
      Serial.println("Pressed pin1");
    }
    if(digitalRead(home2pin)==LOW){
 
      Serial.println("Pressed pin2");
    }       
    if(digitalRead(home3pin)==LOW){
       Serial.println("Pressed pin3");
    }

   
  }

  stateComplete = false;
  //delay(1);
  //Serial.println(steps);
}
int command_num = 0 ;

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar==' '){
      if(command_num != 2){
        newcoor[command_num] = degree * inputString.toInt();
        command_num++;
      }
      inputString ="";
    }
    else if(inChar=='\n'){
      newcoor[command_num] = degree * inputString.toInt();
      command_num = 0;
      inputString ="";
      Serial.println(newcoor[0]);
      Serial.println(newcoor[1]);
      Serial.println(newcoor[2]);
      Serial.println("");
      stateComplete=true;
    }
    
  }
}


void goHome(){
  Serial.println("Made it to goHome");
  while(digitalRead(home1pin)==HIGH | digitalRead(home2pin)==HIGH | digitalRead(home3pin)==HIGH){
    if(digitalRead(home1pin)==HIGH){
      goStep(5,1);
      Serial.println("Moving pin1");
    }
    if(digitalRead(home2pin)==HIGH){
      goStep(-5,2);
      Serial.println("Moving pin2");
    }       
    if(digitalRead(home3pin)==HIGH){
      goStep(5,3);
      Serial.println("Moving pin3");
    }
  }
}

void goStep(int nStep, int axis){
  //Serial.println(axis);
  if(axis==1){
        if(nStep > 0 ){
            digitalWrite(dirPinOne, HIGH);
            accelStep(nStep,stepPinOne);
        } else if(nStep < 0 ){
            digitalWrite(dirPinOne, LOW);
            accelStep(nStep*-1,stepPinOne);
        }
    }else if(axis==2){
        if(nStep > 0 ){
            digitalWrite(dirPinTwo, HIGH);
            accelStep(nStep,stepPinTwo);
        } else if(nStep < 0){ 
            digitalWrite(dirPinTwo, LOW);
            accelStep(nStep*-1,stepPinTwo);
        }
    }else if(axis==3 ){
        if(nStep > 0 ){
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
