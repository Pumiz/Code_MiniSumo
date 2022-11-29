#define PIN_TRIG_F 11
#define PIN_ECHO_F 10

#define PIN_ECHO_D 9
#define PIN_TRIG_D 8

#define PIN_ECHO_I 7
#define PIN_TRIG_I 6

#define MotorI1 2
#define MotorI2 3

#define MotorD1 4
#define MotorD2 5

#define PIN_PULSADOR A5
#define DEBUG 1

long DistanciaF;
long DistanciaD;
long DistanciaI;
long TiempoF;
long TiempoD;
long TiempoI;
unsigned int referenciaBlanco = 100;
unsigned int referenciaSinSuperficie = 20;
unsigned int CNY70der = 0;
unsigned int CNY70izq = 0;

enum PULSADORES{
  BOTON_GO
};

enum ESTADOS{
  ESPERAR,
  COMBATIR
};

int estado = ESPERAR;
int estado_anterior = COMBATIR;

int valor = 0;

int pin_pulsadores[1] = {PIN_PULSADOR};
int estados_pulsadores_anterior[1] = {true};
bool pulsadorEsLiberado(int index) {
 bool estado_actual = digitalRead(pin_pulsadores[index]);
  bool estado = estado_actual != estados_pulsadores_anterior[index] && estado_actual == HIGH;
  if (estado) delay(500);
  estados_pulsadores_anterior[index] = estado_actual;
  return estado;
}

void EnviarPulsoFrontal()
{
  digitalWrite(PIN_TRIG_F, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_F, LOW);
  TiempoF = pulseIn(PIN_ECHO_F, HIGH);
  DistanciaF = TiempoF / 58;
}

void EnviarPulsoDerecho()
{
  digitalWrite(PIN_TRIG_D, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_D, LOW);
  TiempoD = pulseIn(PIN_ECHO_D, HIGH);
  DistanciaD = TiempoD / 58;
}

 void EnviarPulsoIzquierdo()
 {
  digitalWrite(PIN_TRIG_I, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_I, LOW);
  TiempoI = pulseIn(PIN_ECHO_I, HIGH);
  DistanciaI = TiempoI/ 58;
}

  
void setup() {
  Serial.begin(9600); //baudrate=9600
    pinMode(PIN_PULSADOR, INPUT);
    pinMode(MotorD1, OUTPUT); // Se declara los motores como salida.
    pinMode(MotorD2, OUTPUT);
    pinMode(MotorI1, OUTPUT);
    pinMode(MotorI2, OUTPUT);
    pinMode(PIN_ECHO_F, INPUT);
    pinMode(PIN_TRIG_F, OUTPUT);
    pinMode(PIN_ECHO_D, INPUT);
    pinMode(PIN_TRIG_D, OUTPUT);
    pinMode(PIN_ECHO_I, INPUT);
    pinMode(PIN_TRIG_I, OUTPUT);
    digitalWrite(PIN_TRIG_I, LOW); //Talvez Sacar.
    digitalWrite(PIN_TRIG_D, LOW); //Talvez Sacar.
    digitalWrite(PIN_TRIG_F, LOW); //Talvez Sacar.
    Serial.begin(9600);
}

void loop() {
switch(estado){
 case ESPERAR:
  if(DEBUG)Serial.println("Esperando boton");
 
  if (pulsadorEsLiberado(BOTON_GO)){ estado = COMBATIR;
   delay(5000);
   }
  break;

 case COMBATIR:{
  
   EnviarPulsoFrontal();
   EnviarPulsoDerecho();
   EnviarPulsoIzquierdo();

   CNY70der = analogRead(A0);
   CNY70izq = analogRead(A1);
   
   if((CNY70der > referenciaSinSuperficie) && (CNY70der < referenciaBlanco )) {
    digitalWrite(MotorI1, LOW);
    digitalWrite(MotorI2, HIGH);
    digitalWrite(MotorD1, LOW);
    digitalWrite(MotorD2, HIGH);
    delay(300);
    digitalWrite(MotorI1, HIGH);
    digitalWrite(MotorI2, LOW);
    digitalWrite(MotorD1, LOW);
    digitalWrite(MotorD2, HIGH);
    if(DEBUG)Serial.println("Línea blanca");
    delay(350);
  }

     if((CNY70izq > referenciaSinSuperficie) && (CNY70izq < referenciaBlanco )) {
    digitalWrite(MotorI1, LOW);
    digitalWrite(MotorI2, HIGH);
    digitalWrite(MotorD1, LOW);
    digitalWrite(MotorD2, HIGH);
    delay(300);
    digitalWrite(MotorI1, HIGH);
    digitalWrite(MotorI2, LOW);
    digitalWrite(MotorD1, LOW);
    digitalWrite(MotorD2, HIGH);
    if(DEBUG)Serial.println("Línea blanca");
    delay(350);
  }

   if(DistanciaF < 70){
    digitalWrite(MotorI1, HIGH);
    digitalWrite(MotorI2, LOW);
    digitalWrite(MotorD1, HIGH);
    digitalWrite(MotorD2, LOW);
    if(DEBUG)Serial.println("Atacar");
  }else{
    digitalWrite(MotorI1, HIGH);
    digitalWrite(MotorI2, LOW);
    digitalWrite(MotorD1, HIGH);
    digitalWrite(MotorD2, LOW);
    if(DEBUG)Serial.println("Buscar");
  }

    if(DistanciaD < 70){
    digitalWrite(MotorI1, LOW);
    digitalWrite(MotorI2, HIGH);
    digitalWrite(MotorD1, HIGH);
    digitalWrite(MotorD2, LOW);
    if(DEBUG)Serial.println("Derecha");
    delay(200);
  }

  
    if(DistanciaI < 70){
    digitalWrite(MotorI1, HIGH);
    digitalWrite(MotorI2, LOW);
    digitalWrite(MotorD1, LOW);
    digitalWrite(MotorD2, HIGH);
    if(DEBUG)Serial.println("Izquierda");
    delay(200);
  }  
     break;
 }
}
}
