#include <ros.h>
#include <std_msgs/Int8.h>

#define baserotationpwm 6
#define basedirection 7
#define bevel_right_pwm 10
#define bevel_right_drn 5
#define bevel_left_pwm  9
#define bevel_left_drn  12
const int dirPin = 4; // can be 4 and 3 as well
const int stepPin = 11; // can be 11 and 2 as well
int stepp=0;
const int stepsPerRevolution = 50;

int i=0;
int j=0;
int k=0;
int m=0;
ros::NodeHandle n;
std_msgs::Int8 vels;
int vel1,vel2,vel3,vel4,vel5;

void callback(const std_msgs::Int8& msg)
{
  int8_t value_given=msg.data;
  if(value_given==-1){
    digitalWrite(basedirection,LOW);//extension(blue-right) 
    vel3 = 255;
    i=2;
    k++;
  }
  else if(value_given==1){
    digitalWrite(basedirection,HIGH);//retraction
    vel3 = 255;
    i=1;
    k++;
  }
  else if(value_given==5){
    digitalWrite(basedirection,LOW);//extension(blue-right) 
    vel3 = 80;
    i=2;
    k++;
  }
  else if(value_given==-5){
    digitalWrite(basedirection,HIGH);//retraction
    vel3 = 80;
    i=1;
    k++;
  }
  else{
    vel3=0;
    digitalWrite(basedirection,LOW);
  }
  if(value_given==2){
    digitalWrite(bevel_right_drn,LOW);//extension(blue-right)
    digitalWrite(bevel_left_drn,HIGH);
    vel4 = 255;
    vel5 = 255;
    
    m=10;
  }
  else if(value_given==-2){
    digitalWrite(bevel_right_drn,HIGH)  ;//extension(blue-right)
    digitalWrite(bevel_left_drn,LOW);
    vel4 = 255;
    vel5 = 255;
   
    m=20;
  }
  else if(value_given==-7){
    digitalWrite(bevel_right_drn,HIGH)  ;//extension(blue-right)
    digitalWrite(bevel_left_drn,LOW);
    vel4 = 100;
    vel5 = 100;
   
    m=20;
  }
  else if(value_given==7){
    digitalWrite(bevel_right_drn,LOW);//extension(blue-right)
    digitalWrite(bevel_left_drn,HIGH);
    vel4 = 100;
    vel5 = 100;
    
    m=10;
  }
  else if(value_given==3){
    digitalWrite(bevel_right_drn,HIGH);//extension(blue-right)
    digitalWrite(bevel_left_drn,HIGH);
    vel4 = 255;
    vel5 = 255;
 
    m=30;
  }
  else if(value_given==8){
    digitalWrite(bevel_right_drn,HIGH);//extension(blue-right)
    digitalWrite(bevel_left_drn,HIGH);
    vel4 = 100;
    vel5 = 100;
 
    m=30;
  }
  else if(value_given==-3){
    digitalWrite(bevel_right_drn,LOW);//extension(blue-right)
    digitalWrite(bevel_left_drn,LOW);
    vel4 = 255;
    vel5 = 255;
  

    m=40;
  }
  else if(value_given==-8){
    digitalWrite(bevel_right_drn,LOW);//extension(blue-right)
    digitalWrite(bevel_left_drn,LOW);
    vel4 = 100;
    vel5 = 100;
  

    m=40;
  }
  else{
    vel4 = 0;
    vel5 = 0;
    digitalWrite(bevel_right_drn,LOW);
    digitalWrite(bevel_left_drn,LOW);
    m=100;
  }
  if(value_given==4){
      digitalWrite(dirPin, HIGH);
      stepp=101;

  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  }
  else if(value_given==-4){
  digitalWrite(dirPin, LOW);
  stepp=200;

  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  }
  analogWrite(baserotationpwm,(vel3)); 
  analogWrite(bevel_right_pwm,(vel4/2));
  analogWrite(bevel_left_pwm,(vel5/2));
}
ros::Subscriber<std_msgs::Int8> sub1("othermotors_topic", callback); 
void setup(){
  pinMode(baserotationpwm,OUTPUT);
  pinMode(basedirection,OUTPUT);
  pinMode(bevel_right_pwm,OUTPUT);
  pinMode(bevel_left_pwm,OUTPUT);
  pinMode(bevel_right_drn,OUTPUT);
  pinMode(bevel_left_drn,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);

  n.initNode();
  n.subscribe(sub1);
}

void loop(){
  n.spinOnce();
}
