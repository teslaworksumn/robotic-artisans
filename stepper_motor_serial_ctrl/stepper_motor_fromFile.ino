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

#define min1 45
#define max1 90
#define min2 100
#define max2 135
#define min3 0
#define max3 180
#define home1 64.923
#define home2 128.708
#define home3 112.620

int customDelay,customDelayMapped, action; // Defines variables
String inputString = "";         // a string to hold incoming data
boolean stateComplete = false;  // whether the string is complete
float curr1, curr2, curr3, new1, new2, new3; // current and target angles for each motor

void setup() {
  // digital pins on the Arduino can only be either set as an output or input - in our case we want to send data to the driver, so we choose output
  pinMode(stepPinOne , OUTPUT);
  pinMode(dirPinOne , OUTPUT);
  pinMode(stepPinTwo, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);
  pinMode(stepPinThree, OUTPUT);
  pinMode(dirPinThree, OUTPUT);

  curr1=home1;
  curr2=home2;
  curr3=home3;
  
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

// Function for reading the Potentiometer
int speedUp() {
  int customDelay = analogRead(A0); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1023, 300,4000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  return newCustom;  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    new1 = Serial.parseFloat();
    new2 = Serial.parseFloat();
    new3 = Serial.parseFloat();
    stateComplete = true;
    /*
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      action = inputString.toInt(); 
      inputString = "";
      stateComplete = true;
    }
    */
  }
}

void loop() {
  //customDelayMapped = speedUp();
  
  if (stateComplete) {
    if(new1>max1)
		nex1=max1;
	else if(new1<min1)
		new1=min1;
	if(new2>max2)
		new2=max2;
	else if(new2<min2)
		new2=min2;
	if(new3>max3)
		new3=max3;
	else if(new3<min3)
		new3=min3;
     
	while(curr1>=(new1+0.9)){
		curr1=new1-1.8;
		digitalWrite(dirPinOne, HIGH);
		digitalWrite(stepPinOne , HIGH);
		delayMicroseconds(customDelayMapped);
		digitalWrite(stepPinOne , LOW);
		delayMicroseconds(customDelayMapped);
    }
    
    while((curr1+0.9)<=new1){
      curr1=new1+1.8;
      digitalWrite(dirPinOne, LOW);
      digitalWrite(stepPinOne , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinOne , LOW);
      delayMicroseconds(customDelayMapped);
    }

   while(curr2>=(new2+0.9)){
	  curr2=new2-1.8;
      digitalWrite(dirPinTwo, HIGH);
      digitalWrite(stepPinTwo , HIGH);
      delayMicroseconds(customDelayMapped);
      digitalWrite(stepPinTwo , LOW);
      delayMicroseconds(customDelayMapped); 
    }

	while((curr2+0.9)<=new2){
		curr2=curr2+1.8;
		digitalWrite(dirPinTwo, LOW);
		digitalWrite(stepPinTwo,HIGH);
		delayMicroseconds(customDelayMapped);
		digitalWrite(stepPinTwo , LOW);
		delayMicroseconds(customDelayMapped);  
	}

	while(curr3>=(new3+0.9)){
		curr3=curr3-1.8;
		digitalWrite(dirPinThree, HIGH);
		digitalWrite(stepPinThree , HIGH);
		delayMicroseconds(customDelayMapped);
		digitalWrite(stepPinThree , LOW);
		delayMicroseconds(customDelayMapped);  
    }
    
	while((curr3+0.9)<=new3){
		curr3=curr3+1.8;
		digitalWrite(dirPinThree, LOW);
		digitalWrite(stepPinThree , HIGH);
		delayMicroseconds(customDelayMapped);
		digitalWrite(stepPinThree , LOW);
		delayMicroseconds(customDelayMapped);
    }

    stateComplete = false;
  }
}



