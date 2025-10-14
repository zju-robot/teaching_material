int led = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12,OUTPUT);                      //接地
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("hello world");
  for (int a=0; a<=255;a++)                //循环语句，控制PWM亮度的增加
  {
    analogWrite(led,a);
    delay(8);                             //当前亮度级别维持的时间,单位毫秒            
  }
  for (int a=255; a>=0;a--)             //循环语句，控制PWM亮度减小
  {
    analogWrite(led,a);
    delay(8);                             //当前亮度的维持的时间,单位毫秒  
  }
}
