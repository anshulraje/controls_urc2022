#! /usr/bin/env python3

import rospy
from sensor_msgs.msg import *
from std_msgs.msg import Int8

def cb(data):
    
    print(f"callback_called_othermotors")
    base_motor1=data.buttons[3]
    base_motor2=data.buttons[1]
    bevel_motor1=data.axes[6]
    bevel_motor2=data.axes[7]
    stepper_motor1=data.buttons[0]
    stepper_motor2=data.buttons[2]
    obj = Int8()

    if(base_motor1==1):
        obj.data=-1
    elif(base_motor2==1):
        obj.data=1
    elif(bevel_motor1>0.85):
        obj.data=2
    elif(bevel_motor1<-0.85):
        obj.data=-2
    elif(bevel_motor2>0.85):
        obj.data=3
    elif(bevel_motor2<-0.85):
        obj.data=-3
    elif(stepper_motor1==1):
        obj.data=4
    elif(stepper_motor2==1):
        obj.data=-4
    else:
        obj.data=0
    pub.publish(obj)
    
    # rate.sleep()


rospy.init_node("othermotors",anonymous=False)
# rate = rospy.Rate(60) # in hertz
sub=rospy.Subscriber("joy1", Joy, cb)
pub=rospy.Publisher("othermotors_topic",Int8,queue_size=10)
print("othermotors")
rospy.spin()



