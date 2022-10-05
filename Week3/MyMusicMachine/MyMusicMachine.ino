//SYSTEM VARIABLES

int mode = 0; //DETERMINE MY STATE
int cnt_notes = 0; //COUNT NOTES IN RECORD MODE

#define LED_PIN_9  9 //BLUE
#define LED_PIN_10 10 //GREEN
#define LED_PIN_11 11 //RED
#define BTN_MODE   2 //BUTTON MODE

#define NOTE_IN    A0 //Resistor ladder input Pin
#define MAX_NOTES  16 //MAX RECORD NOTES
#define BUZZER     3 //SOUND UOTPUT

const int DURATION = 200; //general note time

int notes[MAX_NOTES];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Communicate with the computer
  pinMode(BTN_MODE, INPUT); //capture mode selection
}

void chooseMode() {
  if(digitalRead(BTN_MODE) == HIGH) {
    if(mode < 3) mode ++;
    else mode = 0;
    delay(384); //poormans debounce.
    }
//    Serial.println(mode);
}

void reset(){
  cnt_notes = 0;
}

void live() {
  int _t = analogRead(NOTE_IN);
  Serial.println(_t);
  tone(BUZZER, analogRead(NOTE_IN), DURATION);
  delay(DURATION % 4);
}

void record() {
  if(cnt_notes < MAX_NOTES){
    int _t = analogRead(NOTE_IN);
    if(_t > 8) {
      tone(BUZZER, _t, DURATION);
      delay(DURATION%4);
      notes[cnt_notes];
      cnt_notes++;
    }
  }
}

void play() {
  
}

void selectMode() {
  switch(mode) {
    case 0: 
    reset(); 
    Serial.println("reset");
    break;
    case 1: live(); 
    Serial.println("live");
    break;
    case 2: record(); Serial.println("record");
    break;
    case 3: play(); Serial.println("play");
    break;
    default: Serial.println("default");
  }
}

void setRGB() {
   switch(mode) {
    case 0: 
    analogWrite(LED_PIN_9,255);
    analogWrite(LED_PIN_10,255);
    analogWrite(LED_PIN_11,255);
    break;
    
    case 1: 
    analogWrite(LED_PIN_9,255);
    analogWrite(LED_PIN_10,0);
    analogWrite(LED_PIN_11,0);
    break;
    
    case 2: 
    analogWrite(LED_PIN_9,0);
    analogWrite(LED_PIN_10,0);
    analogWrite(LED_PIN_11,255);
    break;
    
    case 3:
    analogWrite(LED_PIN_9,0);
    analogWrite(LED_PIN_10,255);
    analogWrite(LED_PIN_11,0);
    break;
    
    default: Serial.println("default");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  chooseMode();
  selectMode();
  setRGB();
}
