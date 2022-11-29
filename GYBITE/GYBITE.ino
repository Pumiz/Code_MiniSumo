//--------------FUNCIONES GLOBALES---------------
#define DEBUG 1  //con DEBUG en 0 no muestra SerialPrint´s  
#define DEBUG_PULSADOR 1
#define DEBUG_CASOS 0
#define ON HIGH
#define OFF LOW
#include "Define.h"
#include "OnlyWrite.h"


//-------------------MOTORES---------------------
int Pines_Motor[6] = {
  MOTOR_DER_1,
  MOTOR_DER_2,
  MOTOR_IZQ_1,
  MOTOR_IZQ_2,
  PWM_MOTOR_DER,
  PWM_MOTOR_IZQ
};

//-------------------PULSADOR-------------------
enum Modo {
  Limpiar_Ruedas,
  Matar_Derecha,
  Te_Espero,
  Matar
};

String ESTADOS[] = {
  "Limpiar_Ruedas",
  "Matar_Derecha",
  "Te_Espero",
  "Matar",
};

//------------------ULTRASONIDO------------------
// MARRON:  VCC
// AZUL:    TRIG
// VERDE:   ECHO
// NEGRO:   GND

long Tiempo;
long Distancia;

//--------------------SHARP`S--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

unsigned int SHARP_der = 0;
unsigned int SHARP_izq = 0;
unsigned int RivalSharp = 60;  // 60cm, basicamente al otra punta de tatami.

int Pines_Sharps[2] = {
  PIN_SHARP_DER,
  PIN_SHARP_IZQ,
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
//Próximamente.


//--------------------FUNCIONES-------------------

void AsignacionPines() {
  for (int idx = 0; idx < 6; idx++) {
    int pin = Pines_Motor[idx];
    pinMode(pin, OUTPUT);
  }

  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }

  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void EnviarPulso() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo / 58;  // El tiempo dividido 58 te da la distancia en centìmetros.
}

void SensarSensores() {

  JSUMO_izq = analogRead(PIN_JSUMO_F_I);
  JSUMO_der = analogRead(PIN_JSUMO_F_D);
  QREder = analogRead(QRE_DERECHO);
  QREizq = analogRead(QRE_IZQUIERDO);
}

void Menu() {
  while (!digitalRead(PIN_PULSADOR)) {
    tiempo++;
    Serial.println(tiempo);
  }
  if (tiempo > tiempo_min && tiempo < tiempo_max) {
    //cambiar estrategia
    caso++;
    tiempo = 0;
    if(DEBUG_PULSADOR)Serial.print("Estas en: ");
    if(DEBUG_PULSADOR)Serial.println(ESTADOS[caso]);
    pantalla = true;
  } else if (tiempo > tiempo_max && pantalla == true) {
    //entrar en el modo
    if(DEBUG_PULSADOR)Serial.print("En ruedo: ");
    if(DEBUG_PULSADOR)Serial.println(ESTADOS[caso]);
    digitalWrite(PIN_LED, HIGH);
    delay(5000);
    digitalWrite(PIN_LED, LOW);
    pantalla = false;
    Mode = true;
    tiempo = 0;
  }
}
#include "Estrategias.h"
//--------------------SETUP-------------------
void setup() {
  Serial.begin(9600);
  AsignacionPines();
  if(DEBUG_PULSADOR)Serial.print("Estas en: ");
  if(DEBUG_PULSADOR)Serial.println(ESTADOS[caso]);
  EncenderLed(); //esto es para saber cuando el arduino termino de leer las líneras anteriores a estas.
}

//--------------------LOOP-------------------
void loop() {

  Menu();


  switch (caso) {
    case Limpiar_Ruedas:
      if (Mode == true) {
        if(DEBUG_CASOS)Serial.println("EN RUEDO Limpiar Ruedas");
        LimpiarRuedas();
      }
      break;
    case Matar_Derecha:
      if (Mode == true) {
        if(DEBUG_CASOS)Serial.println("EN RUEDO Matar Derecha");
        MATARDERECHA();
      }
      break;
    case Te_Espero:
      if (Mode == true) {
        if(DEBUG_CASOS)Serial.println("EN RUEDO Te Espero...");
        TeEspero();
      }
      break;
    case Matar:
      if (Mode == true) {
        if(DEBUG_CASOS)Serial.println("EN RUEDO Matar");
        MATAR();
      }
      break;
  }
}