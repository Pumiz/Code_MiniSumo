#include "Motores.h"
#include "Arduino.h"

Motores::Motores(int p1, int p2, int pwm) : pin1(p1), pin2(p2), pwmPin(pwm) {
  pin1 = p1;
  pin2 = p2;
  pwmPin = pwm;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pwmPin, OUTPUT);
}

void Motores::Stop() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  analogWrite(pwmPin, 0);
}

void Motores::Go(int speed) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  analogWrite(pwmPin, speed);
}

void Motores::Ba(int speed) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  analogWrite(pwmPin, speed);
}
