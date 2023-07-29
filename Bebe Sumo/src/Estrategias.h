
//-------------------LIMPIAR RUEDAS---------------------
void LimpiarRuedas() {
  MotorDerGoLimpiar();
  MotorIzqGoLimpiar();
  if (DEBUG_ESTRATEGIA)
    Serial.println("");
}

//--------------------Ataque Derecha--------------------         10/10 Corregir
// mejor el giro del sharp para el contrario al que busca.
void AtaqueDER() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  // DetectarErrores();

  if (JSUMO_der > Rival && Distancia < 18 && JSUMO_izq > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar");
  }

  if (Distancia > 0 && Distancia < 60) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar");
  } else {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }

  /*   if (Distancia > 20 && SHARP_izq > RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  } */

  if (JSUMO_der > Rival && Distancia > 30) {
    MotorDerGoGhirar();
    MotorIzqBaGhirarSlow();
    if (DEBUG_ESTRATEGIA)
      Serial.println("JSUMO: LATERAL DERECHA");
  }

  if (JSUMO_izq > Rival && Distancia > 30) {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if (SHARP_izq < RivalSharp && SHARP_izq > 0) {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la IZQUIERDA");
    delay(200);
  }

  if (SHARP_der < RivalSharp && SHARP_der > 0) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la DERECHA");
  }

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me caigo weon");
    MotorDerBaLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
  }
}

//-------------------Ataque Izquierda-------------------         10/10 Corregir
// mejor el giro del sharp para el contrario al que busca.
void AtaqueIZQ() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  // DetectarErrores();

  if (JSUMO_der > Rival && Distancia < 18 && JSUMO_izq > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar");
  }

  if (Distancia > 0 && Distancia < 60) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar");
  } else {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }

  /*   if (Distancia > 20 && SHARP_izq > RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  } */

  if (JSUMO_der > Rival && Distancia > 30) {
    MotorDerGoGhirar();
    MotorIzqBaGhirarSlow();
    if (DEBUG_ESTRATEGIA)
      Serial.println("JSUMO: LATERAL DERECHA");
  }

  if (JSUMO_izq > Rival && Distancia > 30) {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if (SHARP_izq < RivalSharp && SHARP_izq > 0) {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la IZQUIERDA");
    delay(200);
  }

  if (SHARP_der < RivalSharp && SHARP_der > 0) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la DERECHA");
  }

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me caigo weon");
    MotorDerBaLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
  }
}

//--------------------Espero Derecha--------------------        10/10 Success
void EsperoDER() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  // DetectarErrores();

  if (Distancia < 75 && Distancia > 19) {
    Visado = true;
    MotorDerStop();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    Visado = false;
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }

  if (Tiempo_acorralar_actual > Tiempo_acorralar_anterior && Visado == true) {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    Visado = true;
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival) {
    Visado = true;
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR 1");
  }

  if (Distancia < 19 && Distancia > 0) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR 2");
  }

  if (SHARP_izq < RivalSharp && SHARP_izq > 0) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp && SHARP_der > 0) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la DERECHA");
  }

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me caigo weon");
    MotorDerBaLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
  }
}

//-------------------Espero Izquierda-------------------        10/10 Success
void EsperoIZQ() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  // DetectarErrores();

  if (Distancia < 75 && Distancia > 19) {
    Visado = true;
    MotorDerStop();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    Visado = false;
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }

  if (Tiempo_acorralar_actual > Tiempo_acorralar_anterior && Visado == true) {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    Visado = true;
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival) {
    Visado = true;
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR 1");
  }

  if (Distancia < 19 && Distancia > 0) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR 2");
  }

  if (SHARP_izq < RivalSharp && SHARP_izq > 0) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp && SHARP_der > 0) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la DERECHA");
  }

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me caigo weon");
    MotorDerBaLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
  }
}

//--------------------Rapido Derecha--------------------         10/10 Success
void RapidoDerecha() {
  SensarSensores();
  EnviarPulso();
  LeerSharp();
  // DetectarErrores();

  if (SHARP_der < RivalSharp) {
    MotorDerBaRAPIDO();
    MotorIzqGoRAPIDO();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la DERECHA");
  }

  if (Distancia > 35) {
    MotorDerGoRAPIDO();
    MotorIzqBaRAPIDO();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }
  if (Distancia < 35 && Distancia > 0) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar");
  }

  if (JSUMO_izq > Rival && Distancia < 35) {
    Ataque_Derecho = true;
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar 2");
    Ataque_Derecho = false;
  }

  if (JSUMO_izq > Rival && Ataque_Derecho == true) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la IZQUIERDA");
  }

  /*   if (JSUMO_izq > Rival) {
      MotorDerBaGhirar();
      MotorIzqGoGhirar();
      if (DEBUG_ESTRATEGIA)
        Serial.println("Te vas a la IZQUIERDA");
    } */
}

//-------------------Rapido Izquierda-------------------         10/10 Success
void RapidoIzquierda() {
  SensarSensores();
  EnviarPulso();
  LeerSharp();
  // DetectarErrores();

  if (SHARP_izq < RivalSharp) {
    MotorDerBaRAPIDO();
    MotorIzqGoRAPIDO();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (Distancia > 35) {
    MotorDerBaRAPIDO();
    MotorIzqGoRAPIDO();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }
  if (Distancia < 35 && Distancia > 0) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Atacar");
  }

  /*   if (JSUMO_der > Rival) {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la DERECHA");
  } */

  /*   if (JSUMO_izq > Rival) {
      MotorDerBaGhirar();
      MotorIzqGoGhirar();
      if (DEBUG_ESTRATEGIA)
        Serial.println("Te vas a la IZQUIERDA");
    } */
}

//-----------------------Deslizar-----------------------         A TESTEAR
void Deslizar() {
  if (Hielo == 1) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me deslizo...");
    delay(700);
    Hielo = 0;
  } else if (Distancia > 60 && Oponente == 0) {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }

  if (Distancia < 75 && Distancia > 15 && Oponente == 0) {
    MotorDerStop();
    MotorIzqStop();
    Oponente = 1;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  }

  if (JSUMO_der > Rival && Oponente == 1) {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival && Oponente == 1) {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR");
  }

  if (Distancia < 19 && Oponente == 1) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR");
  }

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me caigo weon");
    MotorDerBaLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
  }
}

//------------------Espero Con Banderas-----------------         A TESTEAR
void EsperoWithFlags() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  // DetectarErrores();

  if (Distancia < 75 && Distancia > 19) {
    MotorDerStop();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Buscar");
  }

  if (Distancia < 19) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA)
      Serial.println("ATACAR");
  }

  if (millis() > Tiempo_acorralar_anterior) {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    if (EneableFlags)
      MotorDerGoGhirarSlow();
    if (EneableFlags)
      MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la DERECHA");
    EneableFlags = false;
  }

  if (JSUMO_izq > Rival) {
    if (EneableFlags)
      MotorDerBaGhirarSlow();
    if (EneableFlags)
      MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA)
      Serial.println("Te vas a la IZQUIERDA");
    EneableFlags = false;
  }

  if (SHARP_izq < RivalSharp && SHARP_izq > 0) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp && SHARP_der > 0) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA)
      Serial.println("SHARP: Rival a la DERECHA");
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

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ESTRATEGIA)
      Serial.println("Me caigo weon");
    MotorDerBaLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    delay(300);
  }
}