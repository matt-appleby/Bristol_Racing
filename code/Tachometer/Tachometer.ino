void setup(){
    Serial.begin(9600);
    pinMode(A1, INPUT);// check pin name
}

void loop(){
    // f=1/T
    // w=2 pi f
    // See how many revs per 5 sec and then compute RPM
    // 500 rpm  => 52.3 rad/s or 8.3 revps
    
    int LoopDuration = 5000;//ms
    int PseudoSamplingRate=100;//Sampling rate assuming that the loop is instantaneous millis
    int starttime = millis();
    int endtime = starttime;

    int store[round(LoopDuration/PseudoSamplingRate)+1] = {};//Plus 1 to ensure no memeory overload

    int loopcount=0;
    while ((endtime - starttime) <=LoopDuration) // do this loop for up to 1000mS
    {
        store[loopcount]=analogRead(A1);
        delay(PseudoSamplingRate);
        loopcount = loopcount+1;
        endtime = millis();
    }

    //post process the data to remove debouncing like stuff
    // I think it would be cool to do an FFT of the signal and extract dominant
    // maybe just dump to terminal
}
