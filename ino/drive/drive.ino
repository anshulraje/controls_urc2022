#include <ArduinoHardware.h>
#include <geometry_msgs/Twist.h>
#include <Cytron_SmartDriveDuo.h>
#include <ros.h>
#include <std_msgs/Int32.h>
#include <FastLED.h>

ros::NodeHandle nh;

#define TEMP_GND 7
#define NUM_LEDS 16
#define DATA_PIN 2
#define IN1 6 
#define BAUDRATE 115200
Cytron_SmartDriveDuo smartDriveDuo30(SERIAL_SIMPLFIED, IN1, BAUDRATE);
CRGB leds[NUM_LEDS];

 float right_wheel=0; 
 float left_wheel=0;
 float linear=0; 
 float angular=0;

void callback1(const geometry_msgs::Twist& msg)
{
  linear= msg.linear.x;
  angular=msg.angular.z;

  right_wheel = (linear + angular) * 100;
  left_wheel = (linear - angular) * 100;
  
}

void callback2(const std_msgs::Int32& msg){
   int colour;
   colour = msg.data;
   
   if(colour == 0){
    for(int i=0;i<=15;i++){
      leds[i] = CRGB::Red;
    }
    FastLED.show();
  }
  
  if(colour == 1){
    for(int i=0;i<=15;i++){
      leds[i] = CRGB::Blue;
    }
    FastLED.show();
  }

  if(colour == 2){
    for(int i=0;i<=15;i++){
      leds[i] = CRGB(255,150,0);
    }
    FastLED.show();
  }
  
  if(colour == 3){
    for(int j =0; j<5; j++){
      for(int i=0;i<=15;i++){
        leds[i] = CRGB::Green;
      }
      FastLED.show();
      delay(250);
      for(int i=0;i<=15;i++){
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      delay(250);
    }
  }
}

ros::Subscriber<geometry_msgs::Twist> sub1("/rover",&callback1);
ros::Subscriber<std_msgs::Int32> sub2("/led",&callback2);

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub1); 
  nh.subscribe(sub2);
  pinMode(TEMP_GND,OUTPUT);
  digitalWrite(TEMP_GND,LOW); 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
  smartDriveDuo30.control(right_wheel,left_wheel);
  nh.spinOnce();
}
