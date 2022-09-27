
//--------------FUNCIONES GLOBALES---------------
#define DEBUG 1
#define ON HIGH
#define OFF LOW

//-------------------MOTORES---------------------
#define MOTOR_DER_1 8
#define MOTOR_DER_2 7
#define MOTOR_IZQ_1 9
#define MOTOR_IZQ_2 10
#define PWM_MOTOR_DER 3
#define PWM_MOTOR_IZQ 11

int Pines_Motor[4] = {
    MOTOR_DER_1,
    MOTOR_DER_2,
    MOTOR_IZQ_1,
    MOTOR_IZQ_2,
};

#define SPEED_SERCHING 100
#define SPEED_ATTACK 255

//-------------------PULSADOR--------------------
#define PIN_PULSADOR A3
#define PIN_LED 13
bool pantalla = true;
unsigned long tiempo_max = 10000;
int tiempo;

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
#define PIN_TRIG 5
#define PIN_ECHO 6
long Tiempo;
long Distancia;

//--------------------SHARP´S--------------------
#define PIN_SHARP_F_D A7
#define PIN_SHARP_F_I A6
#define PIN_SHARP_DER A5
#define PIN_SHARP_IZQ A4

int Pines_Sharps[4] = {
    PIN_SHARP_F_D,
    PIN_SHARP_F_I,
    PIN_SHARP_DER,
    PIN_SHARP_IZQ,
};

//---------------------CNY70---------------------
unsigned int CNY70der = 0;
unsigned int CNY70izq = 0;
unsigned int BordeTatami = 100;  // NO CAMBIAR DE VALOR
unsigned int SinSuperficie = 20; // NO CAMBIAR DE VALOR

//--------------VARIABLES DE ENTORNO-------------



//-------------------FUNCIONES-------------------
void Avazar()
{
  digitalWrite(MOTOR_DER_1, ON);
  digitalWrite(MOTOR_DER_2, OFF);
  digitalWrite(MOTOR_IZQ_1, ON);
  digitalWrite(MOTOR_IZQ_2, OFF);
  if (DEBUG)
    Serial.println("Avanzar");
}

void Buscar()
{
  // DEPENDE LAS ESTRATEGIAS SELECCIONADAS.
  if (DEBUG)
    Serial.println("Buscar");
}

void Derecha()
{
  digitalWrite(MOTOR_DER_1, OFF);
  digitalWrite(MOTOR_DER_2, ON);
  digitalWrite(MOTOR_IZQ_1, ON);
  digitalWrite(MOTOR_IZQ_2, OFF);
  if (DEBUG)
    Serial.println("Derecha");
  delay(200);
}

void Izquierda()
{
  digitalWrite(MOTOR_DER_1, ON);
  digitalWrite(MOTOR_DER_2, OFF);
  digitalWrite(MOTOR_IZQ_1, OFF);
  digitalWrite(MOTOR_IZQ_2, ON);
  if (DEBUG)
    Serial.println("Izquierda");
  delay(200);
}

void AsignacionPinMotores()
{
  for (int idx = 0; idx < 4; idx++)
  {
    int pin = Pines_Motor[idx];
    pinMode(pin, OUTPUT);
  }
}

void AsignacionPinSharps()
{
  for (int idx = 0; idx < 4; idx++)
  {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }
}

void EnviarPulsoUltradonido()
{
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo / 58;
}
void CNY_Der()
{
  CNY70der = analogRead(A0);

  if ((CNY70der > SinSuperficie) && (CNY70der < BordeTatami))
  {
    // Volver a lo negro
    if (DEBUG)
      Serial.println("Me caigo weon");
  }
}

void CNY_Izq()
{
  CNY70izq = analogRead(A1);
  if ((CNY70izq > SinSuperficie) && (CNY70izq < BordeTatami))
  {
    // Volver a lo negro
    if (DEBUG)
      Serial.println("Me caigo weon");
  }
}

void EncenderLed() {
  digitalWrite(PIN_LED, HIGH);
  delay(350);
  digitalWrite(PIN_LED, LOW);
  delay(350);
}

//--------------------SETUP-------------------
void setup()
{
  Serial.begin(9600); // braudate 9600
  AsignacionPinMotores();
  AsignacionPinSharps();
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(MOTOR_DER_1, OUTPUT);
  pinMode(MOTOR_DER_2, OUTPUT);
  pinMode(MOTOR_IZQ_1, OUTPUT);
  pinMode(MOTOR_IZQ_2, OUTPUT);
  digitalWrite(PIN_TRIG, LOW); // Talvez Sacar.
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

//--------------------LOOP-------------------
void loop()
{
  
  pulsador = analogRead(PIN_PULSADOR);
  delay(200);


  switch (estado) {

    case SET1:
      if (DEBUG && pantalla == true) {
        Serial.println("Estrategia 1");
        EncenderLed();
        pantalla = false;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
          estado = ENRUEDO_SET1;
        } else {
          estado = SET2;
          estado_anterior = estado;
        }
      }
      break;

    case SET2:
      if (DEBUG && pantalla == false) {
        Serial.println("Estrategia 2");
        EncenderLed();
        EncenderLed();
        pantalla = true;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
          estado = ENRUEDO_SET2;
        } else {
          estado = SET3;
          estado_anterior = estado;
        }
      }
      break;

    case SET3:
      if (DEBUG && pantalla == true) {
        Serial.println("Estrategia 3");
        EncenderLed();
        EncenderLed();
        EncenderLed();
        pantalla = false;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
          estado = ENRUEDO_SET3;
        } else {
          estado = SET1;
          estado_anterior = estado;
        }
      }
      break;

    case ENRUEDO_SET1:
      {
        if (DEBUG) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG) Serial.println("EN RUEDO LA ESTRATEGIA 1");
        //acá llamar a la función de la estrategia correspondiete
      }
      break;

    case ENRUEDO_SET2:
      {
        if (DEBUG) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG) Serial.println("EN RUEDO LA ESTRATEGIA 2");
        //acá llamar a la función de la estrategia correspondiete
      }
      break;

    case ENRUEDO_SET3:
      {
        if (DEBUG) Serial.println("INICIANDO");
        delay(4700);
        if (DEBUG) Serial.println("EN RUEDO LA ESTRATEGIA 3");
        //acá llamar a la función de la estrategia correspondiete
      }
      break;
  }

}
