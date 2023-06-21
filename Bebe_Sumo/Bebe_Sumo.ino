// Clave a testear para sensor de piso: Si ambos sensores leen la línea gira 180° sobre su propio eje
//Pero si el dererecho o el izquiero de va la linea gira 90° sobre su eje para el lado contrario del cual leyo el sensor


//--------------FUNCIONES GLOBALES---------------
#include "Define.h"
#include "OnlyWrite.h"
#define DEBUG_PULSADOR 1    // con DEBUG en 0 NO muestra SerialPrint´s
#define DEBUG_ESTRATEGIA 1  // Debug para saber en que if cae en cada estrategia.
#define DEBUG_CASOS 0       //Debug despues de los 5 segundos.
#define DEBUG_ULTRASONIDO 0
#define DEBUG_SHARP 0
#define DEBUG_Error404 0


//-------------------MOTORES---------------------
int Pines_Motor[8] = {
  MOTOR_DER_1,
  MOTOR_DER_2,
  MOTOR_IZQ_1,
  MOTOR_IZQ_2,
  PWM_MOTOR_DER,
  PWM_MOTOR_IZQ,
  PIN_TRIG,
  PIN_LED
};

//-------------------PULSADOR-------------------
enum Modo {
  Limpiar_Ruedas,
  Ataque_Derecha,
  Ataque_Izquierda,
  Espero_Derecha,
  Espero_Izquierda,
  Deslizo,
  Atacar,
  Espero_Flags
};

String ESTADOS[] = {
  "Limpiar_Ruedas",
  "Ataque_Derecha",
  "Ataque_Izquierda",
  "Espero_Derecha",
  "Espero_Izquierda",
  "Deslizo",
  "Atacar",
  "Espero_Flags",
};

//------------------ULTRASONIDO------------------
// MARRON:  VCC    BLANCO
// AZUL:    TRIG   GRIS
// VERDE:   ECHO   AMARILLO
// NEGRO:   GND    BLANCO MATE

long Tiempo_Ultra;
long Distancia;

//--------------------SHARP`S--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

float SHARP_der;
float SHARP_izq;

/* float analogValueDer;
float analogValue; 
 */
unsigned int RivalSharp = 50;

int Pines_Sharps[4] = {
  PIN_SHARP_DER,
  PIN_SHARP_IZQ,
  PIN_ECHO,
  PIN_PULSADOR
};

//----------------------JSUMO--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

int sensor = 0;

unsigned int JSUMO_der = 0;
unsigned int JSUMO_izq = 0;
unsigned int Rival = 500;  // Si no ve nada tira 0 o tende a valores muy cercados. Ej: 17
// Si detecta algo, NO IMPORTA LA DISTANCIA tende a arriba de los 800.

int Pines_JSUMO[2] = {
  PIN_JSUMO_F_D,
  PIN_JSUMO_F_I,
};

//---------------------QRE1113--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int Tatami = 501;  // Si ve línea blanca tende a 200. Si ve lo negro del tatami tende a 800

int Pines_QRE[2] = {
  PIN_QRE_DERECHO,
  PIN_QRE_IZQUIERDO,
};

//--------------------FUNCIONES-------------------

void AsignacionPines() {
  for (int idx = 0; idx < 7; idx++) {
    int pin = Pines_Motor[idx];
    pinMode(pin, OUTPUT);
  }

  for (int idx = 0; idx < 3; idx++) {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_QRE[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }

  digitalWrite(PIN_TRIG, LOW);
}

void EnviarPulso() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);  //delay(60);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo_Ultra = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo_Ultra / 58;
  if (DEBUG_ULTRASONIDO) Serial.println(Distancia);
}

void LeerSharp() {
  int analogValueDer = analogRead(PIN_SHARP_DER);
  float voltageDer = analogValueDer / 1024. * 5;
  float resistenciaDer = 2000 * voltageDer / (1 - voltageDer / 5);
  SHARP_der = pow(50 * 1e3 * pow(10, 0.7) / resistenciaDer, (1 / 0.7));
  SHARP_der = SHARP_der / 10;

  int analogValue = analogRead(PIN_SHARP_IZQ);
  float voltage = analogValue / 1024. * 5;
  float resistencia = 2000 * voltage / (1 - voltage / 5);
  SHARP_izq = pow(50 * 1e3 * pow(10, 0.7) / resistencia, (1 / 0.7));
  SHARP_izq = SHARP_izq / 10;

  if (DEBUG_SHARP) Serial.print("Sharp: ");
  if (DEBUG_SHARP) Serial.print(SHARP_izq);  //  <------- imprime el valor en centímetros del sensor deseado.
  if (DEBUG_SHARP) Serial.println(" cm");
}

void SensarSensores() {
  QREder = analogRead(PIN_QRE_DERECHO);
  QREizq = analogRead(PIN_QRE_IZQUIERDO);
  JSUMO_izq = analogRead(PIN_JSUMO_F_I);
  JSUMO_der = analogRead(PIN_JSUMO_F_D);
}

void Menu() {
  while (!digitalRead(PIN_PULSADOR)) {
    Tiempo++;
    Serial.println(Tiempo);
  }
  if (Tiempo > Tiempo_Min && Tiempo < Tiempo_Max) {
    // Cambiar estrategia
    caso++;
    Tiempo = 0;
    if (DEBUG_PULSADOR) Serial.print("Estas en: ");
    if (DEBUG_PULSADOR) Serial.println(ESTADOS[caso]);
    Pantalla = true;
  } else if (Tiempo > Tiempo_Max && Pantalla == true) {
    // Entrar en el modo
    if (DEBUG_PULSADOR) Serial.print("Esperando 5seg. Inicia en: ");
    if (DEBUG_PULSADOR) Serial.println(ESTADOS[caso]);
    digitalWrite(PIN_LED, HIGH);
    delay(4990);
    digitalWrite(PIN_LED, LOW);
    Pantalla = false;
    Mode = true;
    Tiempo = 0;
  }
}
#include "Error404.h"
#include "Estrategias.h"

//--------------------SETUP-------------------
void setup() {
  Serial.begin(9600);
  AsignacionPines();
  if (DEBUG_PULSADOR)
    Serial.print("Estas en: ");
  if (DEBUG_PULSADOR)
    Serial.println(ESTADOS[caso]);
  EncenderLed();  // esto es para saber cuando el arduino termino de leer las líneras anteriores a estas.
}

//--------------------LOOP-------------------
void loop() {

  Menu();

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
        AtaqueDER();
      }
      break;
    case Ataque_Izquierda:
      if (Mode == true) {
        if (DEBUG_CASOS)
          Serial.println("EN RUEDO Ataque Izquierda");
        AtaqueIZQ();
      }
      break;
    case Espero_Derecha:
      if (Mode == true) {
        if (DEBUG_CASOS)
          Serial.println("EN RUEDO Espero Derecha...");
        EsperoDER();
      }
      break;
    case Espero_Izquierda:
      if (Mode == true) {
        if (DEBUG_CASOS)
          Serial.println("EN RUEDO Espero Izquierda...");
        EsperoIZQ();
      }
      break;
    case Deslizo:
      if (Mode == true) {
        if (DEBUG_CASOS)
          Serial.println("EN RUEDO Deslizar");
        Deslizar();
      }
      break;
    case Atacar:
      if (Mode == true) {
        if (DEBUG_CASOS)
          Serial.println("EN RUEDO Ataque");
        Ataque();
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