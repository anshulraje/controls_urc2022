#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

#include <OneWire.h>
#include <ros.h>

#include <geometry_msgs/Twist.h>

geometry_msgs:: Twist twist_msg;
ros::NodeHandle  nh1;
ros::Publisher pub2 ("sensor_nano", &twist_msg);

#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2                 // Data wire is plugged into port 2 on the Arduino

OneWire oneWire(ONE_WIRE_BUS);          // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
 
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  nh1.getHardware()->setBaud(9600);
//
  sensors.begin();
//  
 // if (!bme.begin(0x77)) {
   // Serial.println("Could not find a valid BME280 sensor, check wiring!");
   // while (1);
  nh1.initNode();
  nh1.advertise(pub2);
}


void loop() {
  /*Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");
*/
  twist_msg.linear.x = (float)bme.readTemperature();

 /* Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa")*/;

  twist_msg.linear.y = (float)bme.readPressure()/ 100.0F ;

 /* Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m")*/;

  twist_msg.linear.y = (float)bme.readAltitude(SEALEVELPRESSURE_HPA);


 /* Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");
*/
  twist_msg.angular.x= (float) bme.readHumidity();


  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
     twist_msg.angular.y=tempC;

  } 
  else
  {
     twist_msg.angular.y=-1;

  }


  int val;
  int mappedValue;
  val = analogRead(A0);
  Serial.print("@Moisture.analog:" );
  Serial.print(val);
  
  twist_msg.angular.z=val;


  mappedValue = map(val,322,667,100,0);
 // Serial.print("@Moisture.percentage:");
  //Serial.println(mappedValue);
  //Serial.println();

  
//  delay(1000);

  pub2.publish(&twist_msg);
  nh1.spinOnce();

}
