
//--------------FUNCIONES GLOBALES---------------
#define DEBUG 0     //con DEBUG en 0 no muestra SerialPrint`s   (SETEAR ESTE ESTADO ANTES DE COMPETIR PARA TENER LA MEJOR OPTIMIZACIÒN)
#define DEBUG_PULSADOR 0 
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
    PWM_MOTOR_IZQ};

//-------------------PULSADOR-------------------
enum ESTADOS
{
  SET1,
  SET2,
  SET3,
  SET4,
  ENRUEDO_SET1,
  ENRUEDO_SET2,
  ENRUEDO_SET3,
  ENRUEDO_SET4
};

int numero = 0;
bool DEBUG_LECTURA = 1;
bool pantalla = true;
bool pulsador;
int estado = SET1;
int estado_anterior = SET3;

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
unsigned int RivalSharp = 60; // 60cm, basicamente al otra punta de tatami. 

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
unsigned int Rival = 500; // Si no ve nada tira 0 o tende a valores muy cercados. Ej: 17
// Si detecta algo, no importa la distancia tende a arriba de lso 800.

int Pines_JSUMO[2] = {
    PIN_JSUMO_F_D,
    PIN_JSUMO_F_I,
};

//---------------------QRE1113--------------------


//--------------------FUNCIONES-------------------

void AsignacionPines()
{
  for (int idx = 0; idx < 6; idx++)
  {
    int pin = Pines_Motor[idx];
    pinMode(pin, OUTPUT);
  }

  for (int idx = 0; idx < 2; idx++)
  {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++)
  {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }

  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void EnviarPulso()
{
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo / 58; // El tiempo dividido 58 te da la distancia en centìmetros.
}

void SensarSensores()
{
  
  JSUMO_izq = analogRead(PIN_JSUMO_F_I);
  JSUMO_der = analogRead(PIN_JSUMO_F_D);
  QREder = analogRead(QRE_DERECHO);
  QREizq = analogRead(QRE_IZQUIERDO);
}

//--------------------SETUP-------------------
void setup()
{
  Serial.begin(9600);
  AsignacionPines();
}

//--------------------LOOP-------------------
void loop()     
{

  //lectura cada 200ms
  if(DEBUG_LECTURA == 1){
    pulsador = digitalRead(PIN_PULSADOR);
    delay(200);
  }    

  switch (estado) {

    case SET1:
      if (pantalla == true) {
        if(DEBUG_PULSADOR)Serial.println("Estrategia 1");
        EncenderLed();
        pantalla = false;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
        DEBUG_LECTURA = 0;
        if (DEBUG_PULSADOR) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG_PULSADOR) Serial.println("EN RUEDO LA ESTRATEGIA 1");
        estado = ENRUEDO_SET1;
        } else {
          estado = SET2;
          estado_anterior = estado;
        }
      }
      break;

    case SET2:
      if (pantalla == false) {
        if(DEBUG_PULSADOR)Serial.println("Estrategia 2");
        EncenderLed();
        EncenderLed();
        pantalla = true;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
        DEBUG_LECTURA = 0;
        if (DEBUG_PULSADOR) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG_PULSADOR) Serial.println("EN RUEDO LA ESTRATEGIA 2");
        estado = ENRUEDO_SET2;
        } else {
          estado = SET3;
          estado_anterior = estado;
        }
      }
      break;

    case SET3:
      if (pantalla == true) {
        if(DEBUG_PULSADOR)Serial.println("Estrategia 3");
        EncenderLed();
        EncenderLed();
        EncenderLed();
        pantalla = false;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
        DEBUG_LECTURA = 0;
        if (DEBUG_PULSADOR) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG_PULSADOR) Serial.println("EN RUEDO LA ESTRATEGIA 3");
        estado = ENRUEDO_SET3;
        } else {
          estado = SET1;
          estado_anterior = estado;
        }
      }
      break;

    case SET4:
      if (pantalla == false) {
        if(DEBUG_PULSADOR) Serial.println("Estrategia 4");
        EncenderLed();
        EncenderLed();
        EncenderLed();
        EncenderLed();
        pantalla = true;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
        DEBUG_LECTURA = 0;
        if (DEBUG_PULSADOR) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG_PULSADOR) Serial.println("EN RUEDO LA ESTRATEGIA 4");
        estado = ENRUEDO_SET4;
        } else {
          estado = SET1;
          estado_anterior = estado;
        }
      }
      break;

    case ENRUEDO_SET1:
      {
        #include "MATERDERECHA.h"

        //acá llamar a la función de la estrategia correspondiete
      }
      break;

    case ENRUEDO_SET2:
      {
        #include "TeEspero.h"
        //acá llamar a la función de la estrategia correspondiete
      }
      break;

    case ENRUEDO_SET3:
      {
        #include "MATAR.h"
        //acá llamar a la función de la estrategia correspondiete
      }
      break;

    case ENRUEDO_SET4:
      {

        //acá llamar a la función de la estrategia correspondiete
      }
      break;
  }
}

