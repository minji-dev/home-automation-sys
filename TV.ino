#include <Arduino.h>

#include <IRremote.h>
int recvPin = 2;
IRrecv irrecv(recvPin);
IRsend irsend;

#include <dht.h>

dht DHT;

#define DHT11_PIN 5

char buffer[128];
int  bufferlen = -1;

void setup() {        
  Serial.begin(115200); //시리얼 통신 초기화
    memset(buffer, 0, 128);
    irrecv.enableIRIn();  // Start the receiver
}
long int scan_ir_data = 0;

void loop() {
  decode_results  results;        // Somewhere to store the results

  if (irrecv.decode(&results)) {  // Grab an IR code
    if (results.decode_type != UNKNOWN) {
      scan_ir_data = results.value;
    }
    irrecv.resume();              // Prepare for the next value
  }
int chk = DHT.read11(DHT11_PIN);

  Serial.print("(");
  Serial.print(scan_ir_data, HEX);
  Serial.print(",");
  Serial.print(DHT.humidity, 1);
  Serial.print(",");
  Serial.print(DHT.temperature, 1);
  Serial.print(")");
delay(1000);
 
  while(Serial.available()){
    char r = Serial.read();
      if(r == '(') {
        bufferlen = 0;
      } else if(r == ')') {
        buffer[bufferlen] = '\0';
        bufferlen = -1;
      } else {
        if(bufferlen>=0) {
          buffer[bufferlen++] = r;
        }
      }
    }
  if(bufferlen == -1) {
    if(buffer[0]>0) {
      int target = atoi(buffer);
      if (target == 1) { /* 1이면 키고 2이면 끄기*/
        irsend.sendLG( 0x8600A0A, 28);
        delay(40);
        irsend.sendLG( 0x8600A0A, 28);
        delay(40);
        irsend.sendLG( 0x8600A0A, 28);
        delay(40);
      } else if (target == 2) {
        irsend.sendLG( 0x86C0051, 28);
        delay(40);
        irsend.sendLG( 0x86C0051, 28);
        delay(40);
        irsend.sendLG( 0x86C0051, 28);
        delay(40);
      }
      memset(buffer, 0, 128);
    }
   
  }
  delay(100);
}  
