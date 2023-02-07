//---------------------QRE1113--------------------
// ROSA:     SEÑAL
// AMARILLO: GND
// CELESTE:  VCC

#define PIN_QRE_DERECHO A1
#define PIN_QRE_IZQUIERDO A0

unsigned int QREder = 0;
unsigned int QREizq = 0;
unsigned int BordeTatami = 300; // Si ve lìnea blanca tende a < 200      Si ve lo negro del tatami tende a > 750

int Pines_QRE[2] = {
    PIN_QRE_DERECHO,
    PIN_QRE_IZQUIERDO,
};

void AsignarPines()
{
    for (int idx = 0; idx < 2; idx++)
    {
        int pin = Pines_QRE[idx];
        pinMode(pin, INPUT);
    }
}

void Borde(){
    if (QREder < BordeTatami)
    {
       Serial.println("Me caigo weon");
    }
}

void setup()
{
    Serial.begin(9600);
    AsignarPines();
}

void loop()
{
    QREder = analogRead(PIN_QRE_DERECHO);
    Borde();
    delay(120);
}