#ifndef Motores_H
#define Motores_H

#include "Arduino.h"

class Motores {
public:
  Motores(int p1, int p2, int pwm);
  void Stop();
  void Go(int speed);
  void Ba(int speed);

private:
  int pin1;
  int pin2;
  int pwmPin;
};

#endif