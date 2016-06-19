#include <string.h>
#include <ctype.h>
#include <QueueList.h>

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
float currentAngle1, currentAngle2, currentAngle3; // current and target angles for each motor
String inputString="";
int stringComplete;
int i;

int axis=0;
int dir = -1; //used to switch direction
float precision = angle_per_16_step*movestep;

//const float angleList[]={88.197 , 131.460 , 132.274 , 49.814 , 141.880 , 110.323 , 49.814 , 141.880 , 69.677 , 88.197 , 131.460 , 47.726 , 0.000 , 0.000 , 0.000 , 49.814 , 141.880 , 110.323 , 49.814 , 141.880 , 69.677 , 88.197 , 131.460 , 47.726 
//                      };
const float angleList[]={90, 106, 153};

void setup() {
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
  currentAngle1 = home1;
  currentAngle2 = home2;
  currentAngle3 = home3;
  //Serial.println("First\n");

  i = 0;
}

bool done=false;

void loop() {
  i+=3;
  if(!done){

    
  if( i<=(((sizeof(angleList))/4)-3) ){
    Serial.println("Entering if statement");
    float setAngle1=angleList[i];
    float setAngle2=angleList[i+1];
    float setAngle3=angleList[i+2];
    if(setAngle1==0.000 && setAngle2==0.000 && setAngle3==0.000){
      goHome();
      currentAngle1 = home1;
      currentAngle2 = home2;
      currentAngle3 = home3;
    } else {
      float error1=currentAngle1-setAngle1;
      float error2=currentAngle2-setAngle2;
      float error3=currentAngle3-setAngle3;
      while(abs(error1)>precision || abs(error2)>precision || abs(error3)>precision){
//        Serial.print(currentAngle1);
//        Serial.print(" ");
//        Serial.print(currentAngle2);
//        Serial.print(" ");
//        Serial.println(currentAngle3);
        if(error1<0){ //go forward
          //Serial.println("inside if 1.1");
          goStep(movestep,1);
          error1+=precision;
          currentAngle1+=precision;
        } else { //go backward
          //Serial.println("inside if 1.2");
          goStep(-1*movestep,1);
          error1-=precision;
          currentAngle1-=precision;
        }
        if(error2<0){ //go forward
          //Serial.println("inside if 2.1");
          goStep(-1*movestep,2);
          error2+=precision;
          currentAngle2+=precision;
        } else { //go backward
          //Serial.println("inside if 2.2");
          goStep(movestep,2);
          error2-=precision;
          currentAngle2-=precision;
        }
        if(error3<0){ //go forward
          //Serial.println("inside if 3.1");
          goStep(movestep,3);
          error3+=precision;
          currentAngle3+=precision;
        } else { //go backward
          //Serial.println("inside if 3.2");
          goStep(-1*movestep,3);
          error3-=precision;
          currentAngle3-=precision;
        }
      }
    }
  }
  }else{
    //do something cute
    goHome();
  }
  
}

void goHome(){
  while(digitalRead(home1pin)==HIGH | digitalRead(home2pin)==HIGH | digitalRead(home3pin)==HIGH){
    if(digitalRead(home1pin)==HIGH){
      goStep(movestep,1);
    }
    if(digitalRead(home2pin)==HIGH){
      goStep(-movestep,2);
    }       
    if(digitalRead(home3pin)==HIGH){
      goStep(movestep,3);
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
