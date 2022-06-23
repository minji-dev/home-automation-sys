#include <Arduino.h>

#include <IRremote.h>
int recvPin = 2;
IRrecv irrecv(recvPin);
IRsend irsend;



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
      if (target == 1) { /* 전원버튼을 누름 */
        irsend.sendNEC(0x20DF10EF, 32); //IR_TVPOWER 
        delay(40);
      irsend.sendSony(0x9CA800FF, 32); // IR_STBPOWER 
        delay(40);
        
      } else if (target == 2) {
        delay(40);
      }
      memset(buffer, 0, 128);
    }
   
  }
  delay(100);
}  
