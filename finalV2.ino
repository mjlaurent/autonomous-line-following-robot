/*
  Project Coding Demo

  To program the car tracking the white line on a dark mat

  Your Name: Laurent, Michael Jhon               
  Version 2




*/




// assign meaningful names to those pins that will be used

#define pinLeftSensor A5      //pin A5
#define pinRightSensor A3     //pin A3
#define pinBumpSensor A4      //pin A4

#define pinLdir 11            //pin D11
#define pinRdir 12            //pin D12

#define pinPWM_L 10            //pin D10
#define pinPWM_R 9            //pin D9


//define variables to be used in script
int leftSensor = 1;
int rightSensor = 1;
int bumpSensor = 1;
int section = 0;


// Turn choice selection
bool firstTurn = false;
bool secondTurn = false;
bool thirdTurn = false;  
bool lastCourse = false;
bool turningFirstLeft = false;
bool turningSecondLeft = false;
bool turningThirdRight = false;
bool rightAngleLeft = false;
bool rightAngleRight = false;
bool stopValue = false;

// Start and stop bump
bool startBump = false;
bool stopBump = false;


// the setup function runs once when you press reset or power the board
void setup ()
{
  // define pins as input and output.
  pinMode(pinLeftSensor, INPUT);
  pinMode(pinRightSensor, INPUT);
  pinMode(pinBumpSensor, INPUT);
  
  pinMode(pinLdir, OUTPUT);
  pinMode(pinRdir, OUTPUT);
  
  pinMode(pinPWM_L, OUTPUT);
  pinMode(pinPWM_R, OUTPUT);
  
  // initialize output pins.
  digitalWrite(pinLdir, HIGH);        
  digitalWrite(pinRdir, HIGH);   
}

// the loop function runs over and over again forever
void loop()
{


  leftSensor = digitalRead(pinLeftSensor);
  rightSensor = digitalRead(pinRightSensor);
  bumpSensor = digitalRead(pinBumpSensor);
  
  // Check start bump 
  if(!bumpSensor && section == 0)  
  {
    analogWrite(pinPWM_L, 250);
    analogWrite(pinPWM_R, 250);
    digitalWrite(pinLdir, HIGH);
    digitalWrite(pinRdir, HIGH);
    delay(200);
    section++;
    startBump = true;
    firstTurn = true;
    leftSensor = 1;
    rightSensor = 1;
  }
  
  else if(bumpSensor && section == 0) 
  {
    analogWrite(pinPWM_L, 0);
    analogWrite(pinPWM_R, 0);
  }
  
  // Bump Check finished 
 
  // Start 
  
  if(!stopBump){
    // First course
    if(startBump && firstTurn){
      analogWrite(pinPWM_L, 250);
      analogWrite(pinPWM_R, 250);
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( !leftSensor && rightSensor ) {
        digitalWrite(pinLdir, LOW);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( leftSensor && !rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, LOW);
      }

      else if ( !leftSensor && !rightSensor ) {
        firstTurn = false;
        turningFirstLeft = true;
      }

    }

    else if(turningFirstLeft){
      
      digitalWrite(pinLdir, LOW);   
      digitalWrite(pinRdir, HIGH);  
      
      
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
        turningFirstLeft = false;
        secondTurn = true;
      }
      }
    // First Course finished

    // Second Course
    else if(secondTurn){
      analogWrite(pinPWM_L, 250);
      analogWrite(pinPWM_R, 250);
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( !leftSensor && rightSensor ) {
        digitalWrite(pinLdir, LOW);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( leftSensor && !rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, LOW);
      }

      else if ( !leftSensor && !rightSensor ) {
        secondTurn = false;
        turningSecondLeft = true;
      }

    }

    else if(turningSecondLeft){
      
      digitalWrite(pinLdir, LOW);   
      digitalWrite(pinRdir, HIGH);  
      
      
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
        turningSecondLeft = false;
        thirdTurn = true;
      }
      }

    // Second Course finished

    // Third Course
    else if(thirdTurn){
      analogWrite(pinPWM_L, 250);
      analogWrite(pinPWM_R, 250);
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( !leftSensor && rightSensor ) {
        digitalWrite(pinLdir, LOW);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( leftSensor && !rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, LOW);
      }

      else if ( !leftSensor && !rightSensor ) {
        thirdTurn = false;
        turningThirdRight = true;
      }

    }

    else if(turningThirdRight){
      
      digitalWrite(pinLdir, HIGH);  
      digitalWrite(pinRdir, LOW);  
      
      
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
        turningThirdRight = false;
        lastCourse = true;
      }
      }
    // Third Course Finished

    // Last Course 
    else if(lastCourse){
      analogWrite(pinPWM_L, 125);
      analogWrite(pinPWM_R, 125);
      stopValue = true;
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
      }

      else if ( !leftSensor && rightSensor ) {
        rightAngleLeft = true;
        lastCourse = false;
        
      }

      else if ( leftSensor && !rightSensor ) {
        rightAngleRight = true;
        lastCourse = false;
       
      }

      else if ( !leftSensor && !rightSensor ) {
        digitalWrite(pinLdir, LOW);   
        digitalWrite(pinRdir, LOW); 
        delay(200);  
      }  

    }
    else if(rightAngleLeft){
      digitalWrite(pinLdir, LOW);
      digitalWrite(pinRdir, HIGH);
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
        rightAngleLeft = false;
        lastCourse = true;
        }
    }
    
    else if(rightAngleRight){
      digitalWrite(pinLdir, HIGH);
      digitalWrite(pinRdir, LOW);
      if ( leftSensor && rightSensor ) {
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
        rightAngleRight = false;
        lastCourse = true;
      }
    }
  // Last Course finished
  }
  
  
  // Stop bump
  if(!bumpSensor && stopValue){
    stopBump = true;
    lastCourse = false;
  }
  
  if(stopBump){
    digitalWrite(pinLdir, LOW);   
    digitalWrite(pinRdir, LOW);
    delay(600);
    analogWrite(pinPWM_L, 0);
    analogWrite(pinPWM_R, 0);
  
  }
  
  // Stop bump finished
}