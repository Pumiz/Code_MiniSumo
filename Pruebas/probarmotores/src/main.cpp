#include <Arduino.h>

#define MOTOR_DER_1 5
#define MOTOR_DER_2 6
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
  //ambos motores van hacia adelante con el orden en el que estan declarados.
  //cada motor corresponde al que esta declarado.

  digitalWrite(MOTOR_DER_1, HIGH);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, 60);

/*   digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, 60); */

  delay(3000);

  digitalWrite(PWM_MOTOR_DER, LOW);
  digitalWrite(PWM_MOTOR_IZQ, LOW);

  delay(2000);
}
