  EnviarPulso();
  SensarSensores();
  #include "Sharp.h"
    
  if (Distancia < 60 && Distancia >15){
    MotorDerStop();
    MotorIzqStop();
    if(DEBUG)Serial.println("Te vi...");
    tiempo_acorralar_actual = millis();
  }else{
    MotorDerStop();
    MotorIzqGoGhirar();
    if(DEBUG)Serial.println("Buscar");
  }

  if(millis() > tiempo_acorralar_anterior){
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if(DEBUG)Serial.println("Me ACERCO...");
  }

  if(JSUMO_der > Rival){
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG)Serial.println("Te vas a la DERECHA");
  }

  if(JSUMO_izq > Rival){
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG)Serial.println("Te vas a la IZQUIERDA");
  }

  if(JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival){
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG)Serial.println("ATACAR");
  }

  if(Distancia < 15){
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG)Serial.println("ATACAR");
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG)Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG)Serial.println("SHARP: Rival a la DERECHA");
  }