#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>

geometry_msgs::Twist rover;
std_msgs::Int32 led;

class Teleop{
  private:
    ros::NodeHandle nh;
    ros::Publisher vel_pub;
    ros::Publisher color_pub;
    ros::Subscriber sub;
  public:
    Teleop(){
      this->vel_pub = this->nh.advertise<geometry_msgs::Twist>("/rover", 20);
      this->color_pub = this->nh.advertise<std_msgs::Int32>("/led", 20);
      this->sub = this->nh.subscribe("/joy0", 20, &Teleop::joyCallback, this);
    }

    void teleop(float linear, float rotational){
      rover.linear.x = linear*0.25;
      rover.angular.z = rotational*0.25;
      this->vel_pub.publish(rover);
    }

    void joyCallback(const sensor_msgs::Joy& msg){
      ros::Rate loop_rate(20); 

      if(msg.axes[3]>0.1 || msg.axes[3] < -0.1 || msg.axes[4] > 0.1 || msg.axes[4] < -0.1){
        this->teleop(msg.axes[4],msg.axes[3]);
      }
      else{
        rover.linear.x = 0;
        rover.angular.z = 0;
        this->vel_pub.publish(rover);
      }
      led.data = 1;
      this->color_pub.publish(led);
      loop_rate.sleep();
    }
};

int main(int argc, char **argv){
  ros::init(argc, argv, "teleop", ros::init_options::AnonymousName);
  Teleop teleop = Teleop();
  ros::spin();
  return 0;
}