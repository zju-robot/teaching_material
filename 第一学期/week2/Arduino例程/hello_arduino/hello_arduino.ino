void setup() {
  Serial.begin(9600);      // 初始化串口，波特率 9600
}

void loop() {
  Serial.println("hello arduino");  // 发送字符串并换行
  delay(1000);                      // 等待 1 秒
}