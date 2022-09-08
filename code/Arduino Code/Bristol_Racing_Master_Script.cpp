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

    
    //output to lcd
    // battery - current - motor temp - race time
    // want: each batteries voltage and speed up or slow down

    // battery [PWM for now]
    lcd.setCursor(1, 0);
    lcd.print(PWM_pct);

    // current draw 
    lcd.setCursor(10, 0);
    lcd.print("12.3A");
    
    // motor temp
    lcd.setCursor(1, 1);
    lcd.print("45.6C");

    // im deleting race time for now, add later
    long int t2 = millis();
    nSeconds = ((t2) % 60000) / 1000;
    nMinutes = (t2) / 60000;
    lcd.setCursor(10, 1);
    if (nMinutes <= 9) {
    lcd.print("0");
    }
    lcd.print(nMinutes);
    lcd.print(":");
    if (nSeconds <= 9) {
    lcd.print("0");
    }
    lcd.print(nSeconds);
}