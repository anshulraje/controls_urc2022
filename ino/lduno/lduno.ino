#include <ros.h>
#include <geometry_msgs/Point.h>

ros::NodeHandle nh;

geometry_msgs::Point feedback;
ros::Publisher pub("lduno_feedback", &feedback);

#define RATCHET_DIR 12
#define RATCHET_PWM 9
#define LEAD_DIR 5
#define LEAD_PWM 10
#define stepsPerRevolution 40
#define STEP_DIR 4
#define STEP_PWM 11

void callback(const geometry_msgs::Point& msg){
  float ratchet = msg.x;
  float lead_screw = msg.y;
  float stepper = msg.z;

  feedback.z = 0;

  if(ratchet == 1){
    digitalWrite(RATCHET_DIR, LOW);
    analogWrite(RATCHET_PWM, 200);
    feedback.x = 1;
  }
  else{
    analogWrite(RATCHET_PWM, 0);
    feedback.x = 0;
  }

  if(lead_screw == 1){
    digitalWrite(LEAD_DIR, LOW);
    analogWrite(LEAD_PWM, 100);
    feedback.y = 1;  
  }
  else if(lead_screw == -1){
    digitalWrite(LEAD_DIR, HIGH);
    analogWrite(LEAD_PWM, 100);  
    feedback.y = -1;
  }
  else{
    analogWrite(LEAD_PWM, 0);
    feedback.y = 0;
  }

  if(stepper == 1){
    digitalWrite(STEP_DIR, LOW);
    for(int i = 0; i<stepsPerRevolution; i++){
      digitalWrite(STEP_PWM, HIGH);
      delayMicroseconds(2000);
      digitalWrite(STEP_PWM, LOW);
      delayMicroseconds(2000);
    }
    feedback.z = 1;  
  }
  else if(stepper == -1){
    digitalWrite(STEP_DIR, HIGH);
    for(int i = 0; i<stepsPerRevolution; i++){
      digitalWrite(STEP_PWM, HIGH);
      delayMicroseconds(2000);
      digitalWrite(STEP_PWM, LOW);
      delayMicroseconds(2000);
    }
    feedback.z = -1;
  }
  pub.publish(&feedback);
}
ros::Subscriber<geometry_msgs::Point> sub("lduno", callback);
 
void setup(){
  pinMode(RATCHET_DIR, OUTPUT);
  pinMode(RATCHET_PWM, OUTPUT);
  pinMode(LEAD_DIR, OUTPUT);
  pinMode(LEAD_PWM, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}

void loop(){
  nh.spinOnce();
}
