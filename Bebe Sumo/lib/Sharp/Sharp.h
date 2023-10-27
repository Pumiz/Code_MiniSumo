#ifndef SENSORSHARP_H
#define SENSORSHARP_H

class Sharp {
private:
  int pinVo;

public:
  Sharp(int pin);

  double ObtenerCM();
};

#endif
