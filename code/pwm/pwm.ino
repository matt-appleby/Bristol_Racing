void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(6, 127);//0=0%, 127=50%, 255=50%
  delay(5);
}
