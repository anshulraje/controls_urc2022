#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist commands;

class LDMega{
  private:
    ros::NodeHandle nh;
		ros::Publisher mega_pub;
    ros::Subscriber sub;
  public:
    LDMega(){
      this->mega_pub = this->nh.advertise<geometry_msgs::Twist>("/ldmega", 20);
      this->sub = this->nh.subscribe("/joy", 20, &LDMega::joyCallback, this);
    }

    void joyCallback(const sensor_msgs::Joy& msg){
      float ratchet = msg.axes[0];
      float lead_screw = msg.axes[1];

      if(abs(ratchet) > 0.25)
        ratchet = 1.0;
			if(abs(lead_screw) > 0.25)
				lead_screw = 1.0 * abs(lead_screw)/lead_screw;

			commands.linear.x = ratchet;
			commands.linear.y = lead_screw;

      this->mega_pub.publish(commands);
    }
};

int main(int argc, char **argv){
  ros::init(argc, argv, "ld_mega", ros::init_options::AnonymousName);
  LDMega ldmega = LDMega();
  ros::spin();
  return 0;
}