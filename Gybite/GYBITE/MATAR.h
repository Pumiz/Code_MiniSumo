    EnviarPulso();
    SensarSensores();

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