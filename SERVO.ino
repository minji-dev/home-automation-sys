#include <Arduino.h>
#include <Servo.h>
 
Servo microServo;
const int servoPin = 7;
int cds = A0;
int val;
char buffer[128];
int  bufferlen = -1;

void setup() {        
  microServo.attach(servoPin); //서보모터 초기화
  pinMode(cds, INPUT);
  microServo.write(85); //원래 기본 각도 (가로)
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
  if(bufferlen == -1) { 
    int target = atoi(buffer);
    if(target < 0) target = 0;
    if(target > 170) target = 170;
    microServo.write(target);
  }
  delay(100);
}  
