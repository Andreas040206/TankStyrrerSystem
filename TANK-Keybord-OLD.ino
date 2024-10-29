
#include "Keyboard.h"

int Red_button = "D5";

unsigned long timeInMilliSec = 0;
unsigned long timeInMilliSecStamp = 0;

unsigned long tapTimeStamp = 0;

int tap = true;

int sensorRight;
int sensorLeft;



void setup() {
  
  pinMode(Red_button, INPUT);

  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("START");

  Keyboard.begin();
}


void tapping(){
  if(timeInMilliSec - tapTimeStamp > ((sensorRight - 540) * 10)){
    tap = true;
  };
  
  if(tap){
    
    Serial.println("RELEASING-----------");

    // Set timestamp
    tapTimeStamp = timeInMilliSec;

    // No tapping anymore
    tap = false;
  }

  if(!tap){
     Serial.println("Holding");
  }
}


void loop() {


  int btn = digitalRead(Red_button);


  sensorLeft = analogRead(A2);
  sensorRight = analogRead(A0);

  int leftValue;
  int rightValue;

  if(millis() - timeInMilliSecStamp > 10) {
      timeInMilliSecStamp = millis();
      timeInMilliSec = timeInMilliSec + 10;
    };



  if (sensorLeft < 470) {
    leftValue = 1;
  } else if (sensorLeft > 560) {
    leftValue = -1;
  } else {
    leftValue = 0;
  }

  if (sensorRight < 450) {
    rightValue = -1;
  } else if (sensorRight > 540) {
    rightValue = 1;
  } else {
    rightValue = 0;
  }



  if (leftValue > 0 && rightValue > 0) {
    // Drive forward
    Keyboard.press('w');

    Keyboard.release('s');
    Keyboard.release('a');
    Keyboard.release('d');
  } else if (leftValue < 0 && rightValue < 0) {
    // Drive backwards
    Keyboard.press('s');

    Keyboard.release('w');
    Keyboard.release('a');
    Keyboard.release('d');
  } else if (leftValue > 0 && rightValue < 0) {
    // Turn tank righaround
    Keyboard.press('d');

    Keyboard.release('w');
    Keyboard.release('a');
    Keyboard.release('s');
  } else if (leftValue < 0 && rightValue > 0) {
    // Turn tank leftaround
    Keyboard.press('a');

    Keyboard.release('w');
    Keyboard.release('s');
    Keyboard.release('d');
  } else if (leftValue > 0) {
    // Turn right while driving
    Keyboard.press('d');
    Keyboard.press('w');

    Keyboard.release('a');
    Keyboard.release('s');
  } else if (leftValue < 0) {
    // Turn right backwards
    Keyboard.press('d');
    Keyboard.press('s');

    Keyboard.release('w');
    Keyboard.release('a');
  } else if (rightValue > 0) {
    // Turn left while driving

    Keyboard.press('w');
    Keyboard.press('a');

    Keyboard.release('s');
    Keyboard.release('d');
  } else if (rightValue < 0) {
    // Turn left backwards
    Keyboard.press('a');
    Keyboard.press('s');

    Keyboard.release('w');
    Keyboard.release('d');
  } else {
    Keyboard.releaseAll();
  };

int buttenPressed = digitalRead(Red_button);
if(buttenPressed == 1){
  Serial.println("BAAANG");
} else{
  Serial.println(buttenPressed);
};



  //PRINTIN SHIT -------------------------------------------

  /*
  if( sensorValue1 < 490  sensorValue1 > 510 && sensorValue1 < 800) {
    if(!(sensorValue2 < 505  sensorValue2 > 527)){
    Serial.println("x: " + String(sensorValue1) );
    } else {
      Serial.print("x: " + String(sensorValue1) + " " );
    }
  }


  if( sensorValue2 < 505 sensorValue2 > 527) {

    if(!( sensorValue1 < 590  sensorValue1 > 510 )){
    Serial.println(" . . . y: " + String(sensorValue2));
    } else {
      Serial.println("y: " + String(sensorValue2));
    }
  }


  if(btn == 1) {
    Keyboard.press('t');
    Serial.println(" . . BANG");
    //Keyboard.releaseAll();
  }

  if(sensorValue1 > 1015 ) {
    Serial.println(" . . ZOOM");

  }
  */

  Serial.print(sensorRight);
  Serial.print(" ");
  Serial.println(sensorLeft);


  delay(5);
};