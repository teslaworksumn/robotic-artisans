#include <AccelStepper.h>

#define acc 3000
#define maxs 20000
#define spd 10000
#define movestep 16

#define min1 45
#define max1 90
#define min2 100
#define max2 135
#define min3 0
#define max3 180
#define home1 64.923
#define home2 128.708
#define home3 112.620
#define angle_per_16_step 0.1125

AccelStepper Stepper1(1,7,6);
AccelStepper Stepper2(1,5,4);
AccelStepper Stepper3(1,3,2);

int dir = 1; //used to switch direction

int customDelay,customDelayMapped, action; // Defines variables
String inputString = "";         // a string to hold incoming data
boolean stateComplete = false;  // whether the string is complete
float curr1, curr2, curr3, new1, new2, new3; // current and target angles for each motor

int axis=0;
float error = angle_per_16_step/2;

void setup() {
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
}

// Function for reading the Potentiometer
int speedUp() {
  int customDelay = analogRead(A0); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1023, 0,10000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  Serial.println(newCustom);
  return newCustom;  
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

void loop() {
  customDelayMapped = speedUp();
  boolean changed = true;
  if (stateComplete) {
    if(new1>max1){
      new1=max1;
    }
    else if(new1<min1){
      new1=min1;
    }
    if(new2>max2){
      new2=max2;
    }
    else if(new2<min2){
      new2=min2;
    }
    if(new3>max3){
      new3=max3;
    }
    else if(new3<min3){
      new3=min3;
    }
    while(changed){ 
      changed = false;
      if(curr1>(new1+error)){
        changed = true;
        curr1-=angle_per_16_step;
        Stepper1.move(-1);
        Stepper1.run();
      }
      else if(curr1<(new1-error)){
        changed = true;
        curr1+=angle_per_16_step;
        Stepper1.move(1);
        Stepper1.run();
      }
      if(curr2>(new2+error)){
        changed = true;
        curr2-=angle_per_16_step;
        Stepper2.move(-1);
        Stepper2.run();
      }
      else if(curr2<(new2-error)){
        changed = true;
        curr2+=angle_per_16_step;
        Stepper2.move(1);
        Stepper2.run();
      }
      if(curr3>(new3+error)){
        changed = true;
        curr3-=angle_per_16_step;
        Stepper3.move(-1);
        Stepper3.run();
      }
      else if(curr3<(new3-error)){
        changed = true;
        curr3+=angle_per_16_step;
        Stepper3.move(1);
        Stepper3.run();
      }
    }
    Serial.print(new1);
    Serial.println(curr1);
    Serial.print(new2);
    Serial.println(curr2);
    Serial.print(new3);
    Serial.println(curr3);
    stateComplete = false;
  }
}
