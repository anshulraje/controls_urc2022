#include <ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

#define DIR4 6               //connections to be checked
#define PWM4 5
#define DIR6 10                   //1 6inch 2 4inch
#define PWM6 11
#define POT1 A4

#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
#define servo4pin 4

float servo11,servo22,servo33;
int servofun1=0;
int servofun2=0;


int i=0;
int j=0;
int k=0;
int m=0;
int potent=0;
int maxl=0;
int minl=0;
#define ldrPin 22
int flagoff=0;
int flagon=0;
int direction6inch=0;
int count=0;
int count2=0;
ros::NodeHandle n;
geometry_msgs::Twist vels;
ros::Publisher pub1("velocitiesm", &vels);
int vel1,vel2,vel3,vel4,vel5;
void callback(const geometry_msgs::Twist& msg)
{
  int potent=analogRead(POT1);
  float x = msg.linear.x;  //
  if(x>0.8){
    digitalWrite(DIR4,LOW);//extension(blue-right) 
    direction6inch=0;
    vel1 = 255;
    vel2=0;
    i=2;
  }
  else if(x<-0.8){
    digitalWrite(DIR4,HIGH);//retraction
    direction6inch=1;
    vel1 = 255;
    vel2=0;
    i=1;
  }
  else{
    vel1=0;
  }
  float y = msg.linear.y;// extension(tape right)
  if(y>0.8){
    digitalWrite(DIR6,LOW);
    direction6inch=0;
    vel2 = 255;
    vel1=0;
    i=2;
  }
  else if(y<-0.8){
    digitalWrite(DIR6,HIGH);//retraction
    direction6inch=1;
    vel2 = 255;
    vel1=0;
    i=1;
  }
  else{
    vel2 = 0;
  }
  
  servo11=msg.angular.x;
  servo22=msg.angular.y;
  if(servo11==1){
    servo1.write(180);
    delay(200);
    servo1.write(90);
    servofun1=1;
  }
  else if(servo11==-1){
    servo1.write(0);
    delay(200);
    servo1.write(90);
    servofun1=2;
  }
  else{
    servo1.write(90);
    servofun1=3;
  }
  if(servo22==1){
    servo2.write(180);
    delay(200);
    servo2.write(90);
    servofun2=4;
  }
  else if(servo22==-1){
    servo2.write(0);
    delay(200);
    servo2.write(90);
    servofun2=5;
  }
  else{
    servo1.write(90);
    servofun2=6;
  }
  

  digitalWrite(PWM4,vel1);
  digitalWrite(PWM6,vel2);
  vels.angular.x=vel1;
  vels.angular.y=vel2;
  vels.linear.x=servofun1;
  vels.linear.y=servofun2;
}
ros::Subscriber<geometry_msgs::Twist> sub1("actuators", callback); 
void setup(){
  pinMode(DIR4,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(DIR6,OUTPUT);
  pinMode(PWM6,OUTPUT);
  pinMode(POT1,INPUT);
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);

  n.initNode();
  n.subscribe(sub1);
  n.advertise(pub1);
}

void loop(){
  
  //pub1.publish(&vels);
  n.spinOnce();
}
