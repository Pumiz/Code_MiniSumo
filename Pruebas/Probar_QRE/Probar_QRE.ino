//---------------------QRE1113--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

#define PIN_QRE_DERECHO A0
#define PIN_QRE_IZQUIERDO A1

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int BordeTatami = 300;  // Si ve lìnea blanca tende de 200 a 720     Si ve lo negro tende de 800 a 1000

int Pines_QRE[2] = {
  PIN_QRE_DERECHO,
  PIN_QRE_IZQUIERDO,
};

void AsignarPines() {
  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_QRE[idx];
    pinMode(pin, INPUT);
  }
}

void Sensar() {
  QREder = analogRead(PIN_QRE_DERECHO);
  QREizq = analogRead(PIN_QRE_IZQUIERDO);
}

void Borde() {
//Serial.println(QREder);
Serial.println(QREizq);
}

void setup() {
  Serial.begin(9600);
  AsignarPines();
}

void loop() {
  Sensar();
  Borde();
  delay(120);
}