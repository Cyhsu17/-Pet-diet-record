#include <ESP32Servo.h>
Servo myservo;  // 建立SERVO物件


void setup() {
  myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
}

void loop() { 
  myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
  
  
  myservo.write(90);  //旋轉到0度，就是一般所說的歸零
  delay(1000); 
  Serial.print("去"); //前進 逆時針轉 4S
  myservo.write(180); //旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  
  myservo.write(10); //後退 順時針轉 2S
  delay(2000);
  Serial.print("回");
  myservo.write(90); //暫停
}
