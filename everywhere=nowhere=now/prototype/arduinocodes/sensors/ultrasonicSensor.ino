#define ultrasonicEcho 2 //green wire
#define ultrasonicTrig 3 //yellow wire
#define pSensorPin A0 //pressure sensor
#define btnSwitchPin 4 //for soundtrack switching
#define SAMPLES 32

// variables
int ultrasonicDist; 
unsigned long ultrasonicDuration;
int pressureReading = 0;
int _tempUltrasonic = -1;
int _tempPressure = -1;
int soundTrackIndex = 0;

void setup() {
  Serial.begin(9600); // 
  pinMode(ultrasonicTrig, OUTPUT); 
  pinMode(ultrasonicEcho, INPUT); 
  pinMode(btnSwitchPin, INPUT);
  // Serial.println("HELLO WORLD");
}

// void sampling() {
//   //
//   for(int i = 0; i < SAMPLES; i++) {
//     _tempUltrasonic += pulseIn(ultrasonicEcho, HIGH);
//     _tempPressure += analogRead(pSensorPin);
//     // delay(1);
//   }
//   _tempUltrasonic = (_tempUltrasonic / SAMPLES );
//   _tempPressure= (_tempPressure / SAMPLES );
//   ultrasonicDuration = _tempUltrasonic;
//   pressureReading = _tempPressure;
//   _tempUltrasonic =0;
//   _tempPressure =0;
// }

void dataSensing() {
  // Clears the ultrasonicTrig condition
  digitalWrite(ultrasonicTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrig, LOW);
  // Reads the ultrasonicEcho, returns the sound wave travel time in microseconds
  ultrasonicDuration = pulseIn(ultrasonicEcho, HIGH);
  // Calculating the ultrasonicDist
  ultrasonicDist = ultrasonicDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  //Pressure reading
  pressureReading = analogRead(pSensorPin);

  //Switch reading
  soundTrackIndex = digitalRead(btnSwitchPin);

  if(ultrasonicDist <= 30){
  // Serial.println(ultrasonicDist);
  Serial.print(ultrasonicDist); Serial.print(",");
  Serial.print(pressureReading); Serial.print(",");
  Serial.print(soundTrackIndex);
  Serial.println();
  }
}

void loop() {
  dataSensing();
}
