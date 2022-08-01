#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
//Servo servo4;

#define DIR4 6               //connections to be checked
#define PWM4 5
#define DIR6 10                   //1 6inch 2 4inch
#define PWM6 11
#define POT1 A4

#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
//#define servo4pin 4

#define stepperenablepin 3

//float servo11,servo22,servo33;
//int servofun1=0;
//int servofun2=0;


int i=0;
int j=0;
int k=0;
int m=0;
ros::NodeHandle n;
std_msgs::Int8 vels;

//ros::Publisher pub1("velocitiesm", &vels);
int vel1,vel2,vel3,vel4,vel5;
void callback(const std_msgs::Int8& msg)
{
  int value_passed=msg.data;  //
  if(value_passed==1){
    digitalWrite(DIR4,LOW);//extension(blue-right) 
    vel1 = 255;
    vel2=0;
    i=2;
  }
  else if(value_passed==-1){
    digitalWrite(DIR4,HIGH);//retraction
    vel1 = 255;
    vel2=0;
    i=1;
  }
  else if(value_passed==7){
    digitalWrite(DIR4,LOW);//extension(blue-right) 
    vel1 = 80;
    vel2=0;
    i=2;
  }
  else if(value_passed==-7){
    digitalWrite(DIR4,HIGH);//retraction
    vel1 = 80;
    vel2=0;
    i=1;
  }
  else{
    vel1=0;
  }
  if(value_passed==2){
    digitalWrite(DIR6,LOW);
    vel2 = 255;
    vel1=0;
    i=2;
  }
  else if(value_passed==-2){
    digitalWrite(DIR6,HIGH);//retraction
    vel2 = 255;
    vel1=0;
    i=1;
  }
  else if(value_passed==8){
    digitalWrite(DIR6,LOW);
    vel2 = 100;
    vel1=0;
    i=2;
  }
  else if(value_passed==-8){
    digitalWrite(DIR6,HIGH);//retraction
    vel2 = 100;
    vel1=0;
    i=1;
  }
  else{
    vel2 = 0;
  }

  if(value_passed==5){
    digitalWrite(stepperenablepin,HIGH);
  }
  else if(value_passed==-5){
    digitalWrite(stepperenablepin,LOW);
  }

if(value_passed==3){
    servo3.write(105);
    delay(200);
    servo3.write(90);
  }
  else if(value_passed==-3){
    servo3.write(75);
    delay(200);
    servo3.write(90);
  }
  else{
    servo3.write(90);
  }
  if(value_passed==4){
    servo2.write(105);
    delay(200);
    servo2.write(90);
  }
  else if(value_passed==-4){
    servo2.write(75);
    delay(200);
    servo2.write(90);
  }
  else{
    servo2.write(90);
  }
//  

  analogWrite(PWM4,vel1);
  analogWrite(PWM6,vel2);
//    vels.data=vel1;
//  vels.angular.y=vel2;
//  vels.linear.x=servofun1;
//  vels.linear.y=servofun2;
}
ros::Subscriber<std_msgs::Int8> sub1("actuators_topic", callback); 
void setup(){
  pinMode(DIR4,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(DIR6,OUTPUT);
  pinMode(PWM6,OUTPUT);
  pinMode(POT1,INPUT);
  servo3.attach(7);
  servo2.attach(8);

  pinMode(3,OUTPUT);
  n.initNode();
  n.subscribe(sub1);
//  n.advertise(pub1);
}

void loop(){
  
//  pub1.publish(&vels);
  n.spinOnce();
}
