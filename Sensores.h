#ifndef SENSOR_h
#define SENSOR_h
#include "Arduino.h"

// PORCENTAJE LINEAL //
int porcentaje_lineal(int, int, int16_t);

// HUMEDAD //
void humedad(int, int, int, int16_t);
// TEMPERATURA //
void temperatura(double, double, int16_t, int);
// LUMINOSIDAD //
void luminosidad(int, int16_t);

#endif
