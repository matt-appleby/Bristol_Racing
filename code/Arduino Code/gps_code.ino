#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial ss(4, 3); //rx pin3, tx pin 4

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("Testing");
}

void loop() {
    while (ss.available() > 0) {
      gps.encode(ss.read());
    }
    if (gps.location.lat() != 0) {
      Serial.println(millis()+" "+gps.location.lat()+" "+gps.location.lng()+" "+gps.altitude.meters() );
    }
    delay(500);
}}