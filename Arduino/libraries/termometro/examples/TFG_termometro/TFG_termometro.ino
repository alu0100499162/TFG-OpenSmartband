/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


 
/** INCLUDE NECESARY LIBRARIES **/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 termometro = Adafruit_MLX90614();



/** SETUP FUNCTION  **/
void setup() {
  Serial.begin(9600);
  termometro.begin();  
}

/** LOOP FUNCTION  **/
void loop() {
  Serial.print("TFG : Smartband OpenSource = ");
  Serial.print("Ambient = "); Serial.print(termometro.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(termometro.readObjectTempC()); Serial.println("*C");


  Serial.println();
  delay(1000);
}
