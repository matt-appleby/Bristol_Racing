// Connections:
// VSS to GND
// VDD to 5V
// RW to GND
// 5V ----10kohms---- V0 ----1kohms---- GND <--- potential divider for V0
// A to 5V via a 10kohm resistor
// K to GND

// pin 7 to be used to detect time start

// include the library code:

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin

// with the arduino pin number it is connected to

// Pin arrangements:
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int nMinutes = 0, nSeconds = 0;

void setup() {

  Serial.begin(115200);
  
  // set up the LCD's number of columns and rows:

  lcd.begin(16, 2);

  // Print a message to the LCD.

  lcd.print("hello world!");

  delay(1000);

  lcd.clear();

  pinMode(7, INPUT);

}


void loop() {
  
  // set the cursor to column 0, line 1

  // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 0);

  // print the number of seconds since reset:

  // lcd.print(millis() / 1000);
  if ((digitalRead(7)) == HIGH) {//when race button is pressed, take a time and start a infinite loop
    long int t1 = millis();
    while (true) {
      long int t2 = millis();

      // battery - current - motor temp - race time
      //
      // each batteries voltage
      // speed up or slow down


      // battery
      lcd.setCursor(1, 0);
      lcd.print("87.1%");

      // current draw 
      lcd.setCursor(10, 0);
      lcd.print("12.3A");
      
      // motor temp
      lcd.setCursor(1, 1);
      lcd.print("45.6C");

      nSeconds = ((t2 - t1) % 60000) / 1000;
      nMinutes = (t2 - t1) / 60000;

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

      delay(10);
      
    }
  }
}
