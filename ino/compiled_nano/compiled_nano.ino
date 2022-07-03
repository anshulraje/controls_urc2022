#include <ArduinoHardware.h>
#include <geometry_msgs/Twist.h>
#include <ros.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

ros::NodeHandle nh;


geometry_msgs::Twist data;
ros::Publisher pub1("feedback", &data);

void setup() {
  nh.initNode();
  nh.advertise(pub1);
}

void loop() {
int valm, valt;
  int mappedValue;
  valm = analogRead(A0);
  
  mappedValue = map(valm,322,667,100,0);
  data.linear.x = mappedValue;

  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(A1);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  data.linear.y = temp_val;

//  data.linear.z = (float)bme.readTemperature();

//  data.angular.x = (float)bme.readPressure()/ 100.0F ;

//  data.angular.y = (float)bme.readAltitude(SEALEVELPRESSURE_HPA);

//  data.angular.z= (float) bme.readHumidity();
  

  pub1.publish(&data);
  
  delay(500);
  nh.spinOnce();
}
