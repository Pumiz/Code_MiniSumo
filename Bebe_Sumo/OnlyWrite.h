#include "Arduino.h"

void EncenderLed() {
  digitalWrite(PIN_LED, HIGH);
  delay(250);
  digitalWrite(PIN_LED, LOW);
  delay(250);
}

/*void SensarQRE()
{

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

        if (DEBUG)Serial.println("Me caigo weon");
    }
}
*/

void MotorDerStop() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, 0);
}

void MotorIzqStop() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, 0);
}

void MotorDerGoATAQUE() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_ATAQUE);
}

void MotorIzqGoATAQUE() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_ATAQUE);
}

void MotorDerGoLimpiar() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_LIMPIAR);
}

void MotorIzqGoLimpiar() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_LIMPIAR);
}

void MotorDerGoBuscar() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_BUSCAR);
}


void MotorIzqGoBuscar() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_BUSCAR);
}

void MotorDerGoGhirar() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_GHIRAR);
}

void MotorIzqGoGhirar() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_GHIRAR);
}

void MotorDerGoGhirarSlow() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_GHIRARSLOW);
}

void MotorIzqGoGhirarSlow() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_GHIRARSLOW);
}

void MotorDerBaGhirarSlow() {
  digitalWrite(MOTOR_DER_1, HIGH);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_GHIRARSLOW);
}

void MotorIzqBaGhirarSlow() {
  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_GHIRARSLOW);
}

void MotorIzqBaATAQUE() {
  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_ATAQUE);
}

void MotorIzqBaGhirar() {
  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_GHIRAR);
}

void MotorDerBaGhirar() {
  digitalWrite(MOTOR_DER_1, HIGH);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_GHIRAR);
}

void MotorDerGoVerFlags() {
  digitalWrite(MOTOR_DER_1, LOW);
  digitalWrite(MOTOR_DER_2, HIGH);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_VER_FLAGS);
}

void MotorIzqGoVerFlags() {
  digitalWrite(MOTOR_IZQ_1, LOW);
  digitalWrite(MOTOR_IZQ_2, HIGH);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_VER_FLAGS);
}

void MotorDerBaVerFlags() {
  digitalWrite(MOTOR_DER_1, HIGH);
  digitalWrite(MOTOR_DER_2, LOW);
  analogWrite(PWM_MOTOR_DER, VELOCIDAD_VER_FLAGS);
}

void MotorIzqBaVerFlags() {
  digitalWrite(MOTOR_IZQ_1, HIGH);
  digitalWrite(MOTOR_IZQ_2, LOW);
  analogWrite(PWM_MOTOR_IZQ, VELOCIDAD_VER_FLAGS);
}
