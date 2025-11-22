#define LED 11

void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LED,10);
  delay(1000);
}
