#include <Servo.h>

#define LED_R 11
#define LED_G 10
#define LED_B 9
#define DLED 13
#define SPIN 3

class Timer {
  private:
  unsigned long startTime;
  unsigned long timePassed;
  unsigned int onTime;
  unsigned int offTime;
  
  public:
  Timer(int on, int off) {
    onTime = on;
    offTime = off;
  }

void setup() {
    startTime = millis();
}
void updateTimer() {
  timePassed = millis() - startTime;
}

boolean passedIntervalOne() {
  if(timePassed > onTime) {
    startTime = millis();
    timePassed = 0;
    return true;
  } 
    return false;
}

boolean passedIntervalTwo() {
  if(timePassed > offTime) {
    startTime = millis();
    timePassed = 0;
    return true;
  } 
    return false;
}
};

//LEDS
Timer timerOne(5000,100);
Timer timerTwo(350,350);
int stateLEDOne = LOW;
int stateLEDTwo = LOW;
int lightIntensity = 255;
//MOTORS
Timer servoTimerOne(5,0);
Servo servo;
int position = 0;
int speed = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(DLED, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //servo motor attach
  servo.attach(SPIN);

  // setup timers
  servoTimerOne.setup();
  timerOne.setup();
  timerTwo.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  timerOne.updateTimer();
  timerTwo.updateTimer();
  servoTimerOne.updateTimer();
//  lightIntensity -= 1;
  // Enter finite state machine for stepping
  fsmLEDOne(timerOne, stateLEDOne, DLED);
  fsmLEDOne(timerTwo, stateLEDTwo, LED_G);
}

void fsmLEDOne(Timer &t, int &s, int l){
  if( s == HIGH && t.passedIntervalOne()) {
    s = LOW;
    digitalWrite(l, s);
  } else if(s == LOW && t.passedIntervalTwo()) {
    s = HIGH;
    digitalWrite(l,s);
  }
}
