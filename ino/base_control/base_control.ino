#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

#define PWM_PIN 3
#define DIR_PIN 2

void callback(const std_msgs::Int32& msg){
    int command = msg.data;
    
    if(command == 1){
        digitalWrite(DIR_PIN, HIGH);
        analogWrite(PWM_PIN, 51);
    }

    else if(command == -1){
        digitalWrite(DIR_PIN, LOW);
        analogWrite(PWM_PIN, 51);
    }

    else{
        analogWrite(PWM_PIN, 0);
    }
}

ros::Subscriber<std_msgs::Int32> sub("/base",&callback);

void setup(){
    nh.initNode();
    nh.subscribe(sub);
    pinMode(PWM_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
}

void loop(){
    nh.spinOnce();
}
