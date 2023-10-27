#include "Lib_Sharp.h"

Lib_Sharp::Lib_Sharp(int p)
{
    pin = p;
    pinMode(pin, INPUT);
}

float Lib_Sharp::SensorRead()
{
    long sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + analogRead(pin);
    }
    float read = sum / n;
    read = read * 1000 / 1024.0;

    return (read);
}