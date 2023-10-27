#include <Arduino.h>

#define MOTOR_DER_1 6
#define MOTOR_DER_2 5

#define MOTOR_IZQ_1 8
#define MOTOR_IZQ_2 7

#define PWM_MOTOR_DER 3
#define PWM_MOTOR_IZQ 11

void setup() {
  pinMode(MOTOR_DER_1, OUTPUT);
  pinMode(MOTOR_DER_2, OUTPUT);
  pinMode(PWM_MOTOR_DER, OUTPUT);

  pinMode(MOTOR_IZQ_1, OUTPUT);
  pinMode(MOTOR_IZQ_2, OUTPUT);
  pinMode(PWM_MOTOR_IZQ, OUTPUT);
}

void loop() {
  // ambos motores van hacia adelante con el orden en el que estan declarados.
  // cada motor corresponde al que esta declarado.

  digitalWrite(MOTOR_DER_1, HIGH);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, 60);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);

  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, 60);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);

    digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, 60);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);

  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, 60);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);
}