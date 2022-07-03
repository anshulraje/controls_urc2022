#include <MQ7.h>
MQ7 mq7(A1,5.0);

#include <CO2Sensor.h>
CO2Sensor co2Sensor(A2, 0.99, 100);

//#include <Adafruit_SI1145.h>
//Adafruit_SI1145 uv = Adafruit_SI1145();
#include <ros.h>

#include <geometry_msgs/Twist.h>

geometry_msgs::Twist twist_msg;
ros::NodeHandle  nh;
ros::Publisher pub1 ("sensor_uno", &twist_msg);


//#include <SPI.h>   //Library for SPI interface 
//#include <Wire.h>  //Library for I2C interface 
int gas_sensor = A0;                             //Sensor pin
float m = -0.318;                                //Slope
float b = 1.133;                                 //Y-Intercept
float R0 = 11.820; 


void setup() {
  co2Sensor.calibrate();
  nh.initNode();
  nh.advertise(pub1);
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
  
  twist_msg.linear.x = percentage;

// twist_msg.linear.y=uv.readVisible();
// twist_msg.linear.z=uv.readIR();
 
  //float UVindex = uv.readUV();
  //UVindex /= 100.0;  
 //0twist_msg.angular.x=UVindex;
 
  int val = co2Sensor.read();
  twist_msg.angular.y=val;

  twist_msg.angular.z=mq7.getPPM();

  pub1.publish(&twist_msg);
  nh.spinOnce();    
}
