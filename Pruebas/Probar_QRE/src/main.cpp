//---------------------QRE1113--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

#include <Arduino.h>
#include <Motores.h>

//-------------------MOTORES--------------------
#define MOTOR_DER_1 6
#define MOTOR_DER_2 5

#define MOTOR_IZQ_1 8
#define MOTOR_IZQ_2 7

#define PWM_MOTOR_DER 3
#define PWM_MOTOR_IZQ 11

Motores MotorDer(MOTOR_DER_1, MOTOR_DER_2, PWM_MOTOR_DER);
Motores MotorIzq(MOTOR_IZQ_1, MOTOR_IZQ_2, PWM_MOTOR_IZQ);

#define PIN_QRE_DERECHO A0
#define PIN_QRE_IZQUIERDO A1

#define DEBUG_SERIAL 0 // 1 permitido, 0 no permitido

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int BordeTatami = 500; // Si ve lìnea blanca tende de 200 a 720     Si
                                // ve lo negro tende de 800 a 1000

int Pines_QRE[2] = {
    PIN_QRE_DERECHO,
    PIN_QRE_IZQUIERDO,
};

void AsignarPines() {
  for (int idx = 0; idx < 2; idx++) {
    int pin = Pines_QRE[idx];
    pinMode(pin, INPUT);
  }
}

void Sensar() {
  QREder = analogRead(PIN_QRE_DERECHO);
  QREizq = analogRead(PIN_QRE_IZQUIERDO);

  if (DEBUG_SERIAL) {
    Serial.print("IZQ: ");
    Serial.print(QREizq);
    Serial.print("   DER: ");
    Serial.println(QREder);
  }
}

void Borde() {
  MotorDer.Go(80);
  MotorIzq.Go(80);
  Serial.println("Busco");

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    Serial.println("Me caigo weon");
    MotorDer.Go(80);
    MotorIzq.Ba(80);
    delay(300);
    MotorDer.Go(80);
    MotorIzq.Ba(80);
    delay(300);
  }
}

void setup() {
  Serial.begin(9600);
  AsignarPines();
}

void loop() {
  Sensar();
  Borde();
}