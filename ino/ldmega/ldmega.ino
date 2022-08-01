#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>

Servo bucket;
Servo cam1;
Servo cam2;

ros::NodeHandle nh;

geometry_msgs::Twist feedback;
ros::Publisher pub("ldmega_feedback", &feedback);

void callback(const geometry_msgs::Twist& msg){
  float bucket_f = msg.linear.x;
  float bucket_b = msg.linear.y;
  float cam1_f = msg.linear.z;
  float cam1_b = msg.angular.x;
  float cam2_f = msg.angular.y;
  float cam2_b = msg.angular.z;

  feedback.linear.x = 0;
  feedback.linear.y = 0;
  feedback.linear.z = 0;
  feedback.angular.x = 0;
  feedback.angular.y = 0;
  feedback.angular.z = 0;

  if(bucket_f){
    bucket.write(180);
    feedback.linear.x = 1;}
  else if(bucket_b){
    bucket.write(0);
    feedback.linear.y = 1;}
  else
    bucket.write(90);

  if(cam1_f){
    cam1.write(105);
    delay(200);
    cam1.write(90);  
    feedback.linear.z = 1;
  }
  else if(cam1_b){
    cam1.write(75);
    delay(200);
    cam1.write(90); 
    feedback.angular.x = 1;
  }
  else
    cam1.write(90);

  if(cam2_f){
    cam2.write(105);
    delay(200);
    cam2.write(90);
    feedback.angular.y = 1;  
  }
  else if(cam2_b){
    cam2.write(75);
    delay(200);
    cam2.write(90);
    feedback.angular.z = 1;
  }
  else
    cam2.write(90);    

  pub.publish(&feedback);
}

ros::Subscriber<geometry_msgs::Twist> sub("ldmega", callback); 

void setup(){
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
  bucket.attach(9);
  cam1.attach(8);
  cam2.attach(7);
}

void loop(){
  nh.spinOnce();
}
