
//H-Bridge Inputs
const int forwardOP = 11;
const int backwardOP = 10;

const int forwardOP1  = 5;
const int backwardOP1 = 4;

//H-Bridge Inputs
const int ena = 12;
const int ena1 = 3;

//Demo Button
const int demo = 7;
boolean helper = false;

//Joystick Output Values
int yValue = 0;
int xValue = 0;

unsigned int x;
unsigned int y;

//speed variable to be mapped from the joystick values.
int Speed = 0;

void setup() {
  
  pinMode(demo, INPUT_PULLUP);
  pinMode(forwardOP, OUTPUT);
  pinMode(forwardOP1, OUTPUT);
  pinMode(backwardOP, OUTPUT);
  pinMode(backwardOP1, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(ena1, OUTPUT);

  digitalWrite(ena, LOW);
  digitalWrite(ena1, LOW);
  digitalWrite(forwardOP, HIGH);
  digitalWrite(forwardOP1, HIGH);
  digitalWrite(backwardOP, LOW);
  digitalWrite(backwardOP1, LOW);

  Serial.begin(38400);


}

void loop() {
  x = 510/4;
  y = 510/4;

  if(digitalRead(demo) == HIGH){
    helper = !helper;
  }

  //reading the data when there is data
  while(Serial.available() > 0){
    y = Serial.read();
    delay(10);
    x = Serial.read();
    
  }
  delay(10);
  //converting the x and y values back to the range of 0-1023
  yValue = y * 4;
  xValue = x * 4;

//if conditional for moving the joystick forwards
  if (yValue > 534){
    digitalWrite(backwardOP, LOW);
    digitalWrite(forwardOP, HIGH);

    digitalWrite(backwardOP1, LOW);
    digitalWrite(forwardOP1, HIGH);

    Speed = map(yValue, 534, 1023, 0, 255);   
  }

//If conditional for the joystick going backward
   else if(yValue < 490){
    digitalWrite(forwardOP, LOW);
    digitalWrite(backwardOP, HIGH);

    digitalWrite(forwardOP1, LOW);
    digitalWrite(backwardOP1, HIGH);

    yValue = yValue - 490;
    yValue = yValue * -1;

    Speed = map(yValue, 0 , 490, 0 , 255);
  }

//if conditional for when the joystick turns a direction
  else if (xValue > 534){
    digitalWrite(forwardOP, LOW);
    digitalWrite(backwardOP, HIGH);

    digitalWrite(backwardOP1, LOW);
    digitalWrite(forwardOP1, HIGH);

    Speed = map(xValue, 534, 1023, 0, 255);  
  }
  
//if conditional for when the joystick turns the opposite direction
  else if(xValue < 490){
    digitalWrite(backwardOP, LOW);
    digitalWrite(forwardOP, HIGH);

    digitalWrite(forwardOP1, LOW);
    digitalWrite(backwardOP1, HIGH);
    

    xValue = xValue - 490;
    xValue = xValue * -1;

    Speed = map(xValue, 0 , 490, 0 , 255);
  }
  
//else the trash can should not be moving so the speed is set to zero
  else{
    Speed = 0;
  }
  if(helper == false){
      analogWrite(ena, Speed);
      analogWrite(ena1, Speed);
    
  }
  else if(helper == true){
    
    analogWrite(ena, HIGH);
    analogWrite(ena1, HIGH);
    
    digitalWrite(backwardOP, LOW);
    digitalWrite(forwardOP, LOW);

    digitalWrite(forwardOP1, LOW);
    digitalWrite(backwardOP1, LOW);


    delay(200);
    
    digitalWrite(backwardOP, HIGH);
    digitalWrite(forwardOP, LOW);

    digitalWrite(forwardOP1, LOW);
    digitalWrite(backwardOP1, HIGH);

    delay(500);

    digitalWrite(backwardOP, LOW);
    digitalWrite(forwardOP, LOW);

    digitalWrite(forwardOP1, LOW);
    digitalWrite(backwardOP1, LOW);

    delay(200);

    digitalWrite(backwardOP, LOW);
    digitalWrite(forwardOP, HIGH);

    digitalWrite(forwardOP1, HIGH);
    digitalWrite(backwardOP1, LOW);

    delay(500);
  }
}
