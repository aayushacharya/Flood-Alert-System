#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
#define trigPin 8
#define echoPin 5
//#define dataPin 11
RH_ASK rf_driver(1000,4,2,5); 
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //pinMode(dataPin,INPUT);
  rf_driver.init();
}
void loop()
{
  //delay(40);
  long duration,cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration=pulseIn(echoPin,HIGH);
  cm=(duration/2)*0.0343;
  Serial.print("Centimetres: ");
  Serial.print(cm);
  Serial.println();
  if(cm<25)
  {
    const char *msg = "HIGH";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
 
  }
  if(cm<35){
    const char* msg="MED";
    {
     rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent(); 
    }
  }
  if (cm>35)
  {
    const char* msg="LOW";
    {
     rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent(); 
    }
  }
  
  
   delay(250);
}
