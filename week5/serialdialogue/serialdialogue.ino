#define START 126 //~
#define END 33 //!
#define SID 0
#define MID_HAPPY 0
#define MID_SAD 1
#define MID_ANGRY 2
#define MID_AMBIVALENT 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.print(START);
  Serial.print(SID);
  Serial.print(MID_HAPPY);
  Serial.print("HELLO WORLD, FIRST MESSAGE");
  Serial.print(END);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
   Serial.print((char)Serial.read());
  }
}
