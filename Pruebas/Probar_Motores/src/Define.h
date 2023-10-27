#define MOTOR_DER_1 6
#define MOTOR_DER_2 5

#define MOTOR_IZQ_1 8
#define MOTOR_IZQ_2 7

#define PWM_MOTOR_DER 3
#define PWM_MOTOR_IZQ 11

#define PIN_PULSADOR 4
#define PIN_LED 13

#define VELOCIDAD_BUSCAR 150
#define VELOCIDAD_VER_FLAGS 175  //testar velocidad antes de establecer.
#define VELOCIDAD_ATAQUE 255
#define VELOCIDAD_ATAQUERAPIDO 180
#define VELOCIDAD_GHIRAR 230 // Reducir a 215 en caso de que con 11.1V gire muy rápido.
#define VELOCIDAD_LIMPIAR 200
#define VELOCIDAD_GHIRARSLOW 60

#define PIN_TRIG 9
#define PIN_ECHO 10

#define PIN_SHARP_DER A5
#define PIN_SHARP_IZQ A6

#define PIN_JSUMO_F_D A7
#define PIN_JSUMO_F_I A4

#define PIN_QRE_DERECHO A0
#define PIN_QRE_IZQUIERDO A1

unsigned long Tiempo_acorralar_anterior = 25000;
unsigned long Tiempo_acorralar_actual = 0;
int caso = 0;
unsigned int Tiempo = 0;
unsigned long Tiempo_Max = 160;  //aprox es 1seg.
unsigned int Tiempo_Min = 20;
bool Pantalla = true;
bool Mode = false;
bool EneableFlags = true;
bool Visado = false;
bool Ataque_Derecho = false;
int Hielo = 1; 
int Oponente = 0;