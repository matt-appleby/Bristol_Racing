
//A4 - Battery voltage 1
//A5 - Battery voltage 2

//Connections:
//PD HIGH Vout - A4
//PD LOW Vout - A5

int V_sense_pin_HIGH = A4;
int V_sense_pin_LOW = A5;

int V_sense_HIGH = 0;
int V_sense_LOW = 0;

float V_sense_HIGH_V = 0;
float V_sense_LOW_V = 0;
float V_batt_1 = 0;
float V_batt_2 = 0;


void setup() {

}

void loop() {
  V_sense_HIGH = analogRead(V_sense_pin_HIGH);
  V_sense_LOW = analogRead(V_sense_pin_LOW);


  V_sense_HIGH_V = ((float)5 / (float)255) * (float)5 * (float)V_sense_HIGH;
  V_sense_LOW_V = ((float)5 / (float)255) * (float)2.5 * (float)V_sense_LOW;

  V_batt_1 = V_sense_HIGH_V - V_sense_LOW_V;
  V_batt_2 = V_sense_LOW_V;

  V_batt_1 = (float)V_batt_1 * (float)0.31125;
  V_batt_2 = (float)V_batt_2 * (float)0.362792;

}
