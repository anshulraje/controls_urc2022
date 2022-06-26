#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/Int32.h>
#include <Cytron_SmartDriveDuo.h>

ros::NodeHandle nh;

#define IN1 6 
#define BAUDRATE 115200
Cytron_SmartDriveDuo smartDriveDuo30(SERIAL_SIMPLFIED, IN1, BAUDRATE);
int turn = 0;

void callback(const std_msgs::Int32& msg){
    int command = msg.data;
    
    if(command == 1)
      turn = 30;

    else if(command == -1)
      turn = -30;

    else
      turn = 0;
}

ros::Subscriber<std_msgs::Int32> sub("/base",&callback);

void setup(){
    nh.initNode();
    nh.subscribe(sub);
}

void loop(){
    smartDriveDuo30.control(turn,0);
    nh.spinOnce();
}
