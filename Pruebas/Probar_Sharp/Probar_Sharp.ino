
#define PIN_SHARP_DER A5
#define PIN_SHARP_IZQ A6

// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

float RivalSharp = 5.60;  // 60cm, basicamente al otra punta de tatami.

int Pines_Sharps[4] = {
  PIN_SHARP_DER,
  PIN_SHARP_IZQ,
};

void LeerSharp() {
  // Serial.print("Sharp: ");
  // Serial.println(SHARP_der);   //  <------- imprime el valor en centímetros del sensor deseado.
  // Serial.println(" cm");
}

void AsignacionPines() {
  for (int idx = 0; idx < 3; idx++) {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }
}

void setup() {
  Serial.begin(9600);
  AsignacionPines();
}

void loop() {

  int analogValueDer = analogRead(PIN_SHARP_DER);
  float voltageDer = analogValueDer / 1024. * 5;
  float resistenciaDer = 2000 * voltageDer / (1 - voltageDer / 5);
  float distancia_der = pow(50 * 1e3 * pow(10, 0.7) / resistenciaDer, (1 / 0.7));
  distancia_der = distancia_der / 10;

  int analogValue = analogRead(PIN_SHARP_IZQ);
  float voltage = analogValue / 1024. * 5;
  float resistencia = 2000 * voltage / (1 - voltage / 5);
  float distancia_izq = pow(50 * 1e3 * pow(10, 0.7) / resistencia, (1 / 0.7));
  distancia_izq = distancia_izq / 10;

  float SHARP_der = distancia_der;
  float SHARP_izq = distancia_izq;

  //Serial.println(SHARP_der);

  if (SHARP_der < RivalSharp) {
    Serial.println("SHARP: Rival Derecha");
  }

  if (SHARP_izq < RivalSharp) {
    Serial.println("SHARP: Rival Izquierda");
  }
}