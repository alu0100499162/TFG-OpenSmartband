#include <Time.h>
#include <TimeLib.h>

#include <HID.h>

#include <Wire.h>
#include "I2Cdev.h"
#include <Adafruit_MLX90614.h>
#include "MPU6050.h"
#include <ArduinoJson.h>


char buffer[256];

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

Adafruit_MLX90614 termometro = Adafruit_MLX90614();
float temperature;

int sensorPinPulse = 0;
int signalPulse; 

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  termometro.begin(); 
  accelgyro.initialize();
  setTime(17,56,00,10,07,2017);

}


void readPulse() {
  signalPulse = analogRead(sensorPinPulse);
}

void readTemperature(){
  temperature = termometro.readObjectTempC();
}

void readIMU() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}

void parseData() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = temperature;
  root["pulse"] = signalPulse;
  JsonArray& accel = root.createNestedArray("accel");
  accel.add(ax);  
  accel.add(ay);   
  accel.add(az); 
  JsonArray& gyro = root.createNestedArray("gyro");
  gyro.add(gx); 
  gyro.add(gy);  
  gyro.add(gz);
  
  JsonArray& timeStamp = root.createNestedArray("timeStamp");
  timeStamp.add(day()); 
  timeStamp.add(month());  
  timeStamp.add(hour());
  timeStamp.add(minute());
  timeStamp.add(second());
  
  root.printTo(buffer, sizeof(buffer));
}

void loop() {
  readPulse();
  readTemperature();
  readIMU();
  parseData();
  Serial.print(buffer);
  Serial.print("\n"); 
  delay(10000);
}
