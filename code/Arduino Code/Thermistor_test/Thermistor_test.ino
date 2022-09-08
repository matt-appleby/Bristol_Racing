
const int R_set = 1000.0, R_0 = 10000.0, V_in = 5.0; // R_set is potential divider resistor, R_0 is thermistor resistance at T_0
const long int T_0 = 298.0, B = 3950.0; // T_0 is temperature in Kelvin that the thermistor resistance is known, B is a thermistor constant

// Thermistor potential divider wiring:
//
// V_in ----R_set---- A0 ----Thermistor---- GND


void setup() {

  Serial.begin(9600);

}

void loop() {

  int V_value = analogRead(A0);

  // Serial.print("V_value: ");
  // Serial.println(V_value);

  float V_out = V_value * (V_in / 1023.0);

  // Serial.print("V_out: ");
  // Serial.println(V_out);

  float R_thermistor = (V_out * R_set) / (V_in - V_out);

  // Serial.print("R_thermistor: ");
  // Serial.println(R_thermistor);

  float T = ((B * T_0) / (T_0 * log(R_thermistor / R_0) + B)) - 273;

  Serial.print("T: ");
  Serial.println(T);

  delay(200);

}
