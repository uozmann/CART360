#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
//#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 30 // Number of LEDs in left
int brightness = 0;

// Here's how to control the LEDs from any two pins:
#define YELLOW_DATAPIN_1   7
#define GREEN_CLOCKPIN_1   5

#define YELLOW_DATAPIN_2   11
#define GREEN_CLOCKPIN_2   10

Adafruit_DotStar left(NUMPIXELS, YELLOW_DATAPIN_1, GREEN_CLOCKPIN_1, DOTSTAR_BRG);
Adafruit_DotStar right(NUMPIXELS, YELLOW_DATAPIN_2, GREEN_CLOCKPIN_2, DOTSTAR_BRG);

void setup() {

  left.begin(); // Initialize pins for output
  right.begin(); // Initialize pins for output
  left.show();  // Turn all LEDs off ASAP
  right.show();  // Turn all LEDs off 

  // left.setBrightness(128);
  // right.setBrightness(128);
  pinMode(LED_BUILTIN, OUTPUT);
}

// Runs 10 LEDs at a time along left, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)
int cnt = 0;
int state_cnt = 0;
int max_rep;
int brightStep;
int b[8] = {32, 64, 96, 128, 164, 196, 228, 255};
int s[4] = {125, 150,  175, 200};
int b_selector = b[7];
int s_selector = s[0];

void goForward() {
  for(int i = 0; i < NUMPIXELS; i++) {
    left.setPixelColor(head+i, color); // 'On' pixel at head
    left.setPixelColor(tail + i, 0);     // 'Off' pixel at tail
    right.setPixelColor(head + i, color); // 'On' pixel at head
    right.setPixelColor(tail + i, 0);     // 'Off' pixel at tail
    
    left.setBrightness(brightness);
    right.setBrightness(brightness);
    brightness +=8;
    if (brightness >= 255) brightness = 255;

  
    left.show();                     // Refresh left
    right.show();                     // Refresh left
    delay(20);                        // Pause 20 milliseconds (~50 FPS)
    delay(20);                        // Pause 20 milliseconds (~50 FPS)

  if( i >= NUMPIXELS) {         // Increment head index.  Off end of left?
    //head = 0;                       //  Yes, reset head index to start
      Serial.println(head);
    //brightness = 0;
    //flowDirection = false;
    }
  }
  
  //if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
  delay(100);
}


void loop() {
//digitalWrite(LED_BUILTIN, HIGH);
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(100);


//int b[2] = {32, 64, 96, 128, 164, 196, 228, 255};
//int s[4] = {125, 150,  175, 200};
switch(state_cnt % 4) {
  case 0: 
    b_selector = b[7];
    s_selector = s[1];
    cnt = 0;
    max_rep = 4;
    brightStep = 2;
    Serial.println("ZERO");
  break;
  case 1: 
    b_selector = b[5];
    s_selector = s[2];
    cnt = 0;
    max_rep = 3;
    //brightStep = 1;
     //brightness = 0;
     Serial.println("ONE");
  
  break;
  case 2: 
    b_selector = b[2];
    s_selector = s[1];
    cnt = 0;
    max_rep = 4;
    brightStep = -2;
     //brightness = 0;
     Serial.println("TWO");
  break;
  case 3: 
     b_selector = b[3];
    s_selector = s[2];
    cnt = 0;
    max_rep = 4;
    //brightStep = 1;
     //brightness = 0;
     Serial.println("THREE");
  break;
  default: break;
  }
    
  if(cnt < max_rep) {
     theaterChaseForward(left.Color(b_selector,  b_selector, b_selector), s_selector); // White, half brightness
     state_cnt += 1;
  }

}

void theaterChaseForward(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      left.clear();         //   Set all pixels in RAM to 0 (off)
      right.clear();


      
      // 'c' counts up from 'b' to end of left in steps of 3...
      for(int c=b; c<left.numPixels(); c += 3) {
        left.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        right.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }

 
      left.setBrightness(brightness);
      right.setBrightness(brightness);
      brightness += brightStep;
      if (brightness >= 255) brightness = 255; 
      
      left.show(); // Update left with new contents
      right.show();
      delay(wait);  // Pause for a moment
    }
  }
}










void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      left.clear();         //   Set all pixels in RAM to 0 (off)
      right.clear();
      // 'c' counts up from 'b' to end of left in steps of 3...
      for(int c=b; c<left.numPixels(); c += 3) {
        left.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        right.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }


    left.setBrightness(brightness);
    right.setBrightness(brightness);
    brightness +=8;
    if (brightness >= 255) brightness = 255;
    
      left.show(); // Update left with new contents
      right.show();
      delay(wait);  // Pause for a moment
    }
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<left.numPixels(); i++) { // For each pixel in left...
    left.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    left.show();                          //  Update left to match
    delay(wait);                           //  Pause for a moment
  }
}
