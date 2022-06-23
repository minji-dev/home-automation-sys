#include <Arduino.h>

int sw = 7;
char buffer[128];
int  bufferlen = -1;

void setup() {        
  pinMode(sw, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if(digitalRead(sw) == LOW){
    digitalWrite(13, HIGH);
    Serial.print("(Off)");
  }
  else {
    digitalWrite(13, LOW);
    Serial.print("(On)");
  }
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
    delay(50);
}  
