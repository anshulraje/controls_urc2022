#! /usr/bin/env python3

import rospy
from std_msgs.msg import *
from sensor_msgs.msg import *
from geometry_msgs.msg import *

def cb(data):
    global flag
    joy_value1 = data.axes[5]
    joy_value2 = data.buttons[5]
    joy_value3 = data.axes[2]
    joy_value4 = data.buttons[4]
    if((joy_value1 < -0.8 and joy_value2>=0.9) or flag == 2 ):
        flag = 2
    if((joy_value3 < -0.8 and joy_value4>=0.9) or flag == -2):
        flag = -2
    # rate.sleep()


def cbm(datam):
    global flag
    manual_value1 = datam.x
    manual_value2 = datam.y
    manual_value3 = datam.z
    obj = Point()
    obj.x = manual_value1
    obj.y = manual_value2
    obj.z = manual_value3
    if(flag == -2):
        pub.publish(obj)
        print("okmanual")
    # rate.sleep()


def cbik(dataik):
    global flag
    ik_value1 = dataik.x
    ik_value2 = dataik.y
    ik_value3 = dataik.z
    obj = Point()
    obj.x = ik_value1
    obj.y = ik_value2
    obj.z = ik_value3
    if(flag == 2):
        pub.publish(obj)
        print("okinverse")
    # rate.sleep()


rospy.init_node("joyinput", anonymous=True)
# rate = rospy.Rate(20)
flag = 2
pub = rospy.Publisher("final_ext", Point, queue_size=10)
print("ok")
sub2 = rospy.Subscriber("manual_control", Point, cbm)
sub1 = rospy.Subscriber("inverse_kinematics", Point, cbik)
sub3 = rospy.Subscriber("joy", Joy, cb)
rospy.spin()
