#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Point.h>

geometry_msgs::Point commands;

class LDUno{
  private:
    ros::NodeHandle nh;
		ros::Publisher uno_pub;
    ros::Subscriber sub;
  public:
    LDUno(){
      this->uno_pub = this->nh.advertise<geometry_msgs::Point>("/lduno", 20);
      this->sub = this->nh.subscribe("/joy1", 20, &LDUno::joyCallback, this);
    }

    void joyCallback(const sensor_msgs::Joy& msg){
      commands.x = msg.buttons[2];
      commands.y = msg.buttons[0];

      this->uno_pub.publish(commands);
    }
};

int main(int argc, char **argv){
  ros::init(argc, argv, "ld_uno", ros::init_options::AnonymousName);
  LDUno lduno = LDUno();
  ros::spin();
  return 0;
}