//-------------------LIMPIAR RUEDAS---------------------
void LimpiarRuedas() {
  MotorDer.Go(VELOCIDAD_LIMPIAR);
  MotorIzq.Go(VELOCIDAD_LIMPIAR);
  if (DEBUG_ACCIONES)
    Serial.println("Limpiando ruedas");
}

//------------------------Ataque------------------------         10/10 Corregir
// Arreglar para cuando busca y lee el sharp opuesto al sentido
// donde esta girando solo se cumpla una condicion, no las dos.
void Ataque() {
  EnviarPulso();
  SensarSensores();

  if (JSUMO_der > Rival && Distancia < 18 && JSUMO_izq > Rival) {
    // Ven los 3 sensores
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar");
  }

  if (Distancia > 0 && Distancia < 60) { // Solo ultrasonido
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar2");
  } else if (Distancia > 60 && caso == Ataque_Derecha) {
    // Busco hacia la derecha
    MotorDer.Stop();
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES) {
      Serial.println("Buscar derecha");
    }
  } else if (Distancia > 60 && caso == Ataque_Izquierda) {
    // Busco hacia la izquierda
    MotorDer.Go(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Stop();
    if (DEBUG_ACCIONES) {
      Serial.println("Buscar izquierda");
    }
  }

  if (JSUMO_izq > Rival && Distancia > 19) { // Jsumo izquierdo y ultrasonido
    MotorDer.Go(VELOCIDAD_GHIRAR);
    MotorIzq.Ba(VELOCIDAD_GHIRAR);
    if (DEBUG_ACCIONES)
      Serial.println("JSUMO: LATERAL IZQUIERDA");
  } else if (JSUMO_izq > Rival && Distancia < 19) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar 3");
  }

  if (JSUMO_der > Rival && Distancia > 19) { // Jsumo derecho y ultrasonido
    MotorDer.Ba(VELOCIDAD_GHIRAR);
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("JSUMO: LATERAL DERECHA");
  } else if (JSUMO_der > Rival && Distancia < 19) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar 4");
  }

  /*   if (SHARP_der > 0 && SHARP_der < RivalSharp) { // Sharp derecho
      MotorDer.Stop();
      MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
      if (DEBUG_ACCIONES)
        Serial.println("SHARP: Rival a la DERECHA");
    } */

/*   if (SHARP_izq > 0 && SHARP_izq < RivalSharp) { // Sharp izquierdo
    MotorDer.Go(VELOCIDAD_GHIRAR);
    MotorIzq.Stop();
    if (DEBUG_ACCIONES)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  } */

  if (ENEABLE_QRE) { // QRE
    if (QREder < BordeTatami || QREizq < BordeTatami) {
      if (DEBUG_ACCIONES)
        Serial.println("Me caigo weon");
      MotorDer.Go(VELOCIDAD_LIMPIAR);
      MotorIzq.Ba(VELOCIDAD_LIMPIAR);
      delay(300);
      MotorDer.Go(VELOCIDAD_LIMPIAR);
      MotorIzq.Ba(VELOCIDAD_LIMPIAR);
      delay(300);
    }
  }
}

//------------------------Espero------------------------        10/10 Success
void Espero() {
  EnviarPulso();
  SensarSensores();

  if (Distancia < 75 && Distancia > 19) {
    MotorDer.Stop();
    MotorIzq.Stop();
    if (DEBUG_ACCIONES)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else if (Distancia > 75 && caso == Espero_Derecha && Visado == false) {
    MotorDer.Stop();
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("Buscar derecha");
  } else if (Distancia > 75 && caso == Espero_Izquierda && Visado == false) {
    MotorDer.Go(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Stop();
    if (DEBUG_ACCIONES)
      Serial.println("Buscar izquierda");
  }

  if (Tiempo_acorralar_actual > Tiempo_acorralar_anterior) {
    Visado = true;
    MotorDer.Go(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    Visado = true;
    MotorDer.Ba(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival) {
    Visado = true;
    MotorDer.Go(VELOCIDAD_GHIRARSLOW); //antes este era Go
    MotorIzq.Ba(VELOCIDAD_GHIRARSLOW);
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la IZQUIERDA");
  } else {
    Visado = false;
  }

  if (JSUMO_der > Rival && Distancia < 19) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar 1");
  }

  if (JSUMO_izq > Rival && Distancia < 19) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar 2");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("ATACAR 3");
  }

  if (Distancia < 19 && Distancia > 0) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("ATACAR 4");
  }

/*   if (SHARP_izq > 0 && SHARP_izq < RivalSharp) {
    MotorDer.Go(VELOCIDAD_GHIRAR);
    MotorIzq.Ba(VELOCIDAD_GHIRAR);
    if (DEBUG_ACCIONES)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  } */

  /*   if (SHARP_der > 0 && SHARP_der < RivalSharp) {
      MotorDer.BaGhirar;
      MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
      if (DEBUG_ACCIONES)
        Serial.println("SHARP: Rival a la DERECHA");
    } */

  if (ENEABLE_QRE) { // QRE
    if (QREder < BordeTatami || QREizq < BordeTatami) {
      if (DEBUG_ACCIONES)
        Serial.println("Me caigo weon");
      MotorDer.Go(VELOCIDAD_LIMPIAR);
      MotorIzq.Ba(VELOCIDAD_LIMPIAR);
      delay(300);
      MotorDer.Go(VELOCIDAD_LIMPIAR);
      MotorIzq.Ba(VELOCIDAD_LIMPIAR);
      delay(300);
    }
  }
}

//------------------------Rapido------------------------         10/10 Success
// correguir si esta bien que solo use un sharp y un jsumo para cada 
// sentido de giro al buscar.
void Rapido() {
  EnviarPulso();
  SensarSensores();

/*   if (SHARP_izq < RivalSharp) {
    MotorDer.Go(VELOCIDAD_ATAQUERAPIDO);
    MotorIzq.Ba(VELOCIDAD_ATAQUERAPIDO);
    if (DEBUG_ACCIONES)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  } */

  /*   if (SHARP_der < RivalSharp) {
      MotorDer.BaRAPIDO;
      MotorIzq.GoRAPIDO;
      if (DEBUG_ACCIONES)
        Serial.println("SHARP: Rival a la DERECHA");
    } */

  if (Distancia > 50 && caso == Rapido_Derecha) {
    // Busco hacia la derecha
    MotorDer.Ba(VELOCIDAD_ATAQUERAPIDO);
    MotorIzq.Go(VELOCIDAD_ATAQUERAPIDO);
    if (DEBUG_ACCIONES)
      Serial.println("Buscar");
  } else if (Distancia > 50 && caso == Rapido_Izquierda) {
    // Busco hacia la izquierda
    MotorDer.Go(VELOCIDAD_ATAQUERAPIDO);
    MotorIzq.Ba(VELOCIDAD_ATAQUERAPIDO);
  }

  if (Distancia > 0 && Distancia < 35) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Atacar");
  }

  if (JSUMO_izq > Rival && Distancia < 35 && caso == Rapido_Derecha) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUERAPIDO);
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_der > Rival && Distancia < 35 && caso == Rapido_Izquierda) {
    MotorDer.Go(VELOCIDAD_ATAQUERAPIDO);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la DERECHA");
  }
}

//-----------------------Deslizar-----------------------         A TESTEAR
void Deslizar() {
  if (Hielo == 1) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("Me deslizo...");
    delay(700);
    Hielo = 0;
  } else if (Distancia > 60 && Oponente == 0) {
    MotorDer.Stop();
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("Buscar");
  }

  if (Distancia < 75 && Distancia > 15 && Oponente == 0) {
    MotorDer.Stop();
    MotorIzq.Stop();
    Oponente = 1;
    if (DEBUG_ACCIONES)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  }

  if (JSUMO_der > Rival && Oponente == 1) {
    MotorDer.Go(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Ba(VELOCIDAD_GHIRARSLOW);
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la DERECHA");
  }

  if (JSUMO_izq > Rival && Oponente == 1) {
    MotorDer.Ba(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la IZQUIERDA");
  }

  if (JSUMO_izq > Rival && Distancia < 30 && JSUMO_der > Rival) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("ATACAR");
  }

  if (Distancia < 19 && Oponente == 1) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("ATACAR");
  }

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ACCIONES)
      Serial.println("Me caigo weon");
    MotorDer.Go(VELOCIDAD_LIMPIAR);
    MotorIzq.Ba(VELOCIDAD_LIMPIAR);
    delay(300);
    MotorDer.Go(VELOCIDAD_LIMPIAR);
    MotorIzq.Ba(VELOCIDAD_LIMPIAR);
    delay(300);
  }
}

//------------------Espero Con Banderas-----------------         A TESTEAR
void EsperoWithFlags() {
  EnviarPulso();
  SensarSensores();

  if (Distancia < 75 && Distancia > 19) {
    MotorDer.Stop();
    MotorIzq.Stop();
    if (DEBUG_ACCIONES)
      Serial.println("Te vi...");
    Tiempo_acorralar_actual = millis();
  } else {
    MotorDer.Stop();
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("Buscar");
  }

  if (Distancia < 19) {
    MotorDer.Go(VELOCIDAD_ATAQUE);
    MotorIzq.Go(VELOCIDAD_ATAQUE);
    if (DEBUG_ACCIONES)
      Serial.println("ATACAR");
  }

  if (millis() > Tiempo_acorralar_anterior) {
    MotorDer.Go(VELOCIDAD_GHIRARSLOW);
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("Me ACERCO...");
  }

  if (JSUMO_der > Rival) {
    if (EneableFlags)
      MotorDer.Go(VELOCIDAD_GHIRARSLOW);
    if (EneableFlags)
      MotorIzq.Ba(VELOCIDAD_GHIRARSLOW);
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la DERECHA");
    EneableFlags = false;
  }

  if (JSUMO_izq > Rival) {
    if (EneableFlags)
      MotorDer.Ba(VELOCIDAD_GHIRARSLOW);
    if (EneableFlags)
      MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    Tiempo_acorralar_anterior = Tiempo_acorralar_actual + 3000;
    if (DEBUG_ACCIONES)
      Serial.println("Te vas a la IZQUIERDA");
    EneableFlags = false;
  }

  if (SHARP_izq < RivalSharp && SHARP_izq > 0) {
    MotorDer.Ba(VELOCIDAD_GHIRAR);
    MotorIzq.Go(VELOCIDAD_GHIRARSLOW);
    if (DEBUG_ACCIONES)
      Serial.println("SHARP: Rival a la IZQUIERDA");
  }
  
  /*
    if (SHARP_der < RivalSharp && SHARP_der > 0) {
      MotorDer.GoGhirar;
      MotorIzq.BaGhirar;
      if (DEBUG_ACCIONES)
        Serial.println("SHARP: Rival a la DERECHA");
    }
   */
  /*
  if (Distancia < 35 && SHARP_der < RivalSharp)
  {
    MotorDerBaVerFlags();
    MotorIzqGoVerFlags();
    if(DEBUG_ACCIONES)Serial.println("");
  }

  if (Distancia < 35 && SHARP_izq < RivalSharp)
  {
    MotorDerGoVerFlags();
    MotorIzqBaVerFlags();
  }
  */

  if (QREder < BordeTatami || QREizq < BordeTatami) {
    if (DEBUG_ACCIONES)
      Serial.println("Me caigo weon");
    MotorDer.Go(VELOCIDAD_LIMPIAR);
    MotorIzq.Ba(VELOCIDAD_LIMPIAR);
    delay(300);
    MotorDer.Go(VELOCIDAD_LIMPIAR);
    MotorIzq.Ba(VELOCIDAD_LIMPIAR);
    delay(300);
  }
}