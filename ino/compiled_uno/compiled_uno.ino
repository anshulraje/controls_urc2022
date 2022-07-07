#include <MQ7.h>
MQ7 mq7(A1,5.0);

#include <CO2Sensor.h>6 peices(298mm*19mm*19mm - 2, 353mm*19mm*19mm - 2, 340mm*19mm*19mm -2)d
CO2Sensor co2Sensor(A2, 0.99, 100);

#include <Adafruit_SI1145.h>
Adafruit_SI1145 uv = Adafruit_SI1145();
#include <ArduinoHardware.h>
#include <SPI.h>   //Library for SPI interface 
#include <Wire.h>  //Library for I2C interface 
int gas_sensor = A0;                             //Sensor pin
float m = -0.318;                                //Slope
float b = 1.133;                                 //Y-Intercept
float R0 = 11.820; 


void setup() {
  Serial.begin(9600);
  uv.begin();
  co2Sensor.calibrate();
}

void loop() {  
  float sensor_volt;                             //Define variable for sensor voltage
  float RS_gas;                                  //Define variable for sensor resistance
  float ratio;                                   //Define variable for ratio
  float sensorValue = analogRead(gas_sensor);    //Read analog values of sensor
  sensor_volt = sensorValue * (4.4 / 1023.0);    //Convert analog values to voltage
  RS_gas = ((4.4 * 10.0) / sensor_volt) - 10.0;  //Get value of RS in a gas
  ratio = RS_gas / R0;                           // Get ratio RS_gas/RS_air
  double ppm_log = (log10(ratio) - b) / m;       //Get ppm value in linear scale according to the the ratio value
  double ppm = pow(10, ppm_log);                 //Convert ppm value to log scale
  double percentage = ppm / 10000;               //Convert to percentage
  
  Serial.print(ppm);
  Serial.print(",");

  float uvVisible = uv.readVisible();
  Serial.print(uvVisible);
  Serial.print(",");
  
  float uvIR = uv.readIR();
  Serial.print(uvIR);
  Serial.print(",");
 
  float UVindex = uv.readUV();
  UVindex /= 100.0;  
  Serial.print(UVindex);
  Serial.print(",");
 
  int val = co2Sensor.read();
  Serial.print(val);
  Serial.print(",");

  float mqppm = mq7.getPPM();
  Serial.println(mqppm);

  delay(500);
}
