#include "Sensores.h"

//CREO UNA FUNCION PARA HACER UN PORCENTAJE LINEAL//
int porcentaje_lineal(int max, int min, int16_t read){
    return ((100*min/(min-max))-(read*100/(min-max)));
}

// HUMEDAD //
void humedad(int pin_entrada, int WaterValue, int AirValue, int16_t adc){
  int16_t reading = adc;
  int16_t humedad = porcentaje_lineal(AirValue, WaterValue, reading);

    if (humedad<0) {
      humedad = 0;
      }
    if (humedad>100){
          humedad = 100;
      }
      Serial.println("===================");
      Serial.println("HUMEDAD");
      Serial.print("Pin: ");
      Serial.print(pin_entrada);
      Serial.print(": ");
      Serial.println(reading);
      Serial.print("Humedad (%): ");
      Serial.print(humedad);
      Serial.println("%");
      Serial.println("===================");
}//()humedad

// TEMPERATURA //
void temperatura(double b, double m, int16_t adc, int pin_entrada){    //Lectura de temperatura
  double elevado = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;   // Hemos tenido problemas para elevar un nÃºmero y esta ha sido la soluciÃ³n que se nos ha ocurrido (2^15).
  double x = (adc / elevado) * 4.096;   //Operaciones para medir la temperatura mediante el ADS
  double temperatura = ((x - b) / m);

  Serial.println("===================");
  Serial.println("TEMPERATURA");
  Serial.println("Pin: ");
  Serial.println(pin_entrada);
  Serial.println("Temperatura (ºC): ");
  Serial.print(temperatura); // Valor calculado de temperatura
  Serial.println();
  Serial.println("===================");
}//()temperatura

// LUMINOSIDAD //
void luminosidad(int pin_entrada, int16_t adc){

    int16_t reading = adc;
    Serial.println("===================");
    Serial.println("LUMINOSIDAD");
    Serial.print("Pin: ");
    Serial.println(pin_entrada);
    Serial.println(reading);
    if(reading<5000){
        Serial.println("Sensor Tapado/obstruido");
    }
    if(reading>5000 && reading<10000){
        Serial.println("Sombreado/Nubes");
    }
    if(reading>10000){
        Serial.println("Soleado");
    }
}//()luz

void salinidad(int power_pin, int pin_entrada, int distilled_v, int sal_v, int16_t adc){
    digitalWrite(power_pin, HIGH);
    delay(100);
    int16_t reading = adc;
    digitalWrite(power_pin, LOW);
    int16_t salinidad = porcentaje_lineal(sal_v,distilled_v,reading);
    
    if (salinidad<0) {
          salinidad = 0;
      }
    if (salinidad>100){
          salinidad = 100;
      }
      
      Serial.println("===================");
      Serial.println("SALINIDAD");
      Serial.println("---------");
      Serial.print("Lectura pin A");
      Serial.print(pin_entrada);
      Serial.print(": ");
      Serial.println(reading);
      Serial.print("Sal(%): ");
      Serial.print(salinidad);
      Serial.println("%");
      Serial.println("===================");   
}//()salinidad
  
