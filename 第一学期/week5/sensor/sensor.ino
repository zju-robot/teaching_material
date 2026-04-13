#define R1 13
#define R2 12
#define R3 11
#define R4 10

int pin_r[4]={13,12,11,10};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R1,INPUT);
  pinMode(R2,INPUT);
  pinMode(R3,INPUT);
  pinMode(R4,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sens[4] = {0,0,0,0};
  for(int i=0;i<4;i++)
  {
  sens[i] = digitalRead(pin_r[i]);
  }
  for(int i=0;i<4;i++)
  {
  // Serial.println("第%d个",i+1);
  Serial.println(sens[i]);
  }
  Serial.write("---------------\n");
  delay(100);
}