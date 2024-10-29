
#include "Keyboard.h"

unsigned long timeInMilliSec = 0;
unsigned long timeInMilliSecStamp = 0;

unsigned long tapTimeStamp = 0;

int tap = true;

int sensorRight;
int sensorLeft;

int Avalue;
int Dvalue;

int Agap;
int Dgap;
int Wgap;
int Sgap;


int Atap;
int Atimestamp;

int Dtap;
int Dtimestamp;

int Wtap;
int Wtimestamp;

int Stap;
int Stimestamp;



void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("START");

  Keyboard.begin();
}


void loop() {
  sensorLeft = analogRead(A2);
  sensorRight = analogRead(A0);

  int leftValue = 490 + (490 - (sensorLeft - 50));
  int RightValue = sensorRight;

  if(millis() - timeInMilliSecStamp > 10) {
      timeInMilliSecStamp = millis();
      timeInMilliSec = timeInMilliSec + 10;
    };

if((RightValue >= 530 && leftValue >= 530) || (RightValue < 470 && leftValue < 470)){


if(RightValue >= 570 && leftValue >= 570){
  Keyboard.press('w');

  Agap = 0;
  Dgap = 0;
  Wgap = 0;
  Sgap = 0;

} else if (RightValue < 440 && leftValue < 440){
  Keyboard.press('s');

  Agap = 0;
  Dgap = 0;
  Wgap = 0;
  Sgap = 0;

}  else if(RightValue > 530 && leftValue > 530){

  Avalue = RightValue - 530;
  Dvalue = leftValue - 530;

  if(Avalue > Dvalue){
    Agap = Avalue - Dvalue;
    if(Agap < 10) {
      Agap = 0;
    }
    Wgap = Dvalue;
    Dgap = 0;
  } else {
    Dgap = Dvalue - Avalue;
    if(Dgap < 10) {
      Dgap = 0;
    }
    Wgap = Avalue;
    Agap = 0;
  }
  Sgap = 0;
} else if(RightValue < 470 && leftValue < 470){
  Avalue =  470 - RightValue;
  Dvalue = 470 - leftValue;

  if(Avalue > Dvalue){
    Agap = Avalue - Dvalue;
    if(Agap < 10) {
      Agap = 0;
    }
    Sgap = Dvalue;
    Dgap = 0;
  } else {
    Dgap = Dvalue - Avalue;
    if(Dgap < 10) {
      Dgap = 0;
    }
    Sgap = Avalue;
    Agap = 0;
  }
  Wgap = 0;
} else {
  Wgap = 0;
  Keyboard.release('w');
  Sgap = 0;
  Keyboard.release('s');
  Dgap = 0;
  Agap = 0;
}

int gapFaktor = 0.001;

// S 
if(!(Sgap == 0)){
   if(timeInMilliSec - Stimestamp > Sgap * gapFaktor){
      Stap = true;
   }

   if(Stap){
      Keyboard.release('s');
      Keyboard.press('s');

      Stimestamp = timeInMilliSec;

     Stap = false;
    }
  }

// W 
if(!(Wgap == 0)){
  if(timeInMilliSec - Wtimestamp > Wgap * gapFaktor){
    Wtap = true;
  }

  if(Wtap){
    Keyboard.release('w');
    Keyboard.press('w');

    Wtimestamp = timeInMilliSec;

    Wtap = false;
  }
} else {
}

// D
if(!(Dgap == 0)){
  if(timeInMilliSec - Dtimestamp >  Dgap * gapFaktor){
    Dtap = true;
  }

  if(Dtap){
    Keyboard.release('d');
    Keyboard.press('d');

    Dtimestamp = timeInMilliSec;

    Dtap = false;
  }
} else {
  Keyboard.release('d');
}

// A
if(!(Agap == 0)){
  if(timeInMilliSec - Atimestamp > Agap * gapFaktor){
    Atap = true;
  }

  if(Atap){
    Keyboard.release('a');
    Keyboard.press('a');

    Atimestamp = timeInMilliSec;

    Atap = false;
  }
} else {
  Keyboard.release('a');
}

} else {
  
  if (leftValue > 530) {
    // Turn right while driving
    Keyboard.press('d');
    Keyboard.press('w');

    Keyboard.release('a');
    Keyboard.release('s');
  } else if (RightValue > 530) {
    // Turn right backwards
    Keyboard.press('a');
    Keyboard.press('w');

    Keyboard.release('s');
    Keyboard.release('d');
  } else if (RightValue < 470) {
    // Turn left while driving

    Keyboard.press('s');
    Keyboard.press('a');

    Keyboard.release('w');
    Keyboard.release('d');
  } else if (leftValue < 470) {
    // Turn left backwards
    Keyboard.press('d');
    Keyboard.press('s');

    Keyboard.release('w');
    Keyboard.release('a');
  } else {
    Keyboard.releaseAll();
  };
}
    
};