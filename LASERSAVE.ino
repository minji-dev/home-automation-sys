#include <Arduino.h>

const int LIMITVALUE = 450;     
int cds = A0;
int val;
char buffer[128];
int  bufferlen = -1;

void setup() {        
  pinMode(cds, INPUT);
  Serial.begin(115200); //시리얼 통신 초기화
}

void loop() {
  val = analogRead(cds); //조도센서로부터 값을 읽어들인다
  Serial.print("(");
  Serial.print(val); //시리얼 모니터에 출력
  Serial.print(")");
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
  delay(100);
}
