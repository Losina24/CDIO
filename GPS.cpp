// GPS //
#include "GPS.h"
#include <TinyGPS++.h>  //LibrerÃ­a del GPS
#include <SoftwareSerial.h>

///////////////////////////////////////////////////////
/////////GPS DEFINITIONS AND CONFIGURATION ////////////
//////////////////////////////////////////////////////
  
#define RX_PIN  12 // GPS RXI
#define TX_PIN  13 // GPS TX0
#define INIT_PIN 15 // Pin para  Inicializar el GPS
#define GPS_BAUD  4800  //  velocidad de comunicaciÃ³n serie

TinyGPSPlus gps; // Definimos el objeto gps
SoftwareSerial ss(RX_PIN,TX_PIN); // Creamos una UART software para comunicaciÃ³n con el GPS

///////////////////////////////////
/////////GPS FUNCTIONS ////////////
///////////////////////////////////

void switch_on_off()
{
   // Power on pulse
  digitalWrite(INIT_PIN,LOW);
  delay(200);
  digitalWrite(INIT_PIN,HIGH);
  delay(200);
  digitalWrite(INIT_PIN,LOW);
}

// Configuracion
void setupGPS() {
  ss.begin(GPS_BAUD); // Inicializar la comunicaciÃ³n con el GPS
  pinMode(INIT_PIN,OUTPUT);
  switch_on_off(); // Pulso para encender el GPS
}

// Funcion principal
void lecturaGPS() {
  char gpsDate[10];
  char gpsTime[10];
  for(int i=0;i<10;i++){  
  if(gps.location.isValid()){ // Si el GPS esta recibiendo los mensajes NMEA
      Serial.println("  Latitud    Longitud      Alt ");
      Serial.println("   (deg)       (deg)      (ft) ");
      Serial.println("-------------------------------"); 

    Serial.print(gps.location.lat(),6);
    Serial.print('\t');
    Serial.print(gps.location.lng(),6);
    Serial.print('\t');
    Serial.print(gps.altitude.feet());
    Serial.print('\t');
  }
  else  // Si no recibe los mensajes
  {

    Serial.print("Satellites in view: ");
    Serial.println(gps.satellites.value());
  }
  }
}
