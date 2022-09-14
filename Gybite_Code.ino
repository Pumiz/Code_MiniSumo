// TODOS LOS NÚMEROS DE PINES ESTÁN EN MODO DE EJEMPLOS
// ELIMINAR ESTO CUÁNDO ESTEN EN SUS VALORES CORRECTOS

//--------------FUNCIONES GLOBALES---------------
#define DEBUG 1
#define ON HIGH
#define OFF LOW
#define IZQUIERDA 1
#define DERECHA 0
#define FRENAR -1
#define izquierdo 1
#define derecho 0
#define RETROCEDER 0

//-------------------MOTORES---------------------
#define MOTOR_DER_1 2
#define MOTOR_DER_2 3
#define MOTOR_IZQ_1 4
#define MOTOR_IZQ_2 5
#define PWM_MOTOR_DER 6
#define PWM_MOTOR_IZQ 7

int Pines_Motor[4] = {
  MOTOR_DER_1,
  MOTOR_DER_2,
  MOTOR_IZQ_1,
  MOTOR_IZQ_2,
};

#define SPEED_SERCHING 100
#define SPEED_ATTACK 255

//-------------------PULSADOR--------------------
#define PIN_PULSADOR A5
enum PULSADORES {
  BOTON_GO
};
int pin_pulsadores[1] = { PIN_PULSADOR };
int estados_pulsadores_anterior[1] = { true };
bool pulsadorEsLiberado(int index) {
  bool estado_actual = digitalRead(pin_pulsadores[index]);
  bool estado = estado_actual != estados_pulsadores_anterior[index] && estado_actual == HIGH;
  if (estado) delay(500);
  estados_pulsadores_anterior[index] = estado_actual;
  return estado;
}

//------------------ULTRASONIDO------------------
#define PIN_TRIG 11
#define PIN_ECHO 10
long Tiempo;
long Distancia;

//--------------------SHARP´S--------------------
#define PIN_SHARP_F_D A2
#define PIN_SHARP_F_I A3
#define PIN_SHARP_DER A4
#define PIN_SHARP_IZQ A5

//---------------------CNY70---------------------
unsigned int CNY70der = 0;
unsigned int CNY70izq = 0;
unsigned int BordeTatami = 100;   //NO CAMBIAR DE VALOR
unsigned int SinSuperficie = 20;  //NO CAMBIAR DE VALOR


//--------------VARIABLES DE ENTORNO-------------
enum ESTADOS {
  ESPERAR,
  COMBATIR
};
int estado = ESPERAR;
int estado_anterior = COMBATIR;

//-------------------FUNCIONES-------------------
void Avazar() {
  digitalWrite(MOTOR_DER_1, ON);
  digitalWrite(MOTOR_DER_2, OFF);
  digitalWrite(MOTOR_IZQ_1, ON);
  digitalWrite(MOTOR_IZQ_2, OFF);
  if (DEBUG) Serial.println("Avanzar");
}

void Buscar() {
  // DEPENDE LAS ESTRATEGIAS SELECCIONADAS.
  if (DEBUG) Serial.println("Buscar");
}

void Derecha() {
  digitalWrite(MOTOR_DER_1, OFF);
  digitalWrite(MOTOR_DER_2, ON);
  digitalWrite(MOTOR_IZQ_1, ON);
  digitalWrite(MOTOR_IZQ_2, OFF);
  if (DEBUG) Serial.println("Derecha");
  delay(200);
}

void Izquierda() {
  digitalWrite(MOTOR_DER_1, ON);
  digitalWrite(MOTOR_DER_2, OFF);
  digitalWrite(MOTOR_IZQ_1, OFF);
  digitalWrite(MOTOR_IZQ_2, ON);
  if (DEBUG) Serial.println("Izquierda");
  delay(200);
}

void AsignacionPinMotores() {
  for (int idx = 0; idx < 4; idx++) {
    int pin = Pines_Motor[idx];
    pinMode(pin, OUTPUT);
  }
}

void AsignacionPinSharps() {
  for (int idx = 0; idx < 4; idx++) {
    int pin = Pines_Sharps[idx];
    pinMode(pin, INPUT);
  }
}

void EnviarPulsoUltradonido() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo / 58;
}
void CNY_Der() {
  CNY70der = analogRead(A0);

  if ((CNY70der > SinSuperficie) && (CNY70der < BordeTatami)) {
    //Volver a lo negro
    if (DEBUG) Serial.println("Me caigo weon");
  }
}

void CNY_Izq() {
  CNY70izq = analogRead(A1);
  if ((CNY70izq > SinSuperficie) && (CNY70izq < BordeTatami)) {
    //Volver a lo negro
    if (DEBUG) Serial.println("Me caigo weon");
  }
}

//--------------------SETUP-------------------
void setup() {
  Serial.begin(9600);  //braudate 9600
  AsignacionPinMotores();
  AsignacionPinSharps();
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  digitalWrite(PIN_TRIG, LOW);  //Talvez Sacar.
}

//--------------------LOOP-------------------
void loop() {
  switch (estado) {
    case ESPERAR:
      if (DEBUG) Serial.println("Esperando boton");

      if (pulsadorEsLiberado(BOTON_GO)) {
        estado = COMBATIR;
        delay(5000);
      }
      break;
      
    case COMBATIR:
  }
}