void setup() {
  pinMode(6, OUTPUT);
}

void loop() {
  analogWrite(6, 127);//0=0%, 127=50%, 255=50%
  delay(5);
}
