
//-------------------LIMPIAR RUEDAS---------------------
void LimpiarRuedas(){
MotorDerGoLimpiar();
MotorIzqGoLimpiar();
if(DEBUG)Serial.println("Limpiando las ruedas");
}

//------------------------MATAR-------------------------
void MATAR(){
    EnviarPulso();
    SensarSensores();
    //DetectarErrores();

    if (JSUMO_der > Rival)
    {
      MotorDerGoBuscar();
      MotorIzqStop();
      if (DEBUG)Serial.println("JSUMO: LATERAL DERECHA");
    }

    if (JSUMO_izq > Rival)
    {
      MotorDerStop();
      MotorIzqGoBuscar();
      if (DEBUG)Serial.println("JSUMO: LATERAL IZQUIERDA");
    }

    if (JSUMO_der > Rival && Distancia < 40 && JSUMO_izq > Rival)
    {
      MotorDerGoATAQUE();
      MotorIzqGoATAQUE();
      if (DEBUG)Serial.println("Atacar");
    }
    else
    {
      MotorDerStop();
      MotorIzqGoBuscar();
      if (DEBUG) Serial.println("Buscar");
    }

    if (Distancia > 7 && Distancia < 60)
    {
      MotorDerGoATAQUE();
      MotorIzqGoATAQUE();
      if (DEBUG)Serial.println("Atacar");
    }

    if (SHARP_izq < RivalSharp)
    {
      MotorDerStop();
      MotorIzqGoGhirar();
      if (DEBUG)Serial.println("SHARP: Rival a la IZQUIERDA");
    }

    if (SHARP_der < RivalSharp)
    {
      MotorDerGoGhirar();
      MotorIzqStop();
      if (DEBUG)Serial.println("SHARP: Rival a la DERECHA");
    }
}
//--------------------MATAR DERECHA---------------------
void MATARDERECHA(){
   SensarSensores();
   EnviarPulso();
   //DetectarErrores();
   
    if (SHARP_der < RivalSharp)
    {
      MotorDerGoATAQUE();
      MotorIzqBaATAQUE();
      if (DEBUG)Serial.println("SHARP: Rival a la DERECHA");
    }

    if (Distancia < 25){
      MotorDerGoATAQUE();
      MotorIzqGoATAQUE();
    }
}


//----------------------Te Espero-----------------------
void TeEspero(){
  EnviarPulso();
  SensarSensores();
  #include "Sharp.h"
  //DetectarErrores();
    
  if (Distancia < 60 && Distancia >19){
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

  if(Distancia < 19){
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
}