
#include <ESP32Servo.h>
Servo myservo;  // 建立SERVO物件


void setup() {
  myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
}

void loop() { 
  for(int counter = 0; counter < 6; counter++){  
  myservo.write(0);  //旋轉到0度，就是一般所說的歸零
  delay(1000);
  Serial.print("去");
  myservo.write(180); //旋轉到180度
  delay(1000);
  Serial.print("回");
   }
}
