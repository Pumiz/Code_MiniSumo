


void DetectarErrores() {

  EnviarPulso();
  SensarSensores();
  LeerSharp();

  if (Distancia == 0) {
    if (DEBUG_Error404)
      Serial.println("Error404: ULTRASONIDO");
  }
 /*
  if (SHARP_izq == 0) {
    if (DEBUG_Error404)
      Serial.println("Error404: SHARP IZQUIERDO");
  }

  if (SHARP_der == 0) {
    if (DEBUG_Error404)
      Serial.println("Error404: SHARP DERECHO");
  }
  */

  if (JSUMO_izq > 320 && JSUMO_izq < 480) {
    if (DEBUG_Error404)
      Serial.println("Error404: JSUMO IZQUIERDO");
  }

  if (JSUMO_der > 320 && JSUMO_izq < 480) {
    if (DEBUG_Error404)
      Serial.println("Error404: JSUMO DERECHO");
  }
}