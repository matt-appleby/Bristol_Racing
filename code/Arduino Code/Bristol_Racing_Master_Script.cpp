// Master script

// Connections:
// VSS to GND
// VDD to 5V
// RW to GND
// 5V ----10kohms---- V0 ----1kohms---- GND <--- potential divider for V0
// A to 5V via a 10kohm resistor
// K to GND
// pin 7 to be used to detect time start

#include <LiquidCrystal.h>

// throttle
int PWM_pin = 3;
int throttle_pin = A0;
int PWM_pct = 0;
int throttle_val = 0;
float throttle_val_pct = 0;

// lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int nMinutes = 0;
int nSeconds = 0;

void setup() {
  pinMode(PWM_pin, OUTPUT);

  Serial.begin(115200);
  lcd.begin(16, 2);// set up the LCD's number of columns and rows:

  //lcd test
  lcd.print("Bristol Racing!");
  delay(1000);
  lcd.clear();
  pinMode(7, INPUT);

}

void loop() {
  //read the throttle value and convert to a 1-255 value
  throttle_val = analogRead(throttle_pin);
  throttle_val_pct = (float)100 * ((float)throttle_val - (float)164) / (float)712;
  PWM_pct = round((float)255 * (float)throttle_val_pct / (float)100);
  if (PWM_pct >= 254) PWM_pct = 255;
  if (PWM_pct <= 1) PWM_pct = 0;

  analogWrite(PWM_pin, PWM_pct);//PWM out

    
}