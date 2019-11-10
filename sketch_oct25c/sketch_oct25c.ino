String myAPIkey = "CVVFSQFEI2VYCU5E"; 
#include <SoftwareSerial.h>
SoftwareSerial esp(2,3);
long startTime = 0;
unsigned char check_connection=0;
unsigned char times_check=0;
int count=0;
void setup()
{
  Serial.begin(9600); 
  esp.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
    esp.print("AT");
    delay(1000);
    esp.println("AT+RST");
    delay(1000);
    esp.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
    delay(1000);
    String data="GET /update?api_key=CVVFSQFEI2VYCU5E&field1=26&field2=20\r\n\r\n";
    esp.println("AT+CIPSEND=66");
    delay(1000);
    esp.println(data);
    Serial.println(count++);
    delay(5000);
}

