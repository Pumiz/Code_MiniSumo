#include "Sharp.h"
#include <Arduino.h>

Sharp::Sharp(int pin) { pinVo = pin; }

double Sharp::ObtenerCM() {
  int valor = analogRead(pinVo);
  double distancia = 9492 / (valor - 16.92);
  //Serial.println(distancia);
  return distancia;
}