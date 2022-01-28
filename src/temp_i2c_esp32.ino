#include "max6675.h" //lib termopar
#include "EmonLib.h" //lib sensor SCT013
#include <Wire.h>    //lib I2C

#define SLAVE_ADDRESS 0x04  // cria o escravo com endereço 0x04
#define FLOATS_SENT 2  //vetor

//pinagem termopar
int ktcSO = 8; //PINO DIGITAL (SO)
int ktcCS = 9; //PINO DIGITAL (CS)
int ktcCLK = 10; //PINO DIGITAL (CLK / SCK)


float data[FLOATS_SENT];


//pinagem sensor SCT013
int pin = A2;
EnergyMonitor sensor;



MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)
  
void setup(){
  Serial.begin(9600); 
  sensor.current(pin, 60.606);

  // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

    // define callbacks for i2c communication
    Wire.onRequest(sendData);

    
}

void loop(){ 
   data[0] = getTemp();
   data[1] = getCorrente();

  
   Serial.println(data[0]);
   Serial.println(data[1]);
   Serial.println("---------------------");

   delay(1000);
}

void sendData(){
  Wire.write((byte*) & data,FLOATS_SENT*sizeof(float));
  
}

float getTemp(){
  float temp = ktc.readCelsius();
  return temp;
}

float getCorrente(){
   float courrent = 0;
   float cor = sensor.calcIrms(1480);

   if (cor>0 && cor<7){
     return courrent;
   }else{
     return cor;
   }
}
