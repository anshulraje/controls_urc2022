#include <ArduinoHardware.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <SPI.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  bme.begin();
}

void loop() {
  int valm, valt;
  int mappedValue;
  valm = analogRead(A0);
  
  mappedValue = map(valm,322,667,100,0);
  Serial.print(mappedValue);
  Serial.print(",");

  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(A1);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  Serial.print(temp_val);
  Serial.print(",");

  float temperature = (float)bme.readTemperature();
  Serial.print(temperature);
  Serial.print(",");

  float pressure = (float)bme.readPressure()/ 100.0F ;
  Serial.print(pressure);
  Serial.print(",");

  float alti = (float)bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print(alti);
  Serial.print(",");

  float humidity = (float) bme.readHumidity();
  Serial.println(humidity);

  delay(500); 
}
