
//-------------------LIMPIAR RUEDAS---------------------
void LimpiarRuedas()
{
  MotorDerGoLimpiar();
  MotorIzqGoLimpiar();
  if(DEBUG_ESTRATEGIA)Serial.println("");
}

//--------------------Ataque Derecha--------------------         A RETOCAR
void AtaqueDER()
{
  EnviarPulso();
  SensarSensores();
  LeerSharp(); // Antes no estaba, para testear.
  //DetectarErrores();

  if (JSUMO_der > Rival && Distancia < 40 && JSUMO_izq > Rival)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("Atacar");
  }
  else
  {
    MotorDerStop();
    MotorIzqGoBuscar();
    if(DEBUG_ESTRATEGIA)Serial.println("Buscar");
  }

  if (JSUMO_der > Rival)
  {
    MotorDerGoBuscar();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("JSUMO: LATERAL DERECHA");
  }

  if (JSUMO_izq > Rival)
  {
    MotorDerStop();
    MotorIzqGoBuscar();
    if(DEBUG_ESTRATEGIA)Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if (Distancia > 0 && Distancia < 60)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("Atacar");
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la IZQUIERDA"); 
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la DERECHA");
  }
}

//-------------------Ataque Izquierda-------------------         A RETOCAR
void AtaqueIZQ()
{
  EnviarPulso();
  SensarSensores();
  LeerSharp(); // Antes no estaba, para testear.
  //DetectarErrores();

  if (JSUMO_der > Rival && Distancia < 40 && JSUMO_izq > Rival)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("Atacar");
  }
  else
  {
    MotorDerGoBuscar();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("Buscar");
  }

  if (JSUMO_der > Rival)
  {
    MotorDerGoBuscar();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("JSUMO: LATERAL DERECHA");
  }

  if (JSUMO_izq > Rival)
  {
    MotorDerStop();
    MotorIzqGoBuscar();
    if(DEBUG_ESTRATEGIA)Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if (Distancia > 0 && Distancia < 60)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("Atacar");
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la IZQUIERDA"); 
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la DERECHA");
  }
}

//--------------------Espero Derecha--------------------        10/10 Success
void EsperoDER()
{
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (Distancia < 75 && Distancia > 19)
  {
    MotorDerStop();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("Te vi..."); 
    tiempo_acorralar_actual = millis();
  }
  else
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("Buscar"); 
  }

  if (millis() > tiempo_acorralar_anterior)
  {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if(DEBUG_ESTRATEGIA)Serial.println("Me ACERCO..."); 
  }

  if (JSUMO_der > Rival)
  {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG_ESTRATEGIA)Serial.println("Te vas a la DERECHA"); 
  }

  if (JSUMO_izq > Rival)
  {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG_ESTRATEGIA)Serial.println("Te vas a la IZQUIERDA"); 
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("ATACAR"); 
  }

  if (Distancia < 19)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("ATACAR"); 
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la IZQUIERDA"); 
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la DERECHA"); 
  }
}

//-------------------Espero Izquierda-------------------        10/10 Success
void EsperoIZQ()
{
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (Distancia < 75 && Distancia > 19)
  {
    MotorDerStop();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("Te vi..."); 
    tiempo_acorralar_actual = millis();
  }
  else
  {
    MotorDerGoGhirar();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("Buscar"); 
  }

  if (millis() > tiempo_acorralar_anterior)
  {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if(DEBUG_ESTRATEGIA)Serial.println("Me ACERCO..."); 
  }

  if (JSUMO_der > Rival)
  {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG_ESTRATEGIA)Serial.println("Te vas a la DERECHA"); 
  }

  if (JSUMO_izq > Rival)
  {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG_ESTRATEGIA)Serial.println("Te vas a la IZQUIERDA"); 
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("ATACAR"); 
  }

  if (Distancia < 19)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("ATACAR"); 
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la IZQUIERDA"); 
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la DERECHA"); 
  }
}

//------------------------Ataque------------------------   A RETOCAR: VA MUY RAPIDO SI PIERDE AL RIVAL.
void Ataque()
{
  SensarSensores();
  EnviarPulso();
  LeerSharp(); // Antes no estaba, para testear.
  //DetectarErrores();

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoATAQUE();
    MotorIzqBaATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la DERECHA"); 
  }

  if (Distancia < 25)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("Atacar");
  }
}

//------------------Espero Con Banderas-----------------         A TESTEAR
void EsperoWithFlags()
{
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (Distancia 
  < 75 && Distancia > 19)
  {
    MotorDerStop();
    MotorIzqStop();
    if(DEBUG_ESTRATEGIA)Serial.println("Te vi..."); 
    tiempo_acorralar_actual = millis();
  }
  else
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("Buscar"); 
  }

  if (Distancia < 19)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if(DEBUG_ESTRATEGIA)Serial.println("ATACAR"); 
  }

  if (millis() > tiempo_acorralar_anterior)
  {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if(DEBUG_ESTRATEGIA)Serial.println("Me ACERCO..."); 
  }

  if (JSUMO_der > Rival)
  {
    if (EneableFlags)
      MotorDerGoGhirarSlow();
    if (EneableFlags)
      MotorIzqBaGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG_ESTRATEGIA)Serial.println("Te vas a la DERECHA"); 
    EneableFlags = false;
  }

  if (JSUMO_izq > Rival)
  {
    if (EneableFlags)
      MotorDerBaGhirarSlow();
    if (EneableFlags)
      MotorIzqGoGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    if(DEBUG_ESTRATEGIA)Serial.println("Te vas a la IZQUIERDA"); 
    EneableFlags = false;
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la IZQUIERDA"); 
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if(DEBUG_ESTRATEGIA)Serial.println("SHARP: Rival a la DERECHA"); 
  }

  /*  
  if (Distancia < 35 && SHARP_der < RivalSharp)
  {
    MotorDerBaVerFlags();
    MotorIzqGoVerFlags();
    if(DEBUG_ESTRATEGIA)Serial.println("");
  }

  if (Distancia < 35 && SHARP_izq < RivalSharp)
  {
    MotorDerGoVerFlags();
    MotorIzqBaVerFlags();
  }
  */
}