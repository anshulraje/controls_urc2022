#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <Servo.h>
#include <FastLED.h>
//Servo servo1;
Servo servo3;
Servo servo4;
//Servo servo4;

#define NUM_LEDS 60

#define DIR4 6               //connections to be checked
#define PWM4 5
#define DIR6 10                   //1 6inch 2 4inch
#define PWM6 11
#define POT1 A4
#define DATA_PIN 2
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

#define stepperenablepin 3

//#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
#define servo4pin 4
//
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

void callback2(const std_msgs::Int8& msg){
  int8_t data = msg.data;

  if(data == 0){
    for(int i=0;i<NUM_LEDS;i++)
      leds[i] = CRGB::Green;
    FastLED.show();
  }
  else if(data == 1){
    for(int i=0;i<NUM_LEDS;i++)
      leds[i] = CRGB::Yellow;
    FastLED.show();
  }
  else{
    for(int i=0;i<NUM_LEDS;i++)
      leds[i] = CRGB::Black;
    FastLED.show();
  }
}

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
    servo4.write(105);
    delay(200);
    servo4.write(90);
  }
  else if(value_passed==-4){
    servo4.write(75);
    delay(200);
    servo4.write(90);
  }
  else{
    servo4.write(90);
  }
//  

  digitalWrite(PWM4,vel1);
  digitalWrite(PWM6,vel2);
//  vels.angular.x=vel1;
//  vels.angular.y=vel2;
//  vels.linear.x=servofun1;
//  vels.linear.y=servofun2;
}
ros::Subscriber<std_msgs::Int8> sub1("actuators_topic", callback);
ros::Subscriber<std_msgs::Int8> sub2("led", callback2); 
void setup(){
  pinMode(DIR4,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(DIR6,OUTPUT);
  pinMode(PWM6,OUTPUT);
  pinMode(POT1,INPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  pinMode(3,OUTPUT); //enable pin - high(disabled) - low(enabled)

  
  servo3.attach(7);
  servo4.attach(4);

  n.initNode();
  n.subscribe(sub1);
  n.subscribe(sub2);
//n.advertise(pub1);
}

void loop(){
  
//  pub1.publish(&vels);
  n.spinOnce();
}
