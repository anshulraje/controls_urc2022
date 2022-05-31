#include <ros.h>
#include <std_msgs/Int32.h>
#include <FastLED.h>

ros::NodeHandle nh;

#define NUM_LEDS 16
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void callback(const std_msgs::Int32& msg){
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

ros::Subscriber<std_msgs::Int32> sub("/led",&callback);

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
  nh.spinOnce();
}
