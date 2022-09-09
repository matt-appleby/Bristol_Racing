
// Master script

/* todo:

- voltage sensing
- current sensing
*/
 
/*
Pins:

A0  -   Throttle input
A1  -   Thermistor

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



// LCD connections:
// VSS to GND
// VDD to 5V
// RW to GND
// 5V ----10kohms---- V0 ----1kohms---- GND <--- potential divider for V0
// A to 5V via a 10kohm resistor
// K to GND


// pin 7 to be used to detect time start


// Thermistor potential divider wiring:
// V_in ----R_set---- A1 ----Thermistor---- GND


// SD card datalogger:
// MOSI - pin 11
// MISO - pin 12
// SCK - pin 13
// SS - pin 10
// If you can't figure out the other two pins then just give up...

#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
//sd
const int chipSelect = 10;

void setup() {
    // load headers into csv
    String header = "Time, V batt high, V batt low, current, motor temp, throttle";// make a string for assembling the data to log:
    File dataFile = SD.open("datalog.txt", FILE_WRITE);// open the file. note that only one file can be open at a time,
    if (dataFile) {                                 // if the file is available, write to it,     // if the file isn't open doesnt write
        dataFile.println(header);
        dataFile.close();
    }
}

void loop() {
    // Data logging  
    // "Time, V batt high, V batt low, current, motor temp, throttle"
    String dataString = String(chipSelect)+", V1, V2, I,"+ String(chipSelect)+ ", " + String(chipSelect); // make a string for assembling the data to log:
    File dataFile = SD.open("datalog.txt", FILE_WRITE);// open the file. note that only one file can be open at a time,
    if (dataFile) {                                 // if the file is available, write to it,     // if the file isn't open doesnt write
        dataFile.println(dataString);
        dataFile.close();
    }
}
