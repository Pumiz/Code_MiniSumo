#define PIN_PULSADOR 5
#define DEBUG 1
#define PIN_LED 13
bool pantalla = true;

unsigned long tiempo_max = 5000;
int tiempo;

void EncenderLed() {
  digitalWrite(PIN_LED, HIGH);
  delay(350);
  digitalWrite(PIN_LED, LOW);
  delay(350);
}

enum ESTADOS {
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


void setup() {
  Serial.begin(9600);
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {


  pulsador = digitalRead(PIN_PULSADOR);
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
