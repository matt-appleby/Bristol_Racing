// Master script

/* todo:

- voltage sensing
- current sensing
*/
 
/*
Pins:

A0  -   Throttle input

1   -   
2   -   to be used to detect time start
3   -   PWM output
4   -   d4      LCD      
5   -   d5      LCD
6   -   d6      LCD
7   -   d7      LCD
8   -   rs      LCD
9   -   en      LCD
10  -   SS      SD card
11  -   MOSI    SD card
12  -   MISO    SD card
13  -   SCK     SD card


*/



// Connections:
// VSS to GND
// VDD to 5V
// RW to GND
// 5V ----10kohms---- V0 ----1kohms---- GND <--- potential divider for V0
// A to 5V via a 10kohm resistor
// K to GND
// pin 7 to be used to detect time start
// Thermistor potential divider wiring:
// V_in ----R_set---- A1 ----Thermistor---- GND

// SD card datalogger
// MOSI - pin 11
// MISO - pin 12
// SCK - pin 13
// SS - pin 10
// If you can't figure out the other two pins then just give up...

#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

// throttle
int PWM_pin = 3;
int throttle_pin = A0;
int PWM_pct = 0;
int throttle_val = 0;
float throttle_val_pct = 0;

// lcd
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int rs = 8;
const int en = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int nMinutes = 0;
int nSeconds = 0;

//thermistor
const int R_set = 1000.0;// R_set is potential divider resistor,
const int R_0 = 10000.0;//  R_0 is thermistor resistance at T_0
const int V_in = 5.0;
const long int T_0 = 298.0; // T_0 is temperature in Kelvin that the thermistor resistance is known,
const long int B = 3950.0;//B is a thermistor constant 

//sd
const int chipSelect = 10;

void setup() {
    pinMode(PWM_pin, OUTPUT);

    Serial.begin(115200);
    lcd.begin(16, 2);// set up the LCD's number of columns and rows:

    //lcd test
    lcd.print("Bristol Racing!");
    delay(1000);
    lcd.clear();
    pinMode(2, INPUT);

    // load headers into csv
    String header = "Time, V batt high, V batt low, current, motor temp, throttle";// make a string for assembling the data to log:
    File dataFile = SD.open("datalog.txt", FILE_WRITE);// open the file. note that only one file can be open at a time,
    if (dataFile) {                                 // if the file is available, write to it,     // if the file isn't open doesnt write
        dataFile.println(header);
        dataFile.close();
    }
}

void loop() {
    //read the throttle value and convert to a 1-255 value
    throttle_val = analogRead(throttle_pin);
    throttle_val_pct = (float)100 * ((float)throttle_val - (float)164) / (float)712;
    PWM_pct = round((float)255 * (float)throttle_val_pct / (float)100);
    if (PWM_pct >= 254) PWM_pct = 255;
    if (PWM_pct <= 1) PWM_pct = 0;

    analogWrite(PWM_pin, PWM_pct);//PWM out

    // time
    // (im deleting race time for now, add later)
    long int time = millis();
    nSeconds = ((time) % 60000) / 1000;
    nMinutes = (time) / 60000;
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

    // thermistor code
    int V_value = analogRead(A1);
    float V_out = V_value * (V_in / 1023.0);
    float R_thermistor = (V_out * R_set) / (V_in - V_out);
    float T = ((B * T_0) / (T_0 * log(R_thermistor / R_0) + B)) - 273;//Motor temp

    // Data logging  
    // "Time, V batt high, V batt low, current, motor temp, throttle"
    String dataString = time+", V1, V2, I,"+ T + ", " + PWM_pct; // make a string for assembling the data to log:
    File dataFile = SD.open("datalog.txt", FILE_WRITE);// open the file. note that only one file can be open at a time,
    if (dataFile) {                                 // if the file is available, write to it,     // if the file isn't open doesnt write
        dataFile.println(dataString);
        dataFile.close();
    }

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
    lcd.print(T);
}