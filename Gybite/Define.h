#define MOTOR_DER_1 8
#define MOTOR_DER_2 9
#define MOTOR_IZQ_1 7
#define MOTOR_IZQ_2 6
#define PWM_MOTOR_DER 3
#define PWM_MOTOR_IZQ 11

#define PIN_PULSADOR 5
#define PIN_LED 13

#define VELOCIDAD_BUSCAR 150
#define VELOCIDAD_ATAQUE 255
#define VELOCIDAD_GHIRAR 200

#define PIN_TRIG 9
#define PIN_ECHO 10

#define PIN_SHARP_DER A5
#define PIN_SHARP_IZQ A6

#define PIN_JSUMO_F_D A7
#define PIN_JSUMO_F_I A4

#define QRE_DERECHO A0
#define QRE_IZQUIERDO A1

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int BordeTatami = 500; // Si ve lìnea blanca tende a 200
unsigned int Tatami = 501;      // Si ve lo negro del tatami tende a 800