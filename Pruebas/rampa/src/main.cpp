#define motorPin 9  // Pin PWM al que está conectado el motor
#define rampTime 2000  // Tiempo total de la rampa en milisegundos (2 segundos en este ejemplo)
#define maxSpeed 255  // Velocidad máxima (valor PWM máximo)
#define updateInterval 20  // Intervalo de actualización en milisegundos

unsigned long prevUpdateTime = 0;
int currentSpeed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - prevUpdateTime >= updateInterval) {
    prevUpdateTime = currentTime;

    if (currentSpeed < maxSpeed) {
      currentSpeed += maxSpeed / (rampTime / updateInterval);
      if (currentSpeed > maxSpeed) {
        currentSpeed = maxSpeed;
      }
    }

    analogWrite(motorPin, currentSpeed);

    if (currentSpeed >= maxSpeed) {
      // La rampa ha terminado
      // Realiza alguna acción con el motor (opcional)
    }
    Serial.println(currentSpeed);
  }

  // El resto de tu código principal puede seguir ejecutándose aquí
}
