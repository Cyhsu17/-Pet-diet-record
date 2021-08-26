//引入涵式庫 
#include <WiFi.h>
#include <HX711.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED設定
#define OLED_RESET     21
Adafruit_SSD1306 display(128, 32, &Wire, -1);

// HX711設定
const int DT_PIN = 25;
const int SCK_PIN = 26;
const int scale_factor = -207; //比例參數，從校正程式中取得
HX711 scale;
 

//Thingspeak+網路設定
String apiKey = "7Z46IGZR87OY7FE9";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "00000";     // replace with your wifi ssid and wpa2 key
const char *pass =  "0000";
const char* server = "api.thingspeak.com";
char* resource = "/update?api_key=";

//宣告
float h;  // h=天秤讀到的值
float h2=0; //宣告暫存的變數h2存舊值 新值=h
float h3; //宣告暫存的變數h3 存變化值(h-h2)
float sum=0; //宣告一個變數存總計


/*
float sum1;
float sum2;
float sum3;
float sum4;
float sum5;
float sum6;
float sum7;

float sum8;
float sum9;
float sum10;
float sum11;
float sum12;
float sum13;
float sum14;

*/


 
WiFiClient client;
 
void setup() 
{      //連網路
       Serial.begin(115200);
       delay(10);
       
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

      //啟動oled
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      
      
      //印天秤資訊+啟動
      Serial.println("Initializing the scale");
      scale.begin(DT_PIN, SCK_PIN);
      Serial.println("Before setting up the scale:"); 
      Serial.println(scale.get_units(5), 0);  //未設定比例參數前的數值
      scale.set_scale(scale_factor);       // 設定比例參數
      scale.tare();               // 歸零

      Serial.println("After setting up the scale:"); 

      Serial.println(scale.get_units(5), 0);  //設定比例參數後的數值

      Serial.println("Readings:");  //在這個訊息之前都不要放東西在電子稱上
      


}



 
void loop() 
{
                           
       
      Serial.println(scale.get_units(10), 0); 

       scale.power_down();             // 進入睡眠模式
       delay(1000);
       scale.power_up();               // 結束睡眠模式

       h=scale.get_units(5);
      
      Serial.print("now : ");
      Serial.println(h);
      if((h-h2)==h){
      h3=0;
      h2=h; 
      Serial.print("h3:");
      Serial.println(h3);
      Serial.print("h2:");
      Serial.println(h2);
       
      if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                          {  
                            
                             client.print(String("GET ") + resource + apiKey + "&field1=" + h + "&field2=" +  h3 + //傳現值於頻道1 差值頻道2
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");
  
                             Serial.print("now : ");
                             Serial.print(h);
                             Serial.print(" g, discrepancy: ");
                             Serial.print(h3);
                             Serial.println("g. Send to Thingspeak.");
                             client.stop();
                             Serial.println("Waiting...");
                          }                       
      }
      else{     
      h3=h-h2;
      h2=h;                               //放值進去h2(舊值)
      Serial.print("h2:"); 
      Serial.println(h2);                 //傳變化值 
      
      if(-h3>2)                     // 減少超過2g傳值到THINGSPEAK  (變化超過0.2)
      {   Serial.print("h3:"); 
          Serial.println(h3);  
          sum=h3+sum;               //累計重量變化值
            
          if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com    //連線到THINGSPEAK
                          {  
                            
                             client.print(String("GET ") + resource + apiKey + "&field1=" + h + "&field2=" +  h3 + "&field3=" + sum  + //傳現值於頻道1 差值頻道2 總計傳頻道3
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");
  
                             Serial.print("now : ");
                             Serial.print(h);
                             Serial.print(" g, discrepancy: ");
                             Serial.print(h3);
                             Serial.println("g. Send to Thingspeak.");
                             Serial.print("sum:"); 
                             Serial.println(sum);
                             float displaysum =abs(sum);  //負值轉正值
                             

                             
                             client.stop();
                             Serial.println("Waiting...");
                             

                             // OLED Display 
                              display.clearDisplay();   
                              display.setTextSize(1);
                              display.setTextColor(WHITE);
                              display.setCursor(0,8); display.println("TODAY EAT");
                              display.setCursor(0,24); display.println(displaysum);
                              display.setCursor(28,24); display.println("g");
                              display.display();
                              delay(1000); 
                          }
                       
      
      
      
      }
        
                     

      
        }                              
                              
      

                 // thingspeak needs minimum 15 sec delay between updates
                   delay(15000); 
        
 
        }
                  
 
                       
          
  
