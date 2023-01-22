#include <ArduinoHardware.h>
#include <geometry_msgs/Twist.h>
#include <Cytron_SmartDriveDuo.h>
#include <ros.h>

ros::NodeHandle nh;

#define IN1 6 
#define BAUDRATE 115200
Cytron_SmartDriveDuo smartDriveDuo30(SERIAL_SIMPLIFIED, IN1, BAUDRATE);
geometry_msgs::Twist vels;
ros::Publisher pub1("feedback", &vels);

 float right_wheel=0; 
 float left_wheel=0;
 float linear=0; 
 float angular=0;

void callback(const geometry_msgs::Twist& msg)
{
  linear= msg.linear.x;
  angular=msg.angular.z;

  right_wheel = (linear + angular) * 100;
  left_wheel = (linear - angular) * 100;
  vels.linear.x = right_wheel;
  vels.linear.y = left_wheel;
  pub1.publish(&vels);
}

ros::Subscriber<geometry_msgs::Twist> sub("/rover",&callback);

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub1);
}

void loop()
{
  smartDriveDuo30.control(right_wheel,left_wheel);
  nh.spinOnce();
}
