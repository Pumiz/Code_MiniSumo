
//-------------------LIMPIAR RUEDAS---------------------
void LimpiarRuedas() {
  MotorDerGoLimpiar();
  MotorIzqGoLimpiar();
  if (DEBUG_ESTRATEGIA) Serial.println("");
}

//--------------------Ataque Derecha--------------------         9/10 Success     Corregir mejor el giro del sharp para el contrario al que busca.
void AtaqueDER() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (JSUMO_der > Rival && Distancia < 18 && JSUMO_izq > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("Atacar");
  }

  if (Distancia > 0 && Distancia < 60) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("Atacar");
  } else {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  }

  /*   if (Distancia > 20 && SHARP_izq > RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  } */

  if (JSUMO_der > Rival && Distancia > 30) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("JSUMO: LATERAL DERECHA");
  }

  if (JSUMO_izq > Rival && Distancia > 30) {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if (SHARP_izq < RivalSharp) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la DERECHA");
  }
}

//-------------------Ataque Izquierda-------------------         9/10 Success     Corregir mejor el giro del sharp para el contrario al que busca.
void AtaqueIZQ() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (JSUMO_der > Rival && Distancia < 18 && JSUMO_izq > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("Atacar");
  }

  if (Distancia > 0 && Distancia < 60) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("Atacar");
  } else {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  }

  /*   if (Distancia > 20 && SHARP_izq > RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  } */

  if (JSUMO_der > Rival && Distancia > 30) {
    MotorDerGoGhirar();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("JSUMO: LATERAL DERECHA");
  }

  if (JSUMO_izq > Rival && Distancia > 30) {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("JSUMO: LATERAL IZQUIERDA");
  }

  if (SHARP_izq < RivalSharp) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la DERECHA");
  }
}

//--------------------Espero Derecha--------------------        10/10 Success
void EsperoDER() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (Distancia < 75 && Distancia > 19) {
    MotorDerStop();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  }

  if (millis() > Tiempo_acorralar_anterior) {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if (DEBUG_ESTRATEGIA) Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival) {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }

  if (Distancia < 19) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }

  if (SHARP_izq < RivalSharp) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la DERECHA");
  }
}

//-------------------Espero Izquierda-------------------        10/10 Success
void EsperoIZQ() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (Distancia < 75 && Distancia > 19) {
    MotorDerStop();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  }

  if (millis() > Tiempo_acorralar_anterior) {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if (DEBUG_ESTRATEGIA) Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival) {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }

  if (Distancia < 19) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }

  if (SHARP_izq < RivalSharp) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la DERECHA");
  }
}

//-----------------------Deslizar-----------------------
void Deslizar() {
  if (Hielo == 1) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("Me deslizo...");
    delay(700);
    Hielo = 0;
  } else if (Distancia > 60 && Oponente == 0) {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  }

  if (Distancia < 75 && Distancia > 15 && Oponente == 0) {
    MotorDerStop();
    MotorIzqStop();
    Oponente = 1;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  }

  if (JSUMO_der > Rival && Oponente == 1) {
    MotorDerGoGhirarSlow();
    MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival && Oponente == 1) {
    MotorDerBaGhirarSlow();
    MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }

  if (Distancia < 19 && Oponente == 1) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }
}

//------------------------Ataque------------------------   A RETOCAR: VA MUY RAPIDO SI PIERDE AL RIVAL.
void Ataque() {
  SensarSensores();
  EnviarPulso();
  LeerSharp();  // Antes no estaba, para testear.
  //DetectarErrores();

  if (SHARP_der < RivalSharp) {
    MotorDerGoLimpiar();
    MotorIzqBaLimpiar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la DERECHA");
  }

  if (Distancia < 25) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("Atacar");
  }
}

//------------------Espero Con Banderas-----------------         A TESTEAR
void EsperoWithFlags() {
  EnviarPulso();
  SensarSensores();
  LeerSharp();
  //DetectarErrores();

  if (Distancia
        < 75
      && Distancia > 19) {
    MotorDerStop();
    MotorIzqStop();
    if (DEBUG_ESTRATEGIA) Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    MotorDerStop();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("Buscar");
  }

  if (Distancia < 19) {
    MotorDerGoATAQUE();
    MotorIzqGoATAQUE();
    if (DEBUG_ESTRATEGIA) Serial.println("ATACAR");
  }

  if (millis() > Tiempo_acorralar_anterior) {
    MotorDerGoGhirarSlow();
    MotorIzqGoGhirarSlow();
    if (DEBUG_ESTRATEGIA) Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    if (EneableFlags)
      MotorDerGoGhirarSlow();
    if (EneableFlags)
      MotorIzqBaGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la DERECHA");
    EneableFlags = false;
  }

  if (JSUMO_izq > Rival) {
    if (EneableFlags)
      MotorDerBaGhirarSlow();
    if (EneableFlags)
      MotorIzqGoGhirarSlow();
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ESTRATEGIA) Serial.println("Te vas a la IZQUIERDA");
    EneableFlags = false;
  }

  if (SHARP_izq < RivalSharp) {
    MotorDerBaGhirar();
    MotorIzqGoGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la IZQUIERDA");
  }

  if (SHARP_der < RivalSharp) {
    MotorDerGoGhirar();
    MotorIzqBaGhirar();
    if (DEBUG_ESTRATEGIA) Serial.println("SHARP: Rival a la DERECHA");
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