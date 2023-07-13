/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Perito en electonica
 * Quinto perito
 * EB5AM
 * Taller de electronica digital y reparacion de computadoras
 * Nombre: Juan Manuel Sebastián Ixen Coy
 * Carnet: 2019519
*/

#include <LedControl.h>
#include <Ticker.h>

#define DIN 4
#define CLK 2
#define CS 3
#define Sensor A0

void Animacion();
void Lectura();

LedControl LED = LedControl(4,2,3,1);
Ticker ISR_Sensor(Lectura, 5000);

const int Largo = 8; 
int gas;
int propano; 

byte Fuego[8] = 
{
B00000000,
B00000100,
B00011000,
B00110000,
B00101000,
B01000100,
B01000100,
B00111000
};
byte Fuego2[8] = 
{
B10001000,
B10000101,
B01011001,
B00110010,
B00111000,
B01111100,
B01111100,
B00111000
};
byte Copo_Nieve[8] = 
{
B10011001,
B01011010,
B00100100,
B11011011,
B11011011,
B00100100,
B01011010,
B10011001
};

void setup() 
{
  Serial.begin(19200); 
  ISR_Sensor.start();
  LED.shutdown(0, false); 
  LED.setIntensity(0, 15); 
  LED.clearDisplay(0); 
  pinMode(Sensor, INPUT); 
}
void loop() 
{
  if (propano > 40) {
    Animacion();
  } else {
    for (int i = 0; i < Largo; i++) {
    LED.setColumn(0, i, Copo_Nieve[i]);
  }
  }
  delay(1000);
  
  ISR_Sensor.update();
}
void Lectura(){
  int suma =  0;
  for(int i = 0; i < 5; i++){
  gas = map(analogRead(A0),0,1023,0,100);
  suma = suma + gas;
  delay(100);
  }
  propano = suma/5;
  Serial.print(gas);
  Serial.print(",");
}
void Animacion()
{
  LED.clearDisplay(0);
  for(int Tiempo = 0; Tiempo < 5; Tiempo++){
  for (int i = Largo; i > 0; i--) {
  LED.setColumn(0, i, Fuego[i]);
  }
  delay(500);

  for (int i = Largo; i > 0; i--) {
  LED.setColumn(0, i, Fuego2[i]);
  }
  delay(500);
}
}
