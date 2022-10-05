int sensorPin = A0;
int value = 0;
#define LED_PIN_3 3
#define PHOTOCELL_PIN_A2 A2
int valuePhotocell = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN_3, OUTPUT);
}

int produceAverage(){
  int temp = 0;
  for(int i = 0; i< 32; i++) {
    temp = temp + analogRead(sensorPin);
  }
  temp = temp/32;
  return temp;
}

void loop() {
  // put your main code here, to run repeatedly:
  value = produceAverage();
  valuePhotocell = analogRead(PHOTOCELL_PIN_A2);
  Serial.println(value, DEC);
  analogWrite(LED_PIN_3, value);
//  digitalWrite(LED_PIN_3, value);
//  delay(200);
}
