#ifndef _Lib_Sharp_
#define _Lib_Sharp_
#include "Arduino.h"

class Lib_Sharp
{
private:
    int pin;
    int n = 5;

public:
    LisLib_Sharp(int p);
    float SensorRead();
};
#endif