 // Si no ve nada tende a los 100, Si detecta algo tende a los 900 si està muy cerca.
 // en caso de que sea un punto promedio e intermedio esta en los 350 y 450.
 
  #define DEBUG_SHARP 0 

  int analogValueDer = analogRead(PIN_SHARP_DER);
  float voltageDer = analogValueDer / 1024. * 5;
  float resistenciaDer = 2000 * voltageDer / (1 - voltageDer / 5);
  float SHARP_der = pow(50 * 1e3 * pow(10, 0.7) / resistenciaDer, (1 / 0.7));
  SHARP_der = SHARP_der / 10;

  int analogValue = analogRead(PIN_SHARP_IZQ);
  float voltage = analogValue / 1024. * 5;
  float resistencia = 2000 * voltage / (1 - voltage / 5);
  float SHARP_izq = pow(50 * 1e3 * pow(10, 0.7) / resistencia, (1 / 0.7));
  SHARP_izq = SHARP_izq / 10;

  if(DEBUG_SHARP)Serial.print("Sharp: ");    
  if(DEBUG_SHARP)Serial.print(SHARP_izq);   //  <------- imprime el valor en centímetros del sensor deseado. 
  if(DEBUG_SHARP)Serial.println(" cm");    

