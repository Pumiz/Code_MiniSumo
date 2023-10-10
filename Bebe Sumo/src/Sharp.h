// Si no ve nada tende a los 100, Si detecta algo tende a los 900 si està muy
// cerca. en caso de que sea un punto promedio e intermedio esta en los 350 y
// 450.

void ObetenerSharCm() {
  float voltageDer = SharpDerValue / 1024. * 5;
  float resistenciaDer = 2000 * voltageDer / (1 - voltageDer / 5);
  SHARP_der = pow(50 * 1e3 * pow(10, 0.7) / resistenciaDer, (1 / 0.7));
  SHARP_der = SHARP_der / 10;

  SHARP_izq = (6762 / (SharpIzqValue - 9)) - 4;

  if (DEBUG_SHARP)
    Serial.print("Sharp: ");
  if (DEBUG_SHARP)
    Serial.print(SHARP_izq); //  <------- imprime el valor en centímetros del
                             //  sensor deseado.
  if (DEBUG_SHARP)
    Serial.println(" cm");
}
