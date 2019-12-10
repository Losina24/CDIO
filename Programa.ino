/*---------------------------------------------------------------------------------------------
    AUTORES : Denis Felst - Alejandro Miralles - Alenjandro Losa - Yeray Candel (VAAY).
    FECHA : 11/11/2019
    En este programa hemos implementado la medida de temperatura. Cada 10 segundos muestra las medidas
  ---------------------------------------------------------------------------------------------*/
#include <EEPROM.h>
#include "Constantes.h"
#include "Sensores.h"
#include "Acelerometro.h"
 
void ICACHE_RAM_ATTR handleInterrupt_ACC() {
  interruptCounter_ACC++;
  EEPROM.write(0,0); //escribe un 0 en la direccion 0, indicando que queremos salir del estado de bucle de muestreo()
  EEPROM.commit();
  loop(); //salta al setup()s
}

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


          //CONFIGURANDO ACELEROMETRO//
          configuracionAcelerometro();
          pinMode(interruptPin_ACC, INPUT_PULLUP);
          attachInterrupt(digitalPinToInterrupt(interruptPin_ACC), handleInterrupt_ACC, FALLING); // handleInterrupt_ACC = handleInterrupt
          //FIN CONFIGURACION ACELEROMETRO//
                     
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
      Serial.println("6. Muestra todos los sensores 10 veces y se activa el modo deep sleep.");
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
    termometro(RoomTemp_Offset, Temp_Sensitivity, degC );
    }
    if (menu=='3'){luminosidad(pin_entrada_luz, ADCL);}
    if (menu=='4'){loop();}
    if (menu=='5'){/*lecturaGPS();*/}
    }//FIN WHILE CONDICION DATA CORRECTO
    if (menu=='6'){
      for(int i=0;i<11;i++){
      humedad(pin_entrada_humedad, AirValue, WaterValue, ADCH);
      temperatura(b, m, ADCT, pin_entrada_temperatura);
      luminosidad(pin_entrada_luz, ADCL);
       
      if (cont <=9) {
      cont++;
      delay(1000);  
      }
      else {
      EEPROM.write(0,1); //escribe en la direccion 0 de la memoria un 1, estado que nos indica 
                         //estamos en el bucle de la función muestreo();
      EEPROM.commit();
      ESP.deepSleep(10000000); //MICROSEGUNDOS!!!!!!!
      }
      }
    }
    
  if (interruptCounter_ACC > 0) {
    interruptCounter_ACC = 0;
    N_interrupt_ACC++;
    Serial.print("EH, han vuelto los jabalíes. Esta es la ");
    Serial.print(N_interrupt_ACC);
    Serial.println(" vez.");
  }
  //giroscopio(radio_helice);
}
