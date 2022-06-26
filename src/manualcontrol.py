#! /usr/bin/env python3

import rospy
from std_msgs.msg import *
from sensor_msgs.msg import *
from geometry_msgs.msg import *

def cb(data):
    print("ok1")
    joy_value1=data.axes[0]
    joy_value2=data.axes[1]
    joy_value3=data.axes[3]
    joy_value4=data.axes[4]
    servo1 = 0
    servo2 = 0
    obj = Twist()

    if(joy_value3>0.9 or joy_value3<-0.9):
        servo1 = 1*joy_value3/abs(joy_value3)
    if(joy_value4>0.9 or joy_value4<-0.9):
        servo2 = 1*joy_value4/abs(joy_value4)
    

    obj.linear.x=joy_value1
    obj.linear.y=joy_value2
    obj.linear.z=1
    obj.angular.x=servo1
    obj.angular.y=servo2
    obj.angular.z=1
    pub.publish(obj)
    rate.sleep()

rospy.init_node("joyinput",anonymous=True)
rate = rospy.Rate(20)
pub=rospy.Publisher("actuators",Twist,queue_size=20)
print("ok")
sub=rospy.Subscriber("/joy1", Joy, cb, queue_size=20)
rospy.spin()
