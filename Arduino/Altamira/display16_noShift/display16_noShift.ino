//**************************************************************//
//  Name    : 16 Pixel Display Prototyping Code                 //
//  Author  : Sam Finnegan                                      //
//  Date    : 28 April 2016                                     //
//  Version : 2.6                                               //
//  Notes   : Code for ME 4054W Senior Design                   //
//          : for use by UMN proDUCT lab                        //
//****************************************************************

//int motorFPin[16] = {22,24};
//int motorBPin[16] = {2,6,9,12};

String inputString = "";// a string to hold incoming data
bool newCmd=false;

  int pixel;
  int action;
  int timeDelay;
  int timeStep;
  int timeCal[16]={100,105,150,100,125,185,200,170,100,95,200,150,90,175,120,100};
  
void setup() {
  for(int i=22; i<54; i++){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600); //open serial communcations at 9600 baud
  inputString.reserve(200); //reserve 200 bytes for the input
}

void loop() {
  if(newCmd){
//    Serial.println(pixel);
//    Serial.println(timeDelay);
//    Serial.println(action);
  switch(action){
    case 0://all down
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),HIGH);
      digitalWrite((2*i+21),LOW);
    }
      delay(timeDelay);
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),LOW);
    }
    break;
    case 2://down
      digitalWrite((2*pixel+20),HIGH);
      digitalWrite((2*pixel+21),LOW);
      delay(timeDelay);
      digitalWrite((2*pixel+20),LOW);
      digitalWrite((2*pixel+21),LOW);
    break;
    case 1://up
      digitalWrite((2*pixel+20),LOW);
      digitalWrite((2*pixel+21),HIGH);
      delay(timeDelay);
      digitalWrite((2*pixel+20),LOW);
      digitalWrite((2*pixel+21),LOW);
    break;
    case 3: //all up
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),HIGH);
    }
    delay(timeDelay);
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),LOW);
    }
    break;
    case 4: //wave up
    for(int i=1;i<5;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),HIGH);
    }
    delay(timeDelay/4);
    for(int i=5;i<9;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),HIGH);
    }
    delay(timeDelay/4);
    for(int i=9;i<13;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),HIGH);
    }
    delay(timeDelay/4);
    for(int i=13;i<17;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),HIGH);
    }
    delay(timeDelay/4);
    for(int i=1;i<5;i++){
      digitalWrite((2*i+20),HIGH);
      digitalWrite((2*i+21),LOW);
    }
    delay(timeDelay/4);
    for(int i=5;i<9;i++){
      digitalWrite((2*i+20),HIGH);
      digitalWrite((2*i+21),LOW);
    }
    delay(timeDelay/4);
    for(int i=9;i<13;i++){
      digitalWrite((2*i+20),HIGH);
      digitalWrite((2*i+21),LOW);d
    }
    delay(timeDelay/4);
    for(int i=13;i<17;i++){
      digitalWrite((2*i+20),HIGH);
      digitalWrite((2*i+21),LOW);
    }
    delay(timeDelay/4);
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),LOW);
    }
    break;
    case 5: //wave down
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),HIGH);
      digitalWrite((2*i+21),LOW);
      if(i%4==0){
        delay(timeDelay/4);
      }
    }
    for(int i=1;i<17;i++){
      digitalWrite((2*i+20),LOW);
      digitalWrite((2*i+21),LOW);
    }
    break;
  }
  newCmd=false;
  }
}
int k=0;
//Receive Commands from the serial port and update setpoint
//Command format: '<pixel number>' + ' ' + '<timeDelay>' + ' ' + '<command>' + '\n'
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar==' '){
      switch(k){
        case 0:
          pixel = inputString.toInt();
          inputString ="";
          k = 1;
        break;
        case 1:
          timeDelay = inputString.toInt();
          inputString ="";
          k = 2;
        break;
      }
    }
    if(inChar=='\n'){
      action = inputString.toInt();
      inputString ="";
      newCmd=true;
      k=0;
    }
  }
}
