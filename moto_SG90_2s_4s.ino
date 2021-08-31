#include <ThingSpeak.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32Servo.h>
Servo myservo;  // 建立SERVO物件

// Network Parameters
const char* ssid     = "ittraining401";
const char* password = "itstudent";

// ThingSpeak information
char* server = "api.thingspeak.com";
unsigned long channelID = 1485980;
char* readAPIKey = "NVDDOQG9QXK4PNHU";
unsigned int dataFieldOne = 3; 

 
String apiKey = "JGPCK8ZD7I1WKHYH";     //  Enter your Write API key from ThingSpeak
char* resource = "/update?api_key=";


// Global variables
// These constants are device specific.  You need to get them from the manufacturer or determine them yourself.
float aConst = 2.25E-02 ;

WiFiClient client;

int connectWiFi() {
  WiFi.begin( ssid, password );
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println( "Connected" );
  ThingSpeak.begin( client );
}


void setup() {

  Serial.begin(115200);
  Serial.println("Start");
  connectWiFi();
   
}

void loop() {

  delay(10000);
  Serial.println("不要等啦...");
  //reading data from thing speak
  aConst = readTSData( channelID, dataFieldOne );
  Serial.println(aConst);
  
  if(aConst==888)
  {    
  
  
  //貼馬達CODE

  myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
  
//1
  myservo.write(90);  //旋轉到0度，就是一般所說的歸零
  delay(1000); 
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//2
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//3
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//4
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//5
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//6
 Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//7
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//8
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");


//變回555
    int h = 555;
    myservo.write(90);
    
    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                          {  
                            
                             client.print(String("GET ") + resource + apiKey + "&field3=" + h +    
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");
  
                          }
      
    
   }
          
 
 


}


float readTSData( long TSChannel, unsigned int TSField ) {

  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " 跑函式Data read from ThingSpeak: " + String( data ) );
  return data;

 
  


}
