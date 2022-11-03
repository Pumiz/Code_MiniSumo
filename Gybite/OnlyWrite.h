void EncenderLed()
{
    digitalWrite(PIN_LED, HIGH);
    delay(250);
    digitalWrite(PIN_LED, LOW);
}

/*void SensarQRE()
{
    QREder = analogRead(QRE_DERECHO);
    QREizq = analogRead(QRE_IZQUIERDO);
    if (QREizq < BordeTatami || QREder < BordeTatami)
    {
        digitalWrite(MOTOR_DER_1, LOW);
        digitalWrite(MOTOR_DER_2, HIGH);
        analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
        digitalWrite(MOTOR_IZQ_1, HIGH);
        digitalWrite(MOTOR_IZQ_2, LOW);
        analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
        delay(300);
        digitalWrite(MOTOR_DER_1, LOW);
        digitalWrite(MOTOR_DER_2, HIGH);
        analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
        digitalWrite(MOTOR_IZQ_1, LOW);
        digitalWrite(MOTOR_IZQ_2, HIGH);
        analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);

        if (DEBUG)
            Serial.println("Me caigo weon");
    }
}
*/

void MotorDerStop()
{
    digitalWrite(MOTOR_DER_1, LOW);
    digitalWrite(MOTOR_DER_2, LOW);
    analogWrite(PWM_MOTOR_DER, 0);
}

void MotorIzqStop()
{
    digitalWrite(MOTOR_IZQ_1, LOW);
    digitalWrite(MOTOR_IZQ_2, LOW);
    analogWrite(PWM_MOTOR_IZQ, 0);
}

void MotorDerGoATAQUE()
{
    digitalWrite(MOTOR_DER_1, HIGH);
    digitalWrite(MOTOR_DER_2, LOW);
    analogWrite(PWM_MOTOR_DER, VELOCIDAD_ATAQUE);
}

void MotorIzqGoATAQUE()
{
    digitalWrite(MOTOR_IZQ_1, LOW);
    digitalWrite(MOTOR_IZQ_2, HIGH);
    analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_ATAQUE);
}

void MotorDerGoBuscar(){
    digitalWrite(MOTOR_DER_1, HIGH);
    digitalWrite(MOTOR_DER_2, LOW);
    analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
}


void MotorIzqGoBuscar(){
    digitalWrite(MOTOR_IZQ_1, LOW);
    digitalWrite(MOTOR_IZQ_2, HIGH);
    analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
}

void MotorDerGoGhirar(){
    digitalWrite(MOTOR_DER_1, LOW);
    digitalWrite(MOTOR_DER_2, HIGH);
    analogWrite(PWM_MOTOR_DER, VELOCIDAD_GHIRAR);
}

void MotorIzqGoGhirar(){
    digitalWrite(MOTOR_IZQ_1, LOW);
    digitalWrite(MOTOR_IZQ_2, HIGH);
    analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_GHIRAR);
}

