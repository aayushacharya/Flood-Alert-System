#include <LiquidCrystal.h>
#include <RH_ASK.h>
#include <SPI.h>

 
#define buzzerPin 2
//#define ledHigh 3
RH_ASK rf_driver(1000,13,2,5);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

 
void setup()
{
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("WATER LEVEL");
    rf_driver.init();
    pinMode(buzzerPin,OUTPUT);
//    pinMode(ledHigh,OUTPUT);
    Serial.begin(9600);
   
  
    
}

 
void loop()
{
    uint8_t buf[10];
    uint8_t buflen = sizeof(buf);
    String msg;
    lcd.setCursor(0,1); 
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      for(int i=0;i<buflen;i++)
      {
        msg+=(char)buf[i];
      }
      if(msg=="HIGH"){
        pinMode(buzzerPin,OUTPUT);
        //pinMode(ledHigh,OUTPUT);
        digitalWrite(buzzerPin,HIGH);
        
        //lcd code here
        lcd.print("  DANGER");
        //digitalWrite(ledHigh,HIGH);
        Serial.println(msg);
        delay(250);
        lcd.print("        ");
        digitalWrite(buzzerPin,LOW);
        
           
      }
      if(msg=="MED"){
        
        //pinMode(ledHigh,OUTPUT);
        
       
        //lcd code here
        lcd.print("    RISK");
        //digitalWrite(ledHigh,HIGH);
        Serial.println(msg);
        delay(250);
        lcd.print("       ");
           
      }
      if(msg=="LOW"){
        
        //pinMode(ledHigh,OUTPUT);
       
       
        //lcd code here
        lcd.print("    SAFE");
        //digitalWrite(ledHigh,HIGH);
        Serial.println(msg);
        delay(250);   
        lcd.print("        ");
      }
      lcd.print("    ");
      //Serial.println(msg);
      //digitalWrite(ledHigh,LOW);
      //Serial.print("Message Received: ");
      //Serial.println(msg);
      //Serial.println((char*)buf);  
      delay(250);       
    }
    
}
