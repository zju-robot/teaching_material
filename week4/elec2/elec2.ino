#define ENA 9         //电机驱动设置 ENA, IN1, IN2 为一组 ENB, IN3, IN4 为一组，ENB组未设置
#define IN1 7          
#define IN2 6
#define IN3 3
#define IN4 4
#define ENB 5

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

}
