// Master script

/*
Pins:

A0  -   Throttle input
A1
A2
A3
A4 - Battery voltage 1
A5 - Battery voltage 2


1   -   
2   -  
3   -  
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
// to lCD connections:
// VSS to GND
// VDD to 5V
// RW to GND
// 5V ----10kohms---- V0 ----1kohms---- GND <--- potential divider for V0
// A to 5V via a 10kohm resistor
// K to GND

//V sense Connections:
//PD HIGH Vout - A4
//PD LOW Vout - A5

#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

// throttle
int throttle_pin = A0;
int throttle_val = 0;
float throttle_val_pct = 0;

// voltage sense
int V_sense_pin_HIGH = A4;
int V_sense_pin_LOW = A5;
int V_sense_HIGH = 0;
int V_sense_LOW = 0;
float V_sense_HIGH_V = 0;
float V_sense_LOW_V = 0;
float V_batt_1 = 0;
float V_batt_2 = 0;

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

//sd
const int chipSelect = 10;

//
int race_time = 0;
int race_percentage = 0;
int battery_percentage=99;

void setup() {
    Serial.begin(115200);
    lcd.begin(16, 2);// set up the LCD's number of columns and rows:

    //lcd test
    lcd.print("Bristol Racing!");
    delay(6000);
    lcd.clear();
    pinMode(2, INPUT);

    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
    }

    Serial.println("card initialized.");
    // load headers into csv
    String header = "Time, V batt high, V batt low, throttle";// make a string for assembling the data to log:
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

    // time
    if (race_time==0 && throttle_val_pct>80){
        race_time=millis();
    }
    long int time = millis();
    nSeconds = ((time-race_time) % 60000) / 1000;
    nMinutes = (time-race_time) / 60000;
    lcd.setCursor(10, 0);
    if (nMinutes <= 9) {
        lcd.print("0");
    }
    lcd.print(nMinutes);
    lcd.print(":");
    if (nSeconds <= 9) {
        lcd.print("0");
    }
    lcd.print(nSeconds);

    // Data logging  
    // "Time, V batt high, V batt low, current, motor temp, throttle"
    String dataString = String(time) + V_batt_1 + V_batt_2 + throttle_val; // make a string for assembling the data to log:
    File dataFile = SD.open("datalog.txt", FILE_WRITE);// open the file. note that only one file can be open at a time,
    if (dataFile) {                                 // if the file is available, write to it,     // if the file isn't open doesnt write
        dataFile.println(dataString);
        dataFile.close();
    }

    //output to lcd
    // battery - current - motor temp - race time
    // want: each batteries voltage and speed up or slow down

    // voltage sense
    V_sense_HIGH = analogRead(V_sense_pin_HIGH);
    V_sense_LOW = analogRead(V_sense_pin_LOW);
    V_sense_HIGH_V = ((float)5 / (float)255) * (float)5 * (float)V_sense_HIGH;
    V_sense_LOW_V = ((float)5 / (float)255) * (float)2.5 * (float)V_sense_LOW;
    V_batt_1 = V_sense_HIGH_V - V_sense_LOW_V;
    V_batt_2 = V_sense_LOW_V;
    V_batt_1 = (float)V_batt_1 * (float)0.31125;
    V_batt_2 = (float)V_batt_2 * (float)0.362792;

    //V_batt_1=float(int(10*V_batt_1))/10;
    //V_batt_2=float(int(10*V_batt_2))/10;

    lcd.setCursor(1, 0);
    lcd.print(V_batt_1);
    lcd.setCursor(1, 1);
    lcd.print(V_batt_2);
    
    race_percentage=int(nMinutes*100/60);
    battery_percentage=int(((V_batt_1+V_batt_2)-21)*100/(24-21));// (V_total-V_min)/(V_max-M_min)
    lcd.setCursor(10, 1);
    if (race_percentage > battery_percentage){
        lcd.print("+++");
    }
    else {
        lcd.print("---");
    }
    delay(500);
}
