#! /usr/bin/env python3

import rospy
from sensor_msgs.msg import *
from std_msgs.msg import Int8
bevelspeed=1

def bevel2(bevelspeed):
    if(bevelspeed==1):
        return -2
    else:
        return -7
def bevel1(bevelspeed):
    if(bevelspeed==1):
        return -3
    else:
        return -8


def cb(data):
    global bevelspeed
    
    print(f"callback_called_othermotors")
    base_motor1=data.buttons[3]
    base_motor2=data.buttons[1]
    bevel_motor1=-data.axes[7]
    bevel_motor2=-data.axes[6]
    stepper_motor1=data.buttons[0]
    stepper_motor2=data.buttons[2]
    base_motor1_low=data.axes[2]
    base_motor2_low=data.axes[5]
    bevel_speed_change=data.buttons[4]
    obj = Int8()

    if(base_motor1==1):
        obj.data=-1
    elif(base_motor2==1):
        obj.data=1
    elif(bevel_motor2>0.85):
        obj.data=bevel2(bevelspeed)
    elif(bevel_motor2<-0.85):
        obj.data=-bevel2(bevelspeed)
    elif(bevel_motor1<-0.85):
        obj.data=bevel1(bevelspeed)
    elif(bevel_motor1>0.85):
        obj.data=-bevel1(bevelspeed)
    elif(stepper_motor1==1):
        obj.data=4
    elif(stepper_motor2==1):
        obj.data=-4
    elif(base_motor1_low==-1):
        obj.data=5
    elif(base_motor2_low==-1):
        obj.data=-5
    elif(bevel_speed_change==1):
        if(bevelspeed==0):
            bevelspeed=1
        elif(bevelspeed==1):
            bevelspeed=0
    else:
        obj.data=0
    pub.publish(obj)

    if(bevelspeed==1):
        print("Bevel running fast")
    if(bevelspeed==0):
        print("Bevel running slow")

    
    # rate.sleep()


rospy.init_node("othermotors",anonymous=False)
# rate = rospy.Rate(60) # in hertz
sub=rospy.Subscriber("joy1", Joy, cb)
pub=rospy.Publisher("othermotors_topic",Int8,queue_size=10)
print("othermotors")
rospy.spin()
