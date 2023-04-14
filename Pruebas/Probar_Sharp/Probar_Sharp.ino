
#define PIN_SHARP_DER A5
#define PIN_SHARP_IZQ A6

// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

unsigned int SHARP_der = 0;
unsigned int SHARP_izq = 0;
unsigned int RivalSharp = 60; // 60cm, basicamente al otra punta de tatami.

int Pines_Sharps[4] = {
    PIN_SHARP_DER,
    PIN_SHARP_IZQ,
};

void LeerSharp(){
  int analogValueDer = analogRead(PIN_SHARP_DER);
  float voltageDer = analogValueDer / 1024. * 5;
  float resistenciaDer = 2000 * voltageDer / (1 - voltageDer / 5);
  float SHARP_der = pow(50 * 1e3 * pow(10, 0.7) / resistenciaDer, (1 / 0.7));
  SHARP_der = SHARP_der / 10;

  int analogValue = analogRead(PIN_SHARP_IZQ);
  float voltage = analogValue / 1024. * 5;
  float resistencia = 2000 * voltage / (1 - voltage / 5);
  float SHARP_izq = pow(50 * 1e3 * pow(10, 0.7) / resistencia, (1 / 0.7));
  SHARP_izq = SHARP_izq / 10;

  Serial.print("Sharp: ");    
  Serial.print(SHARP_izq);   //  <------- imprime el valor en centímetros del sensor deseado. 
  Serial.println(" cm");    
}

void AsignacionPines(){
  for (int idx = 0; idx < 3; idx++)
  {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }
}

void setup(){
Serial.begin(9600);
AsignacionPines();
}

void loop(){
LeerSharp();
}                                                                                                                                                                       