#include <Servo.h>

Servo servo1,servo2,servo3,servo4,servo5,servo6;

#define potpin1 0 
#define potpin2 1 
#define potpin3 2 
#define potpin4 3  
#define potpin5 4 
#define potpin6 5 

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
  sPos = analogRead(potpin1);
  sPos = 180 - map( sPos , 0 ,  1023 , 0 , 180 );
  //sPos = 175 - (( ((float)(sPos + 1)) / 1024 ) *  175) ;
  //Serial.println(sPos); 
  servo1.write(sPos);
  
  sPos = analogRead(potpin2);
  sPos = map( sPos , 0 ,  1023 , 0 , 75 );
  //sPos = (( ((float)(sPos + 1)) / 1024 ) * 75) ;
  //Serial.println(sPos);
  servo2.write(sPos);
  
  sPos = analogRead(potpin3);
  sPos = map( sPos , 0 ,  1023 , 45 , 180 );
  //sPos = (( ((float)(sPos + 1)) / 1024 ) * 180) ;
  servo3.write(sPos);
 
  sPos = analogRead(potpin4);
  sPos = map( sPos , 0 ,  1023 , 50 , 180 );
  //sPos = (( ((float)(sPos + 1)) / 1024 ) * 130) + 50;
  //Serial.println(sPos);
  servo4.write(sPos);
  
  sPos = analogRead(potpin5);
  //sPos = (( ((float)(sPos + 1)) / 1024 ) * 180) ;
  sPos = map( sPos , 0 ,  1023 , 0 , 180 );
  servo5.write(sPos);
  
  sPos = analogRead(potpin6);
  //Serial.println(sPos);
  //sPos = (( ((float)(sPos + 1)) / 1024 ) * 180) ;
  Serial.println(sPos);
  if( sPos > 10 ) 
    sPos = 180;
  else
    sPos = 0;
  //sPos = map( sPos , 0 ,  1023 , 0 , 1 );
  servo6.write(sPos*180);
 
}

