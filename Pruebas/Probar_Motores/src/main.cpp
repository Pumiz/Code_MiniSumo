#include <Arduino.h>
#include <Define.h>

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
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_LIMPIAR);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);

  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_LIMPIAR);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);

  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_LIMPIAR);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);

  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_LIMPIAR);

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, 0);
  digitalWrite(PWM_MOTOR_IZQ, 0);

  delay(2000);
}