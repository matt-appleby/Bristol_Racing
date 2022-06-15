//Code pinched from: https://forum.arduino.cc/t/rpm-counter-tachometer-with-hall-sensor/621754/3

#define ClockPin 3 // Must be pin 2 or 3

      // My Encoder has 400 Clock pulses per revolution
      // note that 150000.0 = (60 seonds * 1000000 microseconds)microseconds in a minute / 400 pulses in 1 revolution)
      // change the math to get the proper multiplier for RPM for your encoder
     // yours has 4 pulses in 1 revolution
      // note that 15000000.0 = (60 seconds * 1000000 microseconds)microseconds in a minute / 4 pulses in 1 revolution
#define Multiplier 60000000.0// don't forget a decimal place to make this number a floating point number
volatile long count = 0;
volatile int32_t dTime; // Delt in time
volatile bool DataPinVal;

void onPin2CHANGECallBackFunction(){ 
    static uint32_t lTime; // Saved Last Time of Last Pulse
    uint32_t cTime; // Current Time
    cTime = micros(); // Store the time for RPM Calculations
// calculate the DeltaT between pulses
    dTime = cTime - lTime; 
    lTime = cTime;

}


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ClockPin, INPUT);  
//  pinMode(DataPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(ClockPin),onPin2CHANGECallBackFunction,RISING);
}

void loop() {
  float DeltaTime;
  float SpeedInRPM = 0;
  float aveSpeed = 0;
  noInterrupts (); 
// Because when the interrupt occurs the EncoderCounter and SpeedInRPM could be interrupted while they 
// are being used we need to say hold for a split second while we copy these values down. This doesn't keep the 
// interrupt from occurring it just slightly delays it while we maneuver values.
// if we don't do this we could be interrupted in the middle of copying a value and the result get a corrupted value.
  DeltaTime = dTime;
  interrupts ();
  
  //SpeedInRPM = Multiplier / DeltaTime; // Calculate the RPM Switch DeltaT to either positive or negative to represent Forward or reverse RPM
// use the speed and counter values for whatever you need to do.
  static unsigned long SpamTimer;
  SpeedInRPM = (DeltaTime)? Multiplier / DeltaTime: 0.0; // Calculate the RPM Switch DeltaT to either positive or negative to represent Forward or reverse RPM
  if ( (unsigned long)(millis() - SpamTimer) >= (100)) {
    SpamTimer = millis();
    Serial.print(SpeedInRPM , 3);
    Serial.print(" RPM");
    Serial.println();
    
  }
}
