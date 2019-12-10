#include "Acelerometro.h"
#include <Wire.h>

//Constantes de Interrupcio


/////////////////////////////////////////////////////
//////DEFINITION ADDRES // ACCEL CONFIG ////////////////
//////////////////////////////////////////////////////
#define    MPU9250_ADDRESS            0x68

#define    ACC_FULL_SCALE_16_G        0x18
#define    GYRO_FULL_SCALE_2000_DPS   0x18

//FIN DEFINITION ADDRES//

//Función lectura auxiliar
void I2Cread(uint8_t DireccionMPU, uint8_t DireccionRegistro, uint8_t NumeroBytes, uint8_t*Datos) {
  Wire.beginTransmission(DireccionMPU);
  Wire.write(DireccionRegistro);
  Wire.endTransmission();
  Wire.requestFrom(DireccionMPU, NumeroBytes);
  uint8_t index = 0;
  while (Wire.available())
    Datos[index++] = Wire.read();
}

//Función escritura auxiliar
void I2CwriteByte(uint8_t DireccionMPU, uint8_t DireccionRegistro, uint8_t Datos) {
  Wire.beginTransmission(DireccionMPU);
  Wire.write(DireccionRegistro);
  Wire.write(Datos);
  Wire.endTransmission();
}


void configuracionAcelerometro(){
  //Configuración de acelerometro
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);

  //Configuracion temperaturaMPU
  I2CwriteByte(MPU9250_ADDRESS, 35, 0x79);

  //WAKE ON MOTION
  I2CwriteByte(0x68, 0x6B, 0x00);
  I2CwriteByte(0x68, 0x6C, 0x07);
  I2CwriteByte(0x68, 0x1D, 0x09);
  I2CwriteByte(0x68, 0x38, 0x40);
  I2CwriteByte(0x68, 0x37, 0x80);
  I2CwriteByte(0x68, 0x69, 0xC0);
  I2CwriteByte(0x68, 0x1F, 0x8E);
  I2CwriteByte(0x68, 0x1E, 0x0D);
  I2CwriteByte(0x68, 0x6B, 0x20);

  //Configuración de giroscopio
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
}

void termometro(float RoomTemp_Offset, float Temp_Sensitivity, float degC )
{
  //Lectura temperatura
  uint8_t Buf[14];

  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  //Registro temperatura
  float temperaturaMPU = (Buf[6] << 8 | Buf[7]);

  temperaturaMPU = ((temperaturaMPU - RoomTemp_Offset) / Temp_Sensitivity) + degC;


  //Valores en pantalla
  Serial.println("Lectura Termómetro");
  Serial.print("Temperatura mpu= ");
  Serial.print(temperaturaMPU);
  Serial.println("ºC");
  Serial.println();
  Serial.println("-------------------------- \n \n \n");

}

//DIVISION termometro-acelerometro

void acelerometro()
{
  //Lectura acelerometro
  uint8_t Buf[14];
  int FS_ACC = 16;

  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  //Registro Acelerometro
  int16_t ax = (Buf[0] << 8 | Buf[1]);
  int16_t ay = (Buf[2] << 8 | Buf[3]);
  int16_t az = Buf[4] << 8 | Buf[5];

  ax = ax * FS_ACC / 32768;
  ay = ay * FS_ACC / 32768;
  az = az * FS_ACC / 32768;

  //Valores en Pantalla
  Serial.println("Lectura Acelerómetro");
  Serial.print("AX=");
  Serial.print(ax, 2);
  Serial.print("g");
  Serial.print("\t");
  Serial.print("AY=");
  Serial.print(ay, 2);
  Serial.print("g");
  Serial.print("\t");
  Serial.print("AZ=");
  Serial.print(az, 2);
  Serial.println("g");

}

//--------------------------------------------------------

void giroscopio(double radio_helice)
{

  //Lectura firoscopio
  uint8_t Buf[14];
  int FS_GYRO = 2000;

  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  //Registro Acelerometro
  int16_t gx = (Buf[8] << 8 | Buf[9]);
  int16_t gy = (Buf[10] << 8 | Buf[11]);
  int16_t gz = Buf[12] << 8 | Buf[13];

  gx = gx * FS_GYRO / 32768;
  gy = gy * FS_GYRO / 32768;
  gz = gz * FS_GYRO / 32768;

  //Valores pantalla
  Serial.println("Lectura Giroscopio:");
  Serial.print("GX=");
  Serial.print(gx, DEC);
  Serial.print("º/sec");
  Serial.print("\t");
  Serial.print("GY=");
  Serial.print(gy, DEC);
  Serial.print("º/sec");
  Serial.print("\t");
  Serial.print("GZ=");
  Serial.print(gz, DEC);
  Serial.println("º/sec");

  //Velocidad del viento, segun pongamos el giroscopio utilizaremos gx, gy o gz.
  //Utilizamos gx pues suponemos que el giroscopio está colocado en la punta de una helice con el punto señalando en la dirección contraria y a la izquierda del palo que sostenta la helice

  double vel_viento = ((gx * 2 * 3.1415926) / 360) * radio_helice;

  Serial.print("La velocidad del viento es de ");
  Serial.print(vel_viento);
  Serial.println(" m/s");

}
