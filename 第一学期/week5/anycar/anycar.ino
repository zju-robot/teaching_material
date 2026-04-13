/* 
* file: anycar.ino
* 本代码仅提供一个巡线的代码框架
* 具体数值可以自行更改
* 框架也可以 (>_<)
*/

#define ENA 9         //电机驱动设置 ENA, IN1, IN2 为一组 ENB, IN3, IN4 为一组
#define IN1 7          
#define IN2 6
#define IN3 3
#define IN4 4
#define ENB 5

#define RIN1 13          //四路循迹传感器引脚，根据自己情况设置
#define RIN2 12
#define RIN3 11
#define RIN4 10

#define DEFSPD 100      //默认速度  需要根据自己实际情况调整大小
#define ADPSPD 50       //调整速度  需要根据自己实际情况调整大小

int pin_r[4]={13,12,11,10};    //四路循迹传感器引脚
int sens[4] = {0, 0, 0, 0};     //四个传感器的读取值
int sens_r[4] = {-3, -1, 1, 3}; //每个传感器对应权值

void setup() {
    // 电机引脚驱动设置，ENB组未设置
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);       

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);
    //四路循迹引脚设置
  pinMode(RIN1, INPUT);
  pinMode(RIN2, INPUT);
  pinMode(RIN3, INPUT);
  pinMode(RIN4, INPUT);  
}
/*
* 误差计算函数
* 功能：根据权值公式以及传感器读数，计算误差
* 返回值：小车与黑线的偏离值，double类型
* 无传入参数
*/
double read_sens()      
{
  int i = 0;
  for (i = 0; i < 4; i++) {     //读取每个传感器的值
    sens[i] = digitalRead(pin_r[i]);
  }
  // 计算误差
  double error = 0.0;
  for (i = 0; i < 4; i++) {
    error += sens_r[i] * sens[i];   //加权求和
  }
  error /= 4;                       //求均值
  return error;
}

void loop() {
  // put your main code here, to run repeatedly:
  double error = 0;
  error = read_sens();              //获取误差
  int SpdA, SpdB;
  SpdA = DEFSPD + error * ADPSPD;   //根据误差确定A，B电机输出量
  SpdB = DEFSPD - error * ADPSPD;
  SpdA = constrain(SpdA, 0, 255);   //constrain函数，将变量SpdA的值限制在0~255之间
  SpdB = constrain(SpdB, 0, 255);  //若SpdA > 255，返回255；若SpdA < 0，返回0
  analogWrite(ENA, SpdA);           //输出，控制电机
  analogWrite(ENB, SpdB);
}

