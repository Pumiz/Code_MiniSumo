
//--------------FUNCIONES GLOBALES---------------
#define DEBUG 0
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

#define VELOCIDAD_BUSCAR 100
#define VELOCIDAD_ATAQUE 200

//-------------------PULSADOR-- C-------------
#define PIN_PULSADOR A3
#define PIN_LED 13
bool pantalla = true;
unsigned long tiempo_max = 3000;
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

//--------------------SHARP`S-------------------
//ROSA:     SEÑAL
//AMARILLO: GND
//CELESTE:  VCC

#define PIN_SHARP_DER A5
#define PIN_SHARP_IZQ A6


unsigned int SHARP_der = 0;
unsigned int SHARP_izq = 0;
unsigned int RivalSharp = 450;  // Si no ve nada tende a los 100, Si detecta algo tende a los 900 si està muy cerca. 
// en cas de que sea un punto promedio e intermedio esta en los 350 y 400.

int Pines_Sharps[2] = {
  PIN_SHARP_DER,
  PIN_SHARP_IZQ,
};


//----------------------JSUMO---------------------

//ROSA:     SEÑAL
//AMARILLO: GND
//CELESTE:  VCC

#define PIN_JSUMO_F_D A7
#define PIN_JSUMO_F_I A4

int sensor =0;

unsigned int JSUMO_der = 0;
unsigned int JSUMO_izq = 0;
unsigned int Rival = 500;    //Si no ve nada tira 0 o tende a valores muy cercados. Ej: 17 
//Si detecta algo, no importa la distancia tende a arriba de lso 800.

int Pines_JSUMO[2] = {
  PIN_JSUMO_F_D,
  PIN_JSUMO_F_I,
};

//---------------------QRE1113--------------------


#define QRE_DERECHO A0
#define QEE_IZQUIERDO A1

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int BordeTatami = 500; //Si ve lìnea blanca tende a 200
unsigned int Tatami = 501;  //Si ve lo negro del tatami tende a 800


//-------------------FUNCIONES-------------------



void EncenderLed() {
  digitalWrite(PIN_LED, HIGH);
  delay(350);
  digitalWrite(PIN_LED, LOW);
  delay(350);
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

void AsignacionPinJSUMO() {
  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_JSUMO[idx];
    pinMode(pin, INPUT);
  }
}

void EnviarPulso() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  Tiempo = pulseIn(PIN_ECHO, HIGH);
  Distancia = Tiempo / 58;
}
void Sensar_QRE() {
  QREder = analogRead(QRE_DERECHO);
  QREizq = analogRead(QEE_IZQUIERDO);
  if (QREizq < Tatami || QREder < Tatami){
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
  delay(300);
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
  delay(350);

    Serial.println("Me caigo weon");
  }
}

void Sensar_Sensores() {
  JSUMO_izq = analogRead(PIN_JSUMO_F_I);
  JSUMO_der = analogRead(PIN_JSUMO_F_D);
  SHARP_der = analogRead(PIN_SHARP_DER);
  SHARP_izq = analogRead(PIN_SHARP_IZQ);
}


//--------------------SETUP-------------------
void setup() {
  Serial.begin(9600);  //braudate 9600
  AsignacionPinMotores();
  AsignacionPinSharps();
  AsignacionPinJSUMO();
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(MOTOR_DER_1, OUTPUT);
  pinMode(MOTOR_DER_2, OUTPUT);
  pinMode(MOTOR_IZQ_1, OUTPUT);
  pinMode(MOTOR_IZQ_2, OUTPUT);
  digitalWrite(PIN_TRIG, LOW);
  pinMode(PWM_MOTOR_DER, OUTPUT);
  pinMode(PWM_MOTOR_IZQ, OUTPUT);

}

//--------------------LOOP-------------------
void loop() {
    pulsador = analogRead(PIN_PULSADOR);
  delay(200);


  switch (estado) {

    case SET1:
      if (pantalla == true) {
        if(DEBUG)Serial.println("Estrategia 1");
        pantalla = false;
      }
      if (pulsador == LOW) {
        if (millis() >= tiempo_max) {
          estado = ENRUEDO_SET1;
      }
      break;

    case ENRUEDO_SET1:
      {
      if(DEBUG)Serial.println("INICIANDO SET 1");

EnviarPulso();
Sensar_Sensores();
//EncenderLed();



  if(JSUMO_der > RivalSharp){
  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
  if(DEBUG)Serial.println("JSUMO: LATERAL DERECHA");
  }

  if(JSUMO_izq > RivalSharp){
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
  if(DEBUG)Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if(JSUMO_der > Rival && Distancia < 30 && JSUMO_izq > Rival){
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_ATAQUE);

  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_ATAQUE); 
  if(DEBUG)Serial.println("Atacar");
  }else{
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);

  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
  if(DEBUG)Serial.println("Buscar");
  }

      
  if(SHARP_izq > RivalSharp){
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);

  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
  if(DEBUG)Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if(SHARP_der > RivalSharp){
  digitalWrite(MOTOR_DER_1, HIGH);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);

  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
  if(DEBUG)Serial.println("SHARP: Rival a la DERECHA");
  }

      }
      break;
}
}
}
