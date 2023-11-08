//------------------GLOBALES---------------------
#include "Define.h"
#include <Arduino.h>
#include <Motores.h>
#include <Sharp.h>

#define DEBUG_PULSADOR 1 // con DEBUG en 0 NO muestra SerialPrint´s
#define DEBUG_ACCIONES 0 // Debug para saber en que if cae en cada estrategia.
#define DEBUG_CASOS 0    // Debug despues de los 5 segundos.
#define DEBUG_ULTRASONIDO 0
#define DEBUG_DIP 0
#define DEBUG_SHARP 0
#define ENEABLE_QRE 0 // 1 permitido, 0 no permitido

int dipConbinedState;
const int numLecturas = 10;
int sumaLecturas = 0;

const int Pines_Salida[2] = {PIN_TRIG, PIN_LED};

const int Pines_Entrada[4] = {PIN_ECHO, PIN_PULSADOR, PIN_DIP_1, PIN_DIP_2};

//-------------------MOTORES--------------------
Motores MotorDer(MOTOR_DER_1, MOTOR_DER_2, PWM_MOTOR_DER);
Motores MotorIzq(MOTOR_IZQ_1, MOTOR_IZQ_2, PWM_MOTOR_IZQ);

//-----------------Estrategias------------------
enum Modo {
  Limpiar_Ruedas,
  Ataque_Derecha,
  Ataque_Izquierda,
  Espero_Derecha,
  Espero_Izquierda,
  Rapido_Derecha,
  Rapido_Izquierda,
  Deslizo,
  Espero_Flags
};

String ESTADOS[] = {
    "Limpiar_Ruedas",   "Ataque_Derecha",   "Ataque_Izquierda",
    "Espero_Derecha",   "Espero_Izquierda", "Rapido_Derecha",
    "Rapido_Izquierda", "Deslizo",          "Espero_Flags",
};

//------------------ULTRASONIDO------------------
// MARRON:  VCC    BLANCO
// AZUL:    TRIG   GRIS
// VERDE:   ECHO   AMARILLO
// NEGRO:   GND    BLANCO MATE

long TiempoUltra;
long Distancia;

//--------------------SHARP`S--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

float SHARP_der;
float SHARP_izq;

Sharp SharpDer(PIN_SHARP_DER);
Sharp SharpIzq(PIN_SHARP_IZQ);

unsigned int RivalSharp = 50; // Valor en centimetros

//----------------------JSUMO--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

int sensor = 0;
unsigned int JSUMO_der = 0;
unsigned int JSUMO_izq = 0;
unsigned int Rival = 500;

const int Pines_JSUMO[2] = {
    PIN_JSUMO_F_D,
    PIN_JSUMO_F_I,
};

//-------------------QRE1113---------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int BordeTatami = 600; // MEDIR EN CADA COMPETENCIA.

const int Pines_QRE[2] = {
    PIN_QRE_DERECHO,
    PIN_QRE_IZQUIERDO,
};

//------------------FUNCIONES--------------------
void AsignacionPines() {
  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_QRE[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 4; idx++) {
    int pin = Pines_Entrada[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_Salida[idx];
    pinMode(pin, OUTPUT);
  }

  digitalWrite(PIN_TRIG, LOW);
}

void EncenderLed() {
  digitalWrite(PIN_LED, HIGH);
  delay(250);
  digitalWrite(PIN_LED, LOW);
}

void EnviarPulso() {
  digitalWrite(PIN_TRIG, HIGH);
  delay(10);
  digitalWrite(PIN_TRIG, LOW);
  TiempoUltra = pulseIn(PIN_ECHO, HIGH);
  Distancia = TiempoUltra / 58;
  if (DEBUG_ULTRASONIDO)
    Serial.println(Distancia);
}

void SeleccionPosicion() {
  bool stateDip1 = analogRead(PIN_DIP_1);
  bool stateDip2 = analogRead(PIN_DIP_2);
  dipConbinedState = (stateDip1 << 1) | stateDip2;
  dipConbinedState = dipConbinedState + 1;
  delay(100);

  if (DEBUG_DIP) {
    Serial.print("DIP A: ");
    Serial.print(stateDip1);
    Serial.print(" - DIP B: ");
    Serial.print(stateDip2);
    Serial.print(" - Combined State: ");
    Serial.println(dipConbinedState);
  }
}

void SensarSensores() {
  QREder = analogRead(PIN_QRE_DERECHO);
  QREizq = analogRead(PIN_QRE_IZQUIERDO);
  JSUMO_izq = analogRead(PIN_JSUMO_F_I);
  JSUMO_der = analogRead(PIN_JSUMO_F_D);

  SHARP_der = SharpDer.ObtenerCM();
  SHARP_izq = SharpIzq.ObtenerCM();
}

void Menu() {
  SeleccionPosicion();
  while (!digitalRead(PIN_PULSADOR)) {
    Tiempo++;
    if (Tiempo >= TiempoMax)
      Tiempo = TiempoMax;

    Serial.println(Tiempo);
  }

  if (Tiempo > Tiempo_Min && Tiempo < TiempoMax) {
    // Cambiar estrategia
    caso++;
    Tiempo = 0;
    if (DEBUG_PULSADOR)
      Serial.print("Estas en: ");
    if (DEBUG_PULSADOR)
      Serial.println(ESTADOS[caso]);
    Pantalla = true;
  } else if (Tiempo >= TiempoMax && Pantalla == true) {
    // Entrar en el modo

    digitalWrite(PIN_LED, HIGH);
    if (caso == Limpiar_Ruedas) {
      if (DEBUG_PULSADOR)
        Serial.print("Inicia en: ");
      if (DEBUG_PULSADOR)
        Serial.println(ESTADOS[caso]);
      delay(100);
    } else {
      if (DEBUG_PULSADOR)
        Serial.print("Esperando 5seg. Inicia en: ");
      if (DEBUG_PULSADOR)
        Serial.println(ESTADOS[caso]);
      delay(4990);
    }

    digitalWrite(PIN_LED, LOW);
    Pantalla = false;
    Mode = true;
    Tiempo = 0;
  }
}

#include "Estrategias.h"

void Selector() {
  switch (caso) {
  case Limpiar_Ruedas:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Limpiar Ruedas");
      LimpiarRuedas();
    }
    break;
  case Ataque_Derecha:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Ataque Derecha");
      Ataque();
    }
    break;
  case Ataque_Izquierda:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Ataque Izquierda");
      Ataque();
    }
    break;
  case Espero_Derecha:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Espero Derecha...");
      Espero();
    }
    break;
  case Espero_Izquierda:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Espero Izquierda...");
      Espero();
    }
    break;
  case Rapido_Derecha:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Rapido Derecha");
      Rapido();
    }
    break;
  case Rapido_Izquierda:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Rapido Izquierda");
      Rapido();
    }
    break;
  case Deslizo:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Deslizar");
      Deslizar();
    }
    break;
  case Espero_Flags:
    if (Mode == true) {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Espero con BANDERAS");
      EsperoWithFlags();
    }
    break;
  }
}

//--------------------SETUP----------------------
void setup() {
  Serial.begin(9600);
  AsignacionPines();
  if (DEBUG_PULSADOR)
    Serial.print("Estas en: ");
  if (DEBUG_PULSADOR)
    Serial.println(ESTADOS[caso]);
  EncenderLed(); // esto es para saber cuando el arduino termino de leer las
                 // líneras anteriores a estas.
}

//--------------------LOOP-----------------------
void loop() {
  // SeleccionPosicion();
  Menu();
  Selector();
}