#define PIN_JSUMO_F_D A7
#define PIN_JSUMO_F_I A4

// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

int sensor = 0;

unsigned int JSUMO_der = 0;
unsigned int JSUMO_izq = 0;
unsigned int Rival = 500; // Si no ve nada tira 0 o tende a valores muy cercados. Ej: 17
// Si detecta algo, NO IMPORTA LA DISTANCIA tende a arriba de los 800.

int Pines_JSUMO[2] = {
    PIN_JSUMO_F_D,
    PIN_JSUMO_F_I,
};

void AsignacionPines()
{
  for (int idx = 0; idx < 2; idx++)
  {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }
}

void setup() {
Serial.begin(9600);
AsignacionPines();
}

void loop() {
sensor = analogRead(PIN_JSUMO_F_D);
Serial.println(sensor);
}
