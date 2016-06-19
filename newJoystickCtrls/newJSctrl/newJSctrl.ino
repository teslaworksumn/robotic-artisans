#include <string.h>
#include <ctype.h>


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

#define home1pin 10

#define home2pin 9
#define home3pin 8

#define min1 60.0
#define max1 144.0
#define min2 65.0
#define max2 106.0
#define min3 110.0
#define max3 153.0
#define home1 144.0
#define home2 106.0
#define home3 153.0
#define angle_per_16_step 0.0275
#define unit_angle 0.0275

#define stepDelay 200
#define movestep 10

boolean stateComplete = false;  // whether the string is complete
float curr1, curr2, curr3, new1, new2, new3, triggerHome; // current and target angles for each motor

int axis=0;
int dir = 1; //used to switch direction
float error = angle_per_16_step*movestep/2;

void setup() {//this is the setup, it runs once
  pinMode(stepPinOne , OUTPUT);
  pinMode(dirPinOne , OUTPUT);
  pinMode(stepPinTwo, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);
  pinMode(stepPinThree, OUTPUT);
  pinMode(dirPinThree, OUTPUT);
 
  pinMode(home1pin, INPUT);
  pinMode(home2pin, INPUT);
  pinMode(home3pin, INPUT);
  
  Serial.begin(9600);
  
  goHome();
  curr1 = home1;
  curr2 = home2;
  curr3 = home3;
  //Serial.println("First\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean changed = true;
  int steps;
  char uselessInfo[20];
  if(Serial.available()){
    Serial.flush();
    Serial.readBytesUntil('X',uselessInfo,20);
    new1 = Serial.parseFloat();
    new2 = Serial.parseFloat();
    new3 = Serial.parseFloat();
    triggerHome = Serial.parseFloat();
    //Serial.flush();
    //Serial.println("G");
    
    Serial.flush();
  
    stateComplete=true;
  }

  if(stateComplete == true){
    if(curr1+new1>max1){
      new1=0;
    }
    else if(curr1+new1<min1){
      new1=0;
    }
    if(curr2+new2>max2){
      new2=0;
    }
    else if(curr2+new2<min2){
      new2=0;
    }
    if(curr3+new3>max3){
      new3=0;
    }
    else if(curr3+new3<min3){
      new3=0;
    }

    if( triggerHome==1 )
    {
      goHome();
    }
    else 
    {
      steps = (new1)/unit_angle;
      curr1+=steps*unit_angle;
      goStep(dir*steps,1);
      Serial.print("1: ");Serial.println(steps);
      Serial.print("new1: ");Serial.println(new1);
      steps = (new2)/unit_angle;
      curr2+=steps*unit_angle;
      goStep(-1*dir*steps,2);
      Serial.print("2: ");Serial.println(steps);
      Serial.print("new2: ");Serial.println(new2);
      steps = (new3)/unit_angle;
      curr3+=steps*unit_angle;
      goStep(dir*steps,3);
      Serial.print("3: ");Serial.println(steps);
      Serial.print("new3: ");Serial.println(new3);
    }
   
  }
  stateComplete = false;
  //delay(1);
  //Serial.println(steps);
}

//void serialEvent(){
//  char uselessInfo[20];
//  if(Serial.available()){
//    Serial.readBytesUntil('X',uselessInfo,20);
//    new1 = Serial.parseFloat();
//    new2 = Serial.parseFloat();
//    new3 = Serial.parseFloat();
//    Serial.println("G");
//  }
//  stateComplete=true;
//}

void goHome(){
  while(digitalRead(home1pin)==HIGH | digitalRead(home2pin)==HIGH | digitalRead(home3pin)==HIGH){
    if(digitalRead(home1pin)==HIGH){
      goStep(5,1);
    }
    if(digitalRead(home2pin)==HIGH){
      goStep(-5,2);
    }       
    if(digitalRead(home3pin)==HIGH){
      goStep(5,3);
    }
  }
}

void goStep(int nStep, int axis){
  //Serial.println(axis);
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
