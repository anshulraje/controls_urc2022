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
    joy_value5=data.axes[5]
    joy_value6=data.axes[2]
    obj = Twist()
    obj.linear.x=joy_value1
    obj.linear.y=joy_value2
    obj.angular.x=joy_value3
    obj.angular.y=joy_value4
    obj.linear.z=joy_value5
    obj.angular.z=joy_value6
    pub.publish(obj)
    # rate.sleep()

rospy.init_node("joyinput",anonymous=True)
# rate = rospy.Rate(20)
pub=rospy.Publisher("actuators",Twist,queue_size=10)
print("ok")()

sub=rospy.Subscriber("joy", Joy, cb)
rospy.spin