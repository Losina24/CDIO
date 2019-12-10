// ---------------------------------------------------
//
// Acelerometro.h
//
// ---------------------------------------------------

#ifndef ACELEROMETRO_YA_INCLUIDO
#define ACELEROMETRO_YA_INCLUIDO
#include "Arduino.h"

 void I2Cread(uint8_t , uint8_t , uint8_t , uint8_t* );
 void I2CwriteByte(uint8_t, uint8_t , uint8_t);
 void configuracionAcelerometro();
 //void termometro(float, float, float );
 //void acelerometro();
 //void giroscopio(double);
 
#endif  
