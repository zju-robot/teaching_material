---
marp: true

header: Week4
footer: 浙江大学机器人协会
paginate: true
theme: template1
---

# PWM舵机调试及机械臂组装

![bg opacity:0.3 width:1300](mearm2.png)

---
# 什么是舵机（Servo）

>舵机(Servo)是在程序的控制下，在一定范围内连续改变输出轴角度并保持的电机系统。即舵机只支持在一定角度内转动，无法像普通直流电机按圈转；其主要控制物体的转动并保持（机器人关节、转向机构）。适用于位置角度经常变化的场合。

- 本质是电机
- 无法像电机一样持续转动
- 一般扭矩大，常用于关节姿态控制


---

![width:500](4.png)

![bg right width:500](5.jpg)



---

# 舵机内部结构

![width:800](2.png)

- 变速齿轮组：降低转速，增大扭矩

---
# 舵机关键参数

- 扭矩（kg·cm 或 oz·in）：舵机输出的力矩大小。
- 速度（秒/60°）：舵机转动一定角度所需的时间。
- 电压（V）：舵机的工作电压范围。
- 尺寸（mm）：舵机的长、宽、高。
- 齿轮类型：塑料齿轮、金属齿轮或碳纤维齿轮。
- 重量（g）：舵机的重量。

---
# 舵机分类

![width:1400](8.png)

---
![width:500](9.jpg)

![bg right width:500](10.jpg)

---
# PWM舵机

![width:1200](6.png)

---
![width:900](7.png)

---
# 内训使用的舵机

![bg right width:500](1.jpg)

- PWM舵机
- 大扭矩（造价高昂）

---
![width:500](11.jpg)

- 防堵转（适用于夹爪）


---
# 舵机接线
![width:800](3.png)


---
# 舵机中立位置（重要！）

>舵机的中立位置指舵机旋转角度为0°的位置

**保证舵机臂在中立位置的正确安装，是舵机正常工作的前提！**

---
举个栗子

![width:500](1.jpg)

![bg right width:500](12.png)

---
# 在arduino中用servo库控制舵机

![width:700](13.png)

---

# mearm2.0

![bg opacity:0.3 width:1300](mearm2.png)





---
# 发行说明 v1.0.0

- 来源于一个开源项目mearm
- 对基于扫描的solidworks文件进行修改
- 加入更可靠的夹爪；加入相机


![bg right width:700](14.png)

---
# 实践环节：按照说明书拼装


---
# THANKS FOR YOUR ATTENTION!



