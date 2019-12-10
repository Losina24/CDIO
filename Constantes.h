// ---------------------------------------------------
//
// Constantes.h
//
// ---------------------------------------------------

#ifndef CONSTANTES_YA_INCLUIDO
#define CONSTANTES_YA_INCLUIDO
#include <Adafruit_ADS1015.h>
#include "Arduino.h"

//CAMBIAR EN FUNCION DE LA DIRECCION A UTILIZAR//
Adafruit_ADS1115 ads1115(0x48);

// HUMEDAD //
const int pin_entrada_humedad = 0;
const int WaterValue = 10200;
const int AirValue = 21200;

// LUMINOSIDAD //
const int pin_entrada_luz = 1;

// TEMPERATURA //
const double b = 0.79;
const double m = 0.035;
const int pin_entrada_temperatura = 2;

//CONTADOR DEEP//
int cont = 0;
const byte interruptPin_ACC = 4;
// TERMOMETRO //
const float RoomTemp_Offset = 21;
const float Temp_Sensitivity = 321;
const float degC = 21;
volatile byte interruptCounter_ACC = 0;
int N_interrupt_ACC = 0;

//double radio_helice = ;


#endif
