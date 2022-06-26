#include <ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>
Servo servo1;
Servo servo2;

#define DIR1 6               //connections to be checked
#define PWM1 5
#define DIR2 10                   //1 6inch 2 4inch
#define PWM2 11
#define DIR3 
#define PWM3 12
#define PWM4led 13
#define POT1 A4

#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
#define servo4pin 4

float servo11,servo22,servo33;
int servofun=0;


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
  float x = msg.linear.x;
  if(x>0.8){
    digitalWrite(DIR1,LOW);//extension(blue-right) 
    direction6inch=0;
    vel1 = 255;
    vel2=0;
    vel3=0;
    vel4=0;
    i=2;
  }
  else if(x<-0.8){
    digitalWrite(DIR1,HIGH);//retraction
    direction6inch=1;
    vel1 = 255;
    vel2=0;
    vel3=0;
    vel4=0;
    i=1;
  }
  else{
    vel1=0;
  }
  float y = msg.linear.y;// extension(tape right)
  if(y>0.8){
    digitalWrite(DIR2,LOW);
    direction6inch=0;
    vel2 = 255;
    vel1=0;
    vel3=0;
    vel4=0;
    i=2;
  }
  else if(y<-0.8){
    digitalWrite(DIR2,HIGH);//retraction
    direction6inch=1;
    vel2 = 255;
    vel1=0;
    vel3=0;
    vel4=0;
    i=1;
  }
  else{
    vel2 = 0;
  }
  float xy= msg.linear.z;
  if(xy<-0.7){
    vel3 = 255;
    vel1=0;
    vel2=0;
    vel4=0;
  }
  else{
    vel3=0;
  }

  float ledxy = msg.angular.z;
  if(ledxy<-0.7){
    vel4 = 255;
    vel1=0;
    vel2=0;
    vel3=0;
  }
  else{
    vel4=0;
  }
  
  servo11=msg.angular.x;
  servo22=msg.angular.y;
  if(servo11==1){
    servo1.write(180);
    delay(200);
    servo1.write(90);
    servofun=1;
  }
  else if(servo11==-1){
    servo1.write(0);
    delay(200);
    servo1.write(90);
    servofun=2;
  }
  else{
    servo1.write(90);
    servofun=3;
  }
  if(servo22==1){
    servo2.write(110);
    servofun=4;
  }
  else if(servo22==-1){
    servo2.write(70);
    servofun=5;
  }
  else{
    servo1.write(90);
    servofun=6;
  }
  
  

  digitalWrite(PWM1,vel1);
  digitalWrite(PWM2,vel2);
  digitalWrite(PWM3,vel3);
  digitalWrite(PWM4led,vel4);
  vels.angular.x=vel2;
  vels.angular.y=vel3;
  vels.angular.z=vel4;
  vels.linear.x=servofun;
}
ros::Subscriber<geometry_msgs::Twist> sub1("actuators", callback); 
void setup(){
  pinMode(DIR1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(POT1,INPUT);
  servo1.attach(2);
  servo2.attach(3);

  n.initNode();
  n.subscribe(sub1);
  n.advertise(pub1);
}

void loop(){
  
  pub1.publish(&vels);
  n.spinOnce();
}
