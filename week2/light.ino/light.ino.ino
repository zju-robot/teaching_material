int led = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

void loop() {

  digitalWrite(led,1);
  delay(100);
  digitalWrite(led,0);
  delay(1000);
}
