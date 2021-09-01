int starttime; // 計時器值放入的變數
int count;     //變數值=天秤sum
int i=0;       //計數(0~13) 存到相應的位置
int save[13];  //陣列 存值0~13
float total1=0;   //每筆存值相加
float total2=0;
float avg=0;   //每七天平均相減

void setup() {
 
Serial.begin(9600); //視窗啟用


}

void loop() {
  
     starttime =millis(); //開計時器

     if ((starttime%60)==0){ //每過20s 記錄一次
        float avg1;  //1~7天 sum平均
        float avg2;  //8~14天 sum平均
        save[i]=count; //存檔
        // count=0;  //歸零
       
        
       
       //Serial.println (h[i]) ;
       Serial.print ("count:") ;
       Serial.print (i) ;
       Serial.print ("=") ;
       Serial.println (save[i]) ;
       // Serial.println (count) ;
        i++;
        if(i>13){  //只存0~13(14筆)
          i=0;
        }
          
          for(int x = 0; x<7; x++ ){

            int total1 = total1+save[x];
            avg1=total1/7;
            Serial.print ("total1:") ;
            Serial.println (total1) ;
            Serial.print ("avg1:") ;
            Serial.print (avg1) ;
            
            
            
            
            }

            for(int x = 7; x<14; x++ ){

             int total2 = total2+save[x];
             avg2=total2/7;
            Serial.print ("total2:") ;
            Serial.println (total2) ;
            Serial.print ("avg2:") ;
            Serial.println (avg2) ;
            
           
            
            
            }

            avg=avg1-avg2;
            Serial.print ("avg:") ;
            Serial.println (avg) ;
            


          
          
          }
   
     
   else{
        count = count+1; 
        Serial.print ("count:") ;
        Serial.println (count); 
  
  
  
      } 
  
 
  

}
