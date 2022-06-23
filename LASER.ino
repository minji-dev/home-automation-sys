int laser = 6;
 
void setup() {
  // 레이저 모듈이 연결된 핀을 OUTPUT(출력)으로 설정합니다.
  pinMode(laser, OUTPUT);
 
  // 레이저 모듈을 활성화 해줍니다.
  digitalWrite(laser, HIGH);
}
 
void loop() {
}
