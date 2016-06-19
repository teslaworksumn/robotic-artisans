#include <Servo.h>

Servo servo1,servo2,servo3,servo4,servo5,servo6;

#define potpin1 1 
#define potpin2 2 
#define potpin3 3 
#define potpin4 4  
#define potpin5 5 
#define potpin6 6 

int pos[] = {90,90,90,90,90,90};    // variable to store the servo position
int sNum,sPos;
String inputString="";
bool newCmd=false;

 
void setup() {
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  
  Serial.begin(9600); //open serial communcations at 9600 baud
  inputString.reserve(200); //reserve 200 bytes for the input
}

void loop() {
  if(newCmd){
    Serial.print("Servo: ");
    Serial.println(sNum);
    Serial.print("Position: ");
    Serial.println(sPos);
    switch(sNum){
      case 1:
        servo1.write(sPos);
      break;
      case 2:
        servo2.write(sPos);
      break;
      case 3:
        servo3.write(sPos);
      break;
      case 4:
        servo4.write(sPos);
      break;
      case 5:
        servo5.write(sPos);
      break;
      case 6:
        servo6.write(sPos);
      break;
    }
    newCmd=false; 
  }
}

int k=0;
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar==' '){
      sNum = inputString.toInt();
      inputString ="";
    }
    if(inChar=='\n'){
      sPos = inputString.toInt();
      inputString ="";
      newCmd=true;
    }
  }
}
