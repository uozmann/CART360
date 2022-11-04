#include <Servo.h>

#define LED_R 11
#define LED_G 10
#define LED_B 9
#define DLED 13

unsigned long sTime;
unsigned long tTime;
unsigned long sTimeR;
unsigned long tTimeR;
int interval = 1000;
int onTimeForLED = 250;
int offTimeForLED = 750;
int onTimeForLEDR = 250;
int offTimeForLEDR = 750;
int ledState = LOW;
int ledStateR = 0;

#define BUTTON 8

#define MOTOR 5
Servo servo;
int angle = 0;

bool btnPressed = false;
int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  servo.attach(MOTOR);
  pinMode(BUTTON, INPUT);
  pinMode(DLED, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);

  sTime = millis();
  sTimeR = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  tTime = millis() - sTime;
  tTimeR = millis() - sTimeR;

  if(ledState == HIGH && tTime >= onTimeForLED) {
    ledState = LOW;
    sTime = millis();
    tTime = 0;
    
  } else if (ledState == LOW && tTime >= offTimeForLED) {
    ledState = HIGH;
    sTime = millis();
    tTime = 0;
  }

  if(ledStateR == 255 && tTimeR >= onTimeForLEDR) {
    ledStateR = 0;
    sTimeR = millis();
    tTimeR = 0;
    
  } else if (ledStateR == 0 && tTimeR >= offTimeForLEDR) {
    ledStateR = 255;
    sTimeR = millis();
    tTimeR = 0;
  }
  digitalWrite(DLED, ledState);
  analogWrite(LED_R, ledStateR);
  analogWrite(LED_G, 255);
  analogWrite(LED_B, 255);

  Serial.println(ledState);
}
