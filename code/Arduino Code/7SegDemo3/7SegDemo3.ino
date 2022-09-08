//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,13,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}


//////////////////////////////////

//Numbers to display on each seven segment display
// numb1 = number to display on left 7seg 
// numb2 =  number to display on right 7seg 

float numb1 = 102;
float numb2 = 0.001;

//////////////////////////////////

String seg1digs=""; 
bool seg1dig1dec = false;
bool seg1dig2dec = false;
bool seg1dig3dec = false;
bool seg1dig4dec = false;
String seg2digs=""; 
bool seg2dig1dec = false;
bool seg2dig2dec = false;
bool seg2dig3dec = false;
bool seg2dig4dec = false;

void displayNumber(float numb1, float numb2) {
seg1dig1dec = false;
seg1dig2dec = false;
seg1dig3dec = false;
seg1dig4dec = false;
seg2dig1dec = false;
seg2dig2dec = false;
seg2dig3dec = false;
seg2dig4dec = false;

seg1digs=String(numb1,4);
int decimalPlace1 = seg1digs.indexOf('.') + 1;
if (decimalPlace1 == 2) seg1dig1dec = true;
else if (decimalPlace1 == 3) seg1dig2dec = true;
else if (decimalPlace1 == 4) seg1dig3dec = true;
else if (decimalPlace1 == 5) seg1dig4dec = true;
seg1digs.remove((decimalPlace1-1),1);

seg2digs=String(numb2,4);
int decimalPlace2 = seg2digs.indexOf('.') + 1;
if (decimalPlace2 == 2) seg2dig1dec = true;
else if (decimalPlace2 == 3) seg2dig2dec = true;
else if (decimalPlace2 == 4) seg2dig3dec = true;
else if (decimalPlace2 == 5) seg2dig4dec = true;
seg2digs.remove((decimalPlace2-1),1);

int str_len1 = seg1digs.length() + 1; 
char seg1digs_array[str_len1];
seg1digs.toCharArray(seg1digs_array, str_len1);

int str_len2 = seg2digs.length() + 1; 
char seg2digs_array[str_len2];
seg2digs.toCharArray(seg2digs_array, str_len2);

int seg1dig1 = seg1digs[0] -'0';
int seg1dig2 = seg1digs[1] -'0';
int seg1dig3 = seg1digs[2] -'0';
int seg1dig4 = seg1digs[3] -'0';
int seg2dig1 = seg2digs[0] -'0';
int seg2dig2 = seg2digs[1] -'0';
int seg2dig3 = seg2digs[2] -'0';
int seg2dig4 = seg2digs[3] -'0';

lc.setDigit(0,7,seg1dig1,seg1dig1dec);
lc.setDigit(0,6,seg1dig2,seg1dig2dec);
lc.setDigit(0,5,seg1dig3,seg1dig3dec);
lc.setDigit(0,4,seg1dig4,seg1dig4dec);
lc.setDigit(0,3,seg2dig1,seg2dig1dec);
lc.setDigit(0,2,seg2dig2,seg2dig2dec);
lc.setDigit(0,1,seg2dig3,seg2dig3dec);
lc.setDigit(0,0,seg2dig4,seg2dig4dec);

delay(delaytime);
//  lc.clearDisplay(0);
//  delay(delaytime); 
}

void loop() { 
  numb1=numb1-0.01;
  numb2=numb2+0.001;
  displayNumber(numb1, numb2);
}
