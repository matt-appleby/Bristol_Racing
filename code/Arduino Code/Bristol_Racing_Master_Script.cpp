// Master script

int PWM_pin = 3;
int throttle_pin = A0;
int PWM_pct = 0;
int throttle_val = 0;
float throttle_val_pct = 0;

void setup() {
  pinMode(PWM_pin, OUTPUT);
}

void loop() {
  throttle_val = analogRead(throttle_pin);
  throttle_val_pct = (float)100 * ((float)throttle_val - (float)164) / (float)712;

  PWM_pct = round((float)255 * (float)throttle_val_pct / (float)100);

  if (PWM_pct >= 254) PWM_pct = 255;
  if (PWM_pct <= 1) PWM_pct = 0;

  analogWrite(PWM_pin, PWM_pct);

}