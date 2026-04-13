---
marp: true

header: Week5
footer: 浙江大学机器人协会
paginate: true
---

# 电机驱动与巡线原理
![bg right opacity:0.2 width:900](cover.png)

---
# 电机驱动REVIEW

---
# 常用电机
- 直流减速电机
- 步进电机（脉冲控制）
- 舵机（不适合底盘，适合执行机构，固定到某个位置）
- 直流无刷电机（无人机，转速非常快，扭矩非常大）

---
# 直流减速电机
- 普通电机+减速器
![width:600](image-9.png)
**思考**：减速器作用


---
## 如何选购电机？
**一些参数**
- 电压（如：12V、24V）
- 功率（如：5.6W、10W）
- 扭矩（如：N·m）
- 原电机转速（如：2000r/min）
- 减速比（如：500:1）

---
## 一个实际问题

**关注扭矩、转速**
考虑一只直流减速电机即可驱动车子，圆柱形橡胶车轮在平滑木板上的滚动摩擦系数为 0.05～0.07，取0.06；取车子重量为4千克，车轮半径为3.3cm，需要扭矩为：

<center>

$0.06\times4kg\times9.8m/s^2\times3.3cm=0.0776N·m$

---
# 力矩

**作用在刚体上某点P的力与该点至转轴的垂直距离d（力臂）的乘积**


$M=R\times F$




---
# 转速
取小车的行进速度分别为100厘米/秒，80厘米/秒，60厘米/秒，40厘米/秒时，则电动机转速分别为：
100厘米/秒*60秒/分/(3.14\*6.6厘米)=290转/分
80厘米/秒*60秒/分/(3.14\*6.6厘米)=232转/分
60厘米/秒*60秒/分/(3.14\*6.6厘米)=174转/分
40厘米/秒*60秒/分/(3.14\*6.6厘米)=116转/分

---
于是考虑选择37ZYJ-36ZY型直流减速电机，该电机性能数据如下：
减速比30/1，转速200转/分，扭矩2.5千克·厘米，额定电压为12V，空载电流 ≤350mA,负载电流 ≤1300 mA 。选用该类型的电机后，可以在大大满足扭矩要求的情况下，维持机器人的最大速度为70厘米/秒。

---
# 直流减速电机的控制

- 电机的正反转
- 电机的速度调节
- 电机的速度观测
- 速度反馈控制（PID算法）(next week)

---
![alt text](image.png)

---
![ width:400](image-1.png)

---
![width:400](image-2.png)

---
![width:400](image-3.png)

---
# 怎么实现开关呢？

---
## 三极管

- 晶体三极管
- 场效应管

---
## 晶体三极管

![width:400](image-5.png)

---
# 利用晶体三极管作为开关的H桥
![width:800](image-6.png)

---
![alt text](image-10.png)

---
![width:800](image-4.png)

---
![alt text](image-8.png)

---
![alt text width:900](image-12.png)



---
# 那么什么是L298N
**电机驱动板**
![bg right 100%](image-7.png)

核心：
- L298N 驱动芯片：核心是两个H桥电路
- 78M05 稳压器：当电源小于或等于12V时，内部电路将由稳压器供电，并且5V引脚作为微控制器供电的输出引脚，即：VCC作为7805的输入，5V是7805的输出，从而可以为板载提供5v电压，为外部电路供电使用

---
# 接线图

![width:800](image-11.png)

---

# 巡线原理

---
![width:600](1.png)

---
# 传感器的原理
![width:700](image-14.png)

---
![width:900](image-15.png)

---
# 引脚配置
三个引脚：
- VCC、GND （两端供电） 
- OUT（输出） 
  （为什么只要一个脚输出？）
![alt text](image-17.png)
![bg right width:500](image-23.png)

---
# 电压比较板
- 作用：模拟信号$\Rightarrow$数字信号
  即：传感头输入$\Rightarrow$高/低电平
- 功能元件：运算放大器
  （作为电压比较器使用）
- **关键：调整可变电阻的值以调整传感器灵敏度！**
![bg right width:600](image-22.png)


---
# 巡线逻辑
![width:800](image-18.png)\

---
![width:800](image-19.png)

---
![widh:800](image-20.png)

---
![alt text](image-21.png)

---
# 代码部分

---
# 传感器值读取
```C
int pin_r[4]={13,12,11,10};
void setup() {
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
  Serial.write("---------------\n");delay(100);
}
```


---
# 加权计算偏差
```C
double read_sens()      
{
  int i = 0;
  int sens_r[4] = {-3, -1, 1, 3}; //每个传感器对应权值
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

```
思考：有没有更科学的计算偏差的方式 ---pid算法

---
# 实践环节
- 完成Anycar的拼装与接线（比较板的VCC和GND需接到Arduino Uno对应供电端上）
- **调节四个传感器灵敏度使之能区分黑白**
- 调试小车巡线

---
# THE END
# THANKS FOR YOUR ATTENTION