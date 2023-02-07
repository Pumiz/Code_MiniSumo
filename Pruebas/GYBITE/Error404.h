    #include "Sharp.h"
    EnviarPulso();
    SensarSensores();
    
void DetectarErrores(){
    if(Distancia == 0){
        if(DEBUG_Error404)Serial.println("Error en: ULTRASONIDO");
    }

    if(SHARP_izq == 0){
        if(DEBUG_Error404)Serial.println("Error en: SHARP IZQUIERDO");
    }
    
    if(SHARP_der == 0){
        if(DEBUG_Error404)Serial.println("Error en: SHARP DERECHO");
    }
}