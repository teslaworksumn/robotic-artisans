#include <AccelStepper.h>

#define acc 200
#define maxs 20000
#define spd 15000
#define movestep 100

#define home1pin 10
#define home2pin 9
#define home3pin 8

#define min1 65.0
#define max1 125.0
#define min2 65.0
#define max2 106.0
#define min3 110.0
#define max3 153.0
#define home1 64.923
#define home2 106.0
#define home3 153.0
#define angle_per_16_step 0.1125
#define unit_angle 0.1125

AccelStepper Stepper1(1,7,6);
AccelStepper Stepper2(1,5,4);
AccelStepper Stepper3(1,3,2);

int dir = 1; //used to switch direction

String inputString = "";         // a string to hold incoming data
boolean stateComplete = false;  // whether the string is complete
float curr1, curr2, curr3, new1, new2, new3; // current and target angles for each motor

int axis=0;
float error = angle_per_16_step*movestep/2;

void setup() {
  pinMode(home1pin, INPUT);
  pinMode(home2pin, INPUT);
  pinMode(home3pin, INPUT);
  // put your setup code here, to run once:
  Stepper1.setMaxSpeed(maxs); //set max speed the motor will turn (steps/second)
  Stepper1.setAcceleration(acc); //set acceleration (steps/second^2)
  Stepper1.setSpeed(spd);
  Stepper2.setMaxSpeed(maxs); //set max speed the motor will turn (steps/second)
  Stepper2.setAcceleration(acc); //set acceleration (steps/second^2)
  Stepper2.setSpeed(spd);
  Stepper3.setMaxSpeed(maxs); //set max speed the motor will turn (steps/second)
  Stepper3.setAcceleration(acc); //set acceleration (steps/second^2)
  Stepper3.setSpeed(spd);
  
  Serial.begin(9600);
  goHome();
  curr1 = home1;
  curr2 = home2;
  curr3 = home3;
  
}

boolean has_distance=false;
  int i = 0;
void loop() {
//  boolean changed = true;
//  int steps;
//  if (stateComplete) {
//    if(new1>max1){
//      new1=max1;
//    }
//    else if(new1<min1){
//      new1=min1;
//    }
//    if(new2>max2){
//      new2=max2;
//    }
//    else if(new2<min2){
//      new2=min2;
//    }
//    if(new3>max3){
//      new3=max3;
//    }
//    else if(new3<min3){
//      new3=min3;
//    }
//    /*
//    while(changed){ 
//      changed = false;
//      if(curr1>(new1+error)){
//        changed = true;
//        curr1-=angle_per_16_step*movestep;
//        Stepper1.move(dir*movestep);
//        Stepper1.run();
//      }
//      else if(curr1<(new1-error)){
//        changed = true;
//        curr1+=angle_per_16_step*movestep;
//        Stepper1.move(-dir*movestep);
//        Stepper1.run();
//      }
//      if(curr2>(new2+error)){
//        changed = true;
//        curr2-=angle_per_16_step*movestep;
//        Stepper2.move(dir*movestep);
//        Stepper2.run();
//      }
//      else if(curr2<(new2-error)){
//        changed = true;
//        curr2+=angle_per_16_step*movestep;
//        Stepper2.move(-dir*movestep);
//        Stepper2.run();
//      }
//      if(curr3>(new3+error)){
//        changed = true;
//        curr3-=angle_per_16_step*movestep;
//        Stepper3.move(dir*movestep);
//        Stepper3.run();
//      }
//      else if(curr3<(new3-error)){
//        changed = true;
//        curr3+=angle_per_16_step*movestep;
//        Stepper3.move(dir*movestep);
//        Stepper3.run();
//      }
//      Serial.print(new1);
//      Serial.println(curr1);
//      Serial.print(new2);
//      Serial.println(curr2);
//      Serial.print(new3);
//      Serial.println(curr3);
//    }*/
//    Serial.println("Before");
//    Serial.println(new1);
//    Serial.println(curr1);
//    Serial.println(new2);
//    Serial.println(curr2);
//    Serial.println(new3);
//    Serial.println(curr3);
//    steps = (curr1-new1)/unit_angle;
//    curr1-=steps*unit_angle;
//    Serial.println(steps);
//    //Stepper1.move(steps);
//    Stepper1.move(5);
//    steps = (curr2-new2)/unit_angle;
//    curr2-=steps*unit_angle;
//    Serial.println(steps);
//    Stepper2.move(steps);
//    
//    steps = (curr3-new3)/unit_angle;
//    curr3-=steps*unit_angle;
//    Serial.println(steps);
//    Stepper3.move(steps);
//    
//    Stepper1.run();
//    Stepper2.run();
//    Stepper3.run();
//    
//  Serial.println("After");
//    Serial.println(new1);
//    Serial.println(curr1);
//    Serial.println(new2);
//    Serial.println(curr2);
//    Serial.println(new3);
//    Serial.println(curr3);
//    
//    stateComplete = false;
//  }
//int target =100;
//for(int i = 0 ; i < 10 ; i++ ) {
//  Stepper1.move(-1*movestep);
//  Stepper1.run();
//}
//delay(1000);
//for(int i = 0 ; i < 10 ; i++ ) {
//  Stepper1.move(-1*movestep);
//  Stepper1.run();
//}
//delay(1000);
/*
if(!has_distance){
   if(i%2 == 0 ){
    Stepper1.move(-10);
   }
   if(i%2 == 1){
    Stepper1.move(10);  
   }
   i++;
}*/
Stepper1.move(-10);
Serial.println(Stepper1.distanceToGo());
while(Stepper1.distanceToGo()!=0)
{
  Stepper1.run();
}
//let us try to get to a position then stop
//Stepper1.run();
//has_distance = (Stepper1.distanceToGo() > 0 ); 
//Serial.println(has_distance);

   
   
//    Stepper1.move(250);
//    Stepper1.run();
//    while( Stepper1.distanceToGo() > 0 ){}
//    Stepper1.move(250);
//    Stepper1.run();
//    while( Stepper1.distanceToGo() > 0 ){}
  

}


void goHome(){
  while(digitalRead(home1pin)==HIGH | digitalRead(home2pin)==HIGH | digitalRead(home3pin)==HIGH){
  if(digitalRead(home1pin)==HIGH){
    Stepper1.move(movestep);
  }
  if(digitalRead(home2pin)==HIGH){
    Stepper2.move(-1*movestep);
  }       
  if(digitalRead(home3pin)==HIGH){
    Stepper3.move(movestep);
  }
  Stepper1.run();
  Stepper2.run();
  Stepper3.run();
  }
}

void serialEvent(){
  while (Serial.available()) {
    // get the new byte:
    new1 = Serial.parseFloat();
    new2 = Serial.parseFloat();
    new3 = Serial.parseFloat();
    
    Serial.read();
    stateComplete = true;
  }
}

