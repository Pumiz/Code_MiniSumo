
//-------------------LIMPIAR RUEDAS---------------------
void LimpiarRuedas()
{
  MotorDerGoLimpiar();
  MotorIzqGoLimpiar();
  //Limpiando las ruedas
}

//------------------------MATAR------------------------- // A RETOCAR
void MATAR()
{
  EnviarPulso();
  SensarSensores();
  // LeerSharp(); // Antes no estaba, para testear.
  DetectarErrores();

  if (JSUMO_der > Rival)
  {
    MotorDerGoBuscar();
    MotorIzqStop();
    //JSUMO: LATERAL DERECHA
  }

  if (JSUMO_izq > Rival)
  {
    MotorDerStop();
    MotorIzqGoBuscar();
    //JSUMO: LATERAL IZQUIERDA
  }

  if (JSUMO_der > Rival && Distancia < 40 && JSUMO_izq > Rival)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    //Atacar
  }
  else
  {
    MotorDerStop();
    MotorIzqGoBuscar();
    //Buscar
  }

  if (Distancia > 7 && Distancia < 60)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    //Atacar
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    // SHARP: Rival a la IZQUIERDA
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqStop();
    //SHARP: Rival a la DERECHA
  }
}
//--------------------MATAR DERECHA---------------------  // A RETOCAR: VA MUY RAPIDO SI PIERDE AL RIVAL.
void MATARDERECHA()
{
  SensarSensores();
  EnviarPulso();
  // LeerSharp(); // Antes no estaba, para testear.
  DetectarErrores();

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoATAQUE();
    MotorIzqBaATAQUE();
    // SHARP: Rival a la DERECHA
  }

  if (Distancia < 25)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
  }
}

//----------------------Te Espero----------------------- // 10/10 Succels
void TeEspero()
{
  EnviarPulso();
  SensarSensores();
  // LeerSharp();
  DetectarErrores();

  if (Distancia < 75 && Distancia > 19)
  {
    MotorDerStop();
    MotorIzqStop();
    // Te vi...
    tiempo_acorralar_actual = millis();
  }
  else
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    // Buscar
  }

  if (millis() > tiempo_acorralar_anterior)
  {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    // Me ACERCO...
  }

  if (JSUMO_der > Rival)
  {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    // Te vas a la DERECHA
  }

  if (JSUMO_izq > Rival)
  {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    // Te vas a la IZQUIERDA
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    // ATACAR
  }

  if (Distancia < 19)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    // ATACAR
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    // SHARP: Rival a la IZQUIERDA
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    // SHARP: Rival a la DERECHA
  }
}

//------------------Te Espero Con Banderas--------------------- // a testear.
void TeEsperoWithFlags()
{
  EnviarPulso();
  SensarSensores();
  // LeerSharp();
  DetectarErrores();

  if (Distancia < 75 && Distancia > 19)
  {
    MotorDerStop();
    MotorIzqStop();
    // Te vi...
    tiempo_acorralar_actual = millis();
  }
  else
  {
    MotorDerStop();
    MotorIzqGoGhirar();
    // Buscar
  }

  if (Distancia < 19)
  {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    // ATACAR
  }

  if (millis() > tiempo_acorralar_anterior)
  {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    // Me ACERCO...
  }

  if (JSUMO_der > Rival)
  {
    if (EneableFlags)
      MotorDerGoGhirarSlow();
    if (EneableFlags)
      MotorIzqBaGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    // Te vas a la DERECHA
    EneableFlags = false;
  }

  if (JSUMO_izq > Rival)
  {
    if (EneableFlags)
      MotorDerBaGhirarSlow();
    if (EneableFlags)
      MotorIzqGoGhirarSlow();
    tiempo_acorralar_anterior = tiempo_acorralar_actual + 3000;
    // Te vas a la IZQUIERDA
    EneableFlags = false;
  }

  if (SHARP_izq < RivalSharp)
  {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    // SHARP: Rival a la IZQUIERDA
  }

  if (SHARP_der < RivalSharp)
  {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    // SHARP: Rival a la DERECHA
  }

  if (Distancia < 35 && SHARP_der < RivalSharp)
  {
    MotorDerBaVerFlags();
    MotorIzqGoVerFlags();
  }

  if (Distancia < 35 && SHARP_izq < RivalSharp)
  {
    MotorDerGoVerFlags();
    MotorIzqBaVerFlags();
  }
}