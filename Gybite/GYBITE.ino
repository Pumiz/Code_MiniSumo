
//--------------FUNCIONES GLOBALES---------------
#define DEBUG 0 // con DEBUG en 0 no muestra SerialPrint`s   (SETEAR ESTES ESTADO ANTES DE COMPETIR PARA TENER LA MEJOR OPTIMIZACIÒN)
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



//-------------------PULSADOR---------------

bool pantalla = true;
unsigned long tiempo_max = 10000;

enum ESTADOS
{
  SET1,
  SET2,
  SET3,
  ENRUEDO_SET1,
  ENRUEDO_SET2,
  ENRUEDO_SET3
};

bool pulsador;
int estado = SET1;
int estado_anterior = SET3;

//------------------ULTRASONIDO------------------

long Tiempo;
long Distancia;

//--------------------SHARP`S-------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC


unsigned int SHARP_der = 0;
unsigned int SHARP_izq = 0;
unsigned int RivalSharp = 450; // Si no ve nada tende a los 100, Si detecta algo tende a los 900 si està muy cerca.
// en caso de que sea un punto promedio e intermedio esta en los 350 y 450.

int Pines_Sharps[2] = {
    PIN_SHARP_DER,
    PIN_SHARP_IZQ,
};

//----------------------JSUMO---------------------

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


//-------------------FUNCIONES-------------------

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
  SHARP_der = analogRead(PIN_SHARP_DER);
  SHARP_izq = analogRead(PIN_SHARP_IZQ);
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

  pulsador = digitalRead(PIN_PULSADOR);

  switch (estado)
  {

  case SET1:
    if (pulsador == LOW)
    {
      EncenderLed(); // verificar todo el case del pulsador
      estado = ENRUEDO_SET1;
      delay(4357);
    }
    break;

  case ENRUEDO_SET1:
  {
    if (DEBUG)Serial.println("INICIANDO SET 1");
    EnviarPulso();
    SensarSensores();
    EncenderLed();

//los motores estan al revez
// cambiar los pines de los motores en la libreria defines 
// cambiar los high por low y viseversa en la libreria onlywrites

    if (JSUMO_der > RivalSharp)
    {
      MotorDerGoBuscar();
      MotorIzqStop();
      if (DEBUG)Serial.println("JSUMO: LATERAL DERECHA");
    }

    if (JSUMO_izq > RivalSharp)
    {
      MotorDerStop();
      MotorIzqGoBuscar();
      if (DEBUG)Serial.println("JSUMO: LATERAL IZQUIERDA");
    }

    if (JSUMO_der > Rival && Distancia < 40 && JSUMO_izq > Rival)
    {
      MotorDerGoATAQUE();
      MotorIzqGoATAQUE();
      if (DEBUG)Serial.println("Atacar");
    }
    else
    {
      MotorDerStop();
      MotorIzqGoBuscar();
      if (DEBUG) Serial.println("Buscar");
    }

    if (Distancia > 7 && Distancia < 60)
    {
      MotorDerGoATAQUE();
      MotorIzqGoATAQUE();
      if (DEBUG)Serial.println("Atacar");
    }

    if (SHARP_izq > RivalSharp)
    {
      MotorDerStop();
      MotorIzqGoGhirar();
      if (DEBUG)Serial.println("SHARP: Rival a la IZQUIERDA");
    }

    if (SHARP_der > RivalSharp)
    {
      MotorDerGoGhirar();
      MotorIzqStop();
      if (DEBUG)Serial.println("SHARP: Rival a la DERECHA");
    }

  break;
  }
}
}
