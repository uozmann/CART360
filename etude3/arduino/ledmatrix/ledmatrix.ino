/********************************************************************************
 *  ETUDE THREE extends the 8 bit music machine schema by incorparating an 8 x 8 
 *  LED Matrix. Instead of sequenced 8 bit tones with values between {0...1023}, 
 *  one will instead create 4 unique LED Matrix Patterns that are tightly coupled 
 *  to each corresponding button press on the resistor ladder. The overall premise 
 *  is the same as the music machine - sequencing LED Patterns.
 *  
 *  MODES (4 POSSIBLE MODES)
 *  RESET, PLAY, RECORD, LOOPOP
 *  
 *  RGB LED (REPRESENTS THE CURRENT MODE)
 *  RESET == OFF
 *  PLAY == BLUE
 *  RECORD == GREEN
 *  LOOPOP == _ANYCOLOUR_
 *  
 *  THE RGB VALUES CAN CHANGE DYNAMICALLY VIA PWM CONTROL OF EACH CHANNEL
 */

/******************** SYSTEM VARIABLES FOR ETUDE THREE TO FUNCTION ***********/
/******************** THERE IS NO NEED TO ALTER THE SYSTEM  VARIABLES ********/

/* THIS INCLUDE WILL REFERNECE YOUR LED PATTERNS IN A TWO DIMENSIONAL ARRAY  */
#include "ETUDE-THREE-MATRIX-PATTERNS.h"

/* CONSTANTS */
/* MODE BUTTON */
#define BUTTON_MODE_PIN 2
/* RGB LED PINS */
#define LED_PIN_R 9
#define LED_PIN_G 10
#define LED_PIN_B 11
#define KEY       A0 // BUTTON PRESSED ON RESISTOR LADDER

//Matrix Pin
#define CLK_PIN 6
#define CS_PIN 7
#define DATA_PIN 8
int numDevice = 1;

/* VARIABLES FOR ETUDE THREE TO FUNCTION */
int mode = 0;
int currentBtnState;
int pastBtnState = 0;

/* PATTERN COUNTER */
int countPatterns = 0;
int pastPattern; 
int resistanceValue;
int resistanceBtn = 0;
int patternsIndex = 0;
boolean resistanceBtnOn = false;

/* MAX NUMBER OF PATTERNS IN SEQUENCE ARRAY */
#define MAX_PATTERNS 16

/* AN ARRAY WHICH HOLD PATTERNS SOURCED VIA RECORD MODE AND DISPLAYED VIA LOOPOP MODES */
int patterns[MAX_PATTERNS] = {0}; 

/* PAUSE PERIOD BETWEEN PATTERNS */
int duration = 200; // (CAN BE CHANGED BY PATTERN ATTRIBUTES)

/********************************************************************************/
/********************* SETUP THE MAX72XX LIBRARY (PROVIDED) *********************/
/********************************************************************************/
 /* Extract the contents of the "LedControl.zip" archive and Install the LedControl 
  * Library for the Arduino Enviroment and reference it for use within ETUDE THREE
  * i.e. you must include a library before using it.
  */ 
#include <LedControl.h>// ... ENSURE THAT YOU REFERNECE THE LED MATRIX LIBRARY

/* Initialise an instance of the LedControl Library to control your LED Matrix */
/* MAX72XX CONNECTIONS TO ARDUINO
  * Create a new controler 
  * Params :
  * dataPin     pin on the Arduino where data gets shifted out
  * clockPin    pin for the clock
  * csPin       pin for selecting the device 
  * numDevices  maximum number of devices that can be controled
*/

//LedControl(DATA_PIN, CLK_PIN, CS_PIN, numDevice);
LedControl lc = LedControl(DATA_PIN, CLK_PIN, CS_PIN, numDevice);// CREATE AN INSTANCE OF THE LED MATRIX;

/* VARIABLES FOR LED MATRIX TO FUNCTION */
const unsigned int BRIGHTNESS = 8; // Range = {0 ... 15}

/* REFRESH RATE FOR LED MATRIX DRAWING - CHANGE AS YOU REQUIRE*/
unsigned long REFRESH_RATE_1 = 250; // 40 HZ REFRESH RATE (High Flicker)
unsigned long REFRESH_RATE_2 = 10;  // 100 HZ (Low Flicker)
unsigned long HOLD_PATTERN = 1000;  // 1 HZ 
/* LED MATRIX WAKE ROUTINE - NO NEED TO ALTER FUNCTION */
void wakeUpMAX72XX() {
  lc.shutdown(0, false);
  lc.setIntensity(0, BRIGHTNESS);
  lc.clearDisplay(0);
}

/********************************************************************************/
/* ALGORITHM TO DRAW YOUR PATTERN ROW x ROW CONTAINED WITHIN TWO DIMENSIONAL ARRAY */
void drawPatternByRow(int patternSelect) {
  // CLEAR LED MATRIX
  lc.clearDisplay(0);
  for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, ( splats[patternSelect][i]) );
      delay(REFRESH_RATE_2); // CHANGE TO INCREASE REFRESH RATE.
  }
  delay(HOLD_PATTERN); // CHANGE TO INCREASE REFRESH RATE.
  // CLEAR LED MATRIX
  lc.clearDisplay(0);
}


void drawPatternByRowNew(int patternSelect) {
  int currentPattern = patternSelect;
  // CLEAR LED MATRIX
  lc.clearDisplay(0);
  if (pastPattern > 3) {
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, ( splats[patternSelect][i]) ); //the initial led pattern
      pastPattern = currentPattern;
      delay(REFRESH_RATE_2); // CHANGE TO INCREASE REFRESH RATE.
    } 
  } else if (pastPattern <= 3){
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, ( splatsInverse[patternSelect][i]) ); //the reverse led pattern
      pastPattern = currentPattern +4;
      delay(REFRESH_RATE_2); // CHANGE TO INCREASE REFRESH RATE.
    }
  }
  delay(HOLD_PATTERN); // CHANGE TO INCREASE REFRESH RATE.
  // CLEAR LED MATRIX
  lc.clearDisplay(0);
}

/********************************************************************************/

/* SETUP ROUTINE - NO NEED TO ALTER FUNCTION */
void setup() {
  Serial.begin(57600);
  wakeUpMAX72XX();
  pinMode(BUTTON_MODE_PIN, INPUT);
  pinMode(KEY, INPUT);
  /* EXAMPLE PATTERN FOR DISPLAY ON LED MATRIX, THE PARAMETER VALUE OF ZERO REFERS TO FIRST 
   *  PATTERN IN ETUDE-THREE-MATRIX-PATTERNS ARRAY */ 
  drawPatternByRow(3); // TESTS CORRECT HOOK-UP OF LED MATRIX - MAKE SURE THIS DRAWS TO THE MATRIX
}

/* ETUDE THREE PART ONE - BUILD OUT PHYSICAL CIRCUIT & IMPLEMENT CODE FUNCTION FOR
   FOR setMode(), setRBG() and runMode() - use stubs (function) placeholders where needed */
void loop() {
  setMode();  // CYCLE THROUGH MODES BASED ON BUTTON PRESS
  setRGB();   // SET RGB LED COLOUR BASED ON CURRENT MODE
  runMode();  // ACTUATE SET MODE
}


/* setMode() controls the viability of the modes variable - count */  
void setMode(){
  currentBtnState = digitalRead(BUTTON_MODE_PIN); //get current btn state
  if (currentBtnState != pastBtnState) { //check if btn is pressed
    if (currentBtnState == 0) { //check if btn is released
       mode++;
    } 
  }
  pastBtnState = currentBtnState; //sync past btn press to current btn state
  if (mode > 3) { //make the mode go back to 0
    mode = 0;
  }
  delay(50);
}

/* setRGB() sets the visible colour of the RGB LED based on the current active mode - 
   implement using a switch control structure */ 
void setRGB() {
  switch(mode) {
    case 0: 
      analogWrite(LED_PIN_R, 0);
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_B, 0);
      break;
    case 1:
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_R, 0);
      analogWrite(LED_PIN_B, 255);
      break;
    case 2:
      analogWrite(LED_PIN_B, 0);
      analogWrite(LED_PIN_G, 255);
      analogWrite(LED_PIN_R, 0);
      break;
    case 3:
      analogWrite(LED_PIN_R, 255);
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_B, 0);
      break;
    default: break;
  }
}

/* runMode() determines which action is active based on the outcome of setMode() - 
   implement function logic using a switch control structure */   
void runMode() {
  switch(mode) {
    case 0: 
    reset();
    break; // RESET
    
    case 1: 
    play();
    break; // PLAY
    
    case 2: 
    record();
    break; // RECORD
    
    case 3: 
    loopop();
    break; // PLAYBACK
    
    default: break;   
  }
}

/* reset() - restart the system */ 
void reset() {
  patternsIndex = 0;
}

void resistanceBtnCounter() {
  resistanceValue = analogRead(KEY);
  if (resistanceValue >= 200 && resistanceValue < 260) {
      countPatterns = 0;
      resistanceBtn = 0;
    } else if (resistanceValue >= 330 && resistanceValue < 350) {
      countPatterns = 1;
      resistanceBtn = 1;
    } else if (resistanceValue >= 500 && resistanceValue < 520) {
      countPatterns = 2;
      resistanceBtn = 2;
    } else if (resistanceValue >= 900 && resistanceValue < 1200) {
      countPatterns = 3;
      resistanceBtn = 3;
    } else {
       resistanceBtn = 4;
    }

}
/* play() - capture button press from resistor ladder and produce a pattern on the LED Matrix
- implement function logic using a switch control structure */
void play() {
    resistanceBtnCounter();
    
    switch(resistanceBtn) {
      case 0: /* draw that pattern */ 
      drawPatternByRowNew(countPatterns);
      break;
      
      case 1: 
      /* draw that pattern */ 
      drawPatternByRowNew(countPatterns);
      break;
      
      case 2: 
      /* draw that pattern */ 
      drawPatternByRowNew(countPatterns);
      break;
      
      case 3: 
      /* draw that pattern */ 
      drawPatternByRowNew(countPatterns);
      break;
      
      case 4: 
      /* draw that pattern */ 
      break;
    }
}

/* record() - capture the sequence (MAX 16 PATTERNS) of input patterns from the resistor ladder and store them  
 *  in an array - implement function logic using a switch control structure */
void record() {
  //read btn press 
   resistanceValue = analogRead(KEY);
  if (resistanceValue >= 200 && resistanceValue < 260) {
      resistanceBtnOn = true;
      countPatterns = 0;
      resistanceBtn = 0;
    } else if (resistanceValue >= 330 && resistanceValue < 350) {
      resistanceBtnOn = true;
      countPatterns = 1;
      resistanceBtn = 1;
    } else if (resistanceValue >= 500 && resistanceValue < 520) {
      resistanceBtnOn = true;
      countPatterns = 2;
      resistanceBtn = 2;
    } else if (resistanceValue >= 900 && resistanceValue < 1200) {
      resistanceBtnOn = true;
      countPatterns = 3;
      resistanceBtn = 3;
    } else {
       resistanceBtnOn = false;
    }

  //illuminate the led according to the btn pressed
  switch(resistanceBtn) {
      case 0: /* draw that pattern */ 
      if (patternsIndex < 15 && resistanceBtnOn) {
        drawPatternByRowNew(countPatterns);
      }
      break;
      
      case 1: 
      /* draw that pattern */ 
      if (patternsIndex < 15 && resistanceBtnOn) {
        drawPatternByRowNew(countPatterns);
      }
      break;
      
      case 2: 
      /* draw that pattern */ 
      if (patternsIndex < 15 && resistanceBtnOn) {
        drawPatternByRowNew(countPatterns);
      }
      break;
      
      case 3: 
      /* draw that pattern */ 
      if (patternsIndex < 15 && resistanceBtnOn) {
        drawPatternByRowNew(countPatterns);
      }
      break;

      default:
      break;
    }

    //increase the index for patterns array by 1 each time the btn is pressed
    if (resistanceBtnOn == true && patternsIndex < 15) {
    patternsIndex ++;
    delay(50);
    resistanceBtnOn = false;
    } else if (resistanceBtnOn == true && patternsIndex == 15) { //do not increase the index anymore is it reaches 15
      patternsIndex = 15;
      delay(50);
      resistanceBtnOn = false;
    }
  
    patterns[patternsIndex] = countPatterns;

    
    Serial.print("Index: ");
    Serial.print(patternsIndex);
    Serial.print("Value: ");
    Serial.println(patterns[patternsIndex]);
//    delay(100);
}

/* loopo() - loops over the contents of the patterns array continiously until the mode changes */
void loopop() {
    //for each loop through pattern[]
    for (int i : patterns) {
    int loopingPattern = patterns[i];
    drawPatternByRowNew(loopingPattern);  
    delay(50);

    //check for btn press
    currentBtnState = digitalRead(BUTTON_MODE_PIN);
    if (currentBtnState == 1) {
      mode = -1;
      break;
    delay(50);
    }
    }

}
