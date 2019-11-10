#include <ThingSpeak.h>
#include<ESP8266WiFi.h>

const int buzzer =  4;
int outputpin= 0;
String apiKey = "SL01KUDPIWL0VHE2";
const char *ssid =  "Xender";     // replace with your wifi ssid and wpa2 key
const char *pass =  "zxcvbnm1";
//Thingspeak information
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup()
{
       Serial.begin(9600);
       pinMode(buzzer, OUTPUT);
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
      ThingSpeak.begin(client);
 
}
void loop()
{
digitalRead(outputpin);
  float sensor_volt;  
  float RS_air; //  Rs in clean air
  float R0;  // R0 in 1000 ppm LPG
  float sensorValue;
 
//Average  
analogRead(outputpin);
    for(int x = 0 ; x < 100 ; x++)
  {    sensorValue = sensorValue + analogRead(outputpin);
  }
  sensorValue = sensorValue/100.0;
//-----------------------------------------------/
 
  sensor_volt = (sensorValue/1024)*3.3;
  RS_air = (5.0-sensor_volt)/sensor_volt; // Depend on RL on yor module
  R0 = RS_air/9.9; // According to MQ9 datasheet table
   
Serial.println(sensorValue);
    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
      {  
         String postStr = apiKey;
         postStr +="&field1=";
         sensorValue=sensorValue;
         postStr += String(sensorValue);
         postStr += "\r\n\r\n";
         String str = "GET https://api.thingspeak.com/update?api_key=";
         str += postStr;
         client.println(str);
      }
    if(sensorValue>600){
    digitalWrite(buzzer,HIGH);
    }
  else{
    digitalWrite(buzzer,LOW);
    }
client.stop();
delay(10000);
}
