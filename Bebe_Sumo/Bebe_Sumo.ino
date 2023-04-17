// Clave a testear para sensor de piso: Si ambos sensores leen la línea gira 180° sobre su propio eje
//Pero si el dererecho o el izquiero de va la linea gira 90° sobre su eje para el lado contrario del cual leyo el sensor


//--------------FUNCIONES GLOBALES---------------

#define DEBUG_PULSADOR 1  // con DEBUG en 0 NO muestra SerialPrint´s
#define DEBUG_CASOS 0 //Debug del print despues de los 5 segundos.
#define DEBUG_ESTRATEGIA 1  // Debug para saber en que if cae en cada estrategia.
#define DEBUG_SHARP 0
#define DEBUG_Error404 1
#include "Define.h"
#include "OnlyWrite.h"
#include "Sharp.h"

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
enum Modo
{
  Limpiar_Ruedas,
  Matar_Derecha,
  Te_Espero,
  Matar,
  TeEsperoConFlags
};

String ESTADOS[] = {
    "Limpiar_Ruedas",
    "Matar_Derecha",
    "Te_Espero",
    "Matar",
    "TeEsperoConFlags",
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
unsigned int RivalSharp = 60; // 60cm, basicamente al otra punta de tatami.

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
unsigned int Rival = 500; // Si no ve nada tira 0 o tende a valores muy cercados. Ej: 17
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
unsigned int BordeTatami = 500; // Si ve lìnea blanca tende a 200
unsigned int Tatami = 501;      // Si ve lo negro del tatami tende a 800

int Pines_QRE[2] = {
    PIN_QRE_DERECHO,
    PIN_QRE_IZQUIERDO,
};

//--------------------FUNCIONES-------------------

void AsignacionPines()
{
  for (int idx = 0; idx < 7; idx++)
  {
    int pin = Pines_Motor[idx];
    pinMode(pin, OUTPUT);
  }

  for (int idx = 0; idx < 3; idx++)
  {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++)
  {
    int pin = Pines_QRE[idx];
    pinMode(pin, INPUT);
  }

  for (int idx = 0; idx < 2; idx++)
  {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }

  digitalWrite(PIN_TRIG, LOW);
}

void EnviarPulso()
{
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);  //delay(60);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo / 58;
}

void SensarSensores()
{
  QREder = analogRead(PIN_QRE_DERECHO);
  QREizq = analogRead(PIN_QRE_IZQUIERDO);
  JSUMO_izq = analogRead(PIN_JSUMO_F_I);
  JSUMO_der = analogRead(PIN_JSUMO_F_D);
}

void Menu()
{
  while (!digitalRead(PIN_PULSADOR))
  {
    tiempo++;
    Serial.println(tiempo);
  }
  if (tiempo > tiempo_min && tiempo < tiempo_max)
  {
    // cambiar estrategia
    caso++;
    tiempo = 0;
    if (DEBUG_PULSADOR)Serial.print("Estas en: ");
    if (DEBUG_PULSADOR)Serial.println(ESTADOS[caso]);
    pantalla = true;
  }
  else if (tiempo > tiempo_max && pantalla == true)
  {
    // entrar en el modo
    if (DEBUG_PULSADOR)Serial.print("Esperando 5seg. Inicia en: ");
    if (DEBUG_PULSADOR)Serial.println(ESTADOS[caso]);
    digitalWrite(PIN_LED, HIGH);
    delay(5000);
    digitalWrite(PIN_LED, LOW);
    pantalla = false;
    Mode = true;
    tiempo = 0;
  }
}
#include "Error404.h"
#include "Estrategias.h"

//--------------------SETUP-------------------
void setup()
{
  Serial.begin(9600);
  AsignacionPines();
  if (DEBUG_PULSADOR)
    Serial.print("Estas en: ");
  if (DEBUG_PULSADOR)
    Serial.println(ESTADOS[caso]);
  EncenderLed(); // esto es para saber cuando el arduino termino de leer las líneras anteriores a estas.
}

//--------------------LOOP-------------------
void loop()
{

  Menu();

  switch (caso)
  {
  case Limpiar_Ruedas:
    if (Mode == true)
    {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Limpiar Ruedas");
      LimpiarRuedas();
    }
    break;
  case Matar_Derecha:
    if (Mode == true)
    {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Matar Derecha");
      MATARDERECHA();
    }
    break;
  case Te_Espero:
    if (Mode == true)
    {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Te Espero...");
      TeEspero();
    }
    break;
  case Matar:
    if (Mode == true)
    {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Matar");
      MATAR();
    }
    break;
  case TeEsperoConFlags:
    if (Mode == true)
    {
      if (DEBUG_CASOS)
        Serial.println("EN RUEDO Te Espero con BANDERAS");
      TeEsperoWithFlags();
    }
    break;
  case 5:
    caso = 0;
    break;
  }
}