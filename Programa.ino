/*---------------------------------------------------------------------------------------------
    AUTORES : Denis Felst - Alejandro Miralles - Alenjandro Losa - Yeray Candel (VAAY).
    FECHA : 11/11/2019
    En este programa hemos implementado la medida de temperatura. Cada 10 segundos muestra las medidas
  ---------------------------------------------------------------------------------------------*/
#include <Wire.h>
#include <EEPROM.h>
#include "Constantes.h"
#include "Sensores.h"

void setup() {
Serial.begin(9600); //inicializa puerto serie
  Serial.println("Pulse I para Iniciar...");  
  while(!Serial.available()){}
    char iniciar = Serial.read();
       if (iniciar=='I'){
          Serial.println("Inicializando...");
          Serial.println("Ajustando la ganancia...");
          ads1115.setGain(GAIN_ONE); //ajusta las ganancias
          Serial.println("Rango del ADC: +/- 4.096V (Resolución 2mV)");    

          //CONFIGURANDO INTERRUPCION DEEPSLEEP//
          attachInterrupt(digitalPinToInterrupt(interruptPinDeep), handleInterruptDeep, FALLING); 
          //define la función de interrupciones para que sea activada cuando pase de nivel alto a nivel bajo (cuando se pulse el interruptor) 
           
        }//if iniciar       
}

void loop() {
  int16_t ADCH = ads1115.readADC_SingleEnded(pin_entrada_humedad);
  int16_t ADCT = ads1115.readADC_SingleEnded(pin_entrada_temperatura);
  int16_t ADCL = ads1115.readADC_SingleEnded(pin_entrada_luz);
delay(1000);
      Serial.println("¿Qué quieres hacer?");
      Serial.println("0. Modo de muestreo de todos los sensores.");
      Serial.println("1. Sensor de humedad.");
      Serial.println("2. Sensor de temperatura");
      Serial.println("3. Sensor de luz.");
      Serial.println("4. Sensor de salinidad(no disponible)");
      Serial.println("5. Mostrar posicion Sensores.");
      Serial.println("6. Muestra todos los sensores y se activa el modo deep sleep.");
  char menu; //define un caracter
    while((menu!='0')&&(menu!='1')&&(menu!='2')&&(menu!='3')&&(menu!='4')&&(menu!='5')&&(menu!='6')&&(menu!='7')){ //BUCLE MIENTRAS EL CARACTER NO SEA EL ADECUADO
    while(!Serial.available()){} //BUCLE ESPERANDO CARÁCTER DISPONIBLE A LEER
    menu = Serial.read(); //lee el caracter
    if (menu=='0'){
      humedad(pin_entrada_humedad, AirValue, WaterValue, ADCH);
      temperatura(b, m, ADCT, pin_entrada_temperatura);
      luminosidad(pin_entrada_luz, ADCL);
    } 
    if (menu=='1'){humedad(pin_entrada_humedad, AirValue, WaterValue, ADCH); }
    //if (menu=='2'){salinity_reading(power_pin_sal, pin_entrada_sal, DistilledValue, SalinityValue, ADCS);}
    if (menu=='2'){temperatura(b, m, ADCT, pin_entrada_temperatura);
    }
    if (menu=='3'){luminosidad(pin_entrada_luz, ADCL);}
    if (menu=='4'){loop();}
    if (menu=='5'){/*lecturaGPS();*/}
    }//FIN WHILE CONDICION DATA CORRECTO
    if (menu=='6'){
      humedad(pin_entrada_humedad, AirValue, WaterValue, ADCH);
      temperatura(b, m, ADCT, pin_entrada_temperatura);
      luminosidad(pin_entrada_luz, ADCL);
       
      Serial.println("Presiona el interruptor si quieres salir.");
      delay(5000);//NOS DA 5 SEGUNDOS PARA ACTIVAR LA INTERRUPCION ANTES DE ENTRAR EN MODO DEEP SLEEP
                //Y POSTERIORMENTE RESETEARSE PARA DESPERTARSE
      ESP.deepSleep(5000000);    
      EEPROM.write(0,1); //escribe en la direccion 0 de la memoria un 1, estado que nos indica 
                         //estamos en el bucle de la función muestreo();
      EEPROM.commit();
    }
  //giroscopio(radio_helice);
}

ICACHE_RAM_ATTR void handleInterruptDeep(){//EN CASO DE QUE LA INTERRUPCION SEA ACTIVADA
      EEPROM.write(0,0); //escribe un 0 en la direccion 0, indicando que queremos salir del estado de bucle de muestreo()
      EEPROM.commit();
    loop(); //salta al setup()s
} 
