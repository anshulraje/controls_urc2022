#! /usr/bin/env python3

import rospy
from sensor_msgs.msg import *
from std_msgs.msg import Int8
from geometry_msgs import *
import time
import beepy

servo_flag1=1
servo_flag2=1 #trigger servo

servo_flag3=1
servo_flag4=1 #button servo


enable_status=True
actuatorspeed=0

def actuator2(actuatorspeed):
    if(actuatorspeed==1):
        return 1
    else:
        return 7
def actuator1(actuatorspeed):
    if(actuatorspeed==1):
        return -2
    else:
        return -8


def cb(data):
    global servo_flag1
    global servo_flag2
    global servo_flag3
    global servo_flag4

    global enable_status

    global actuatorspeed

    print(f"callback_called_actuators")
    joy_value1=data.axes[0]
    joy_value2=data.axes[1]
    joy_value3=data.axes[4]
    joy_value4=data.axes[3] #pano servo
    joy_value5=data.axes[2]
    joy_value6=data.axes[5]
    stepper_enable=data.buttons[11]
    actuator_speed_change=data.buttons[5]

    obj = Int8()

    if(actuator_speed_change==1):
        if(actuatorspeed==0):
            actuatorspeed=1
        elif(actuatorspeed==1):
            actuatorspeed=0

    if(joy_value1>0.85):
        obj.data=actuator2(actuatorspeed)
    elif(joy_value1<-0.85):
        obj.data=-actuator2(actuatorspeed)
    elif(joy_value2>0.85):
        obj.data=actuator1(actuatorspeed)
    elif(joy_value2<-0.85):
        obj.data=-actuator1(actuatorspeed)


    elif(joy_value3>0.85):
        if(servo_flag3==1):
            obj.data=-3
            servo_flag3=0
    elif(joy_value3<-0.85):
        if(servo_flag4==1):
            obj.data=3
            servo_flag4=0

    elif(joy_value4<-0.85):
        if(servo_flag1==1):
            obj.data=-4
            servo_flag1=0
    elif(joy_value4>0.85):
        if(servo_flag2==1):
            obj.data=4
            servo_flag2=0



    elif(stepper_enable==1):
        if(enable_status==False):
            enable_status=True  
            obj.data=5
        elif(enable_status==True):
            enable_status=False
            obj.data=-5

    else:
        obj.data=0

    if(joy_value3==0 and joy_value4==0):
        servo_flag3=1
        servo_flag4=1 
        servo_flag2=1
        servo_flag1=1

    pub.publish(obj)

    if(enable_status==False):
        print("STEPPER IS ON!!!!!!!!!!!!!!!!!!!!!!!!")
    elif(enable_status==True):
        print("STEPPER IS OFF")
    
    print("******************************")
    if(actuatorspeed==1):
        print(f"Actuator full speed {time.time()}")
    elif(actuatorspeed==0):
        print(f"Actuator half speed {time.time()}")
    print("******************************")

    # rate.sleep()


rospy.init_node("joyinput",anonymous=True)
# rate = rospy.Rate(20)
pub=rospy.Publisher("actuators_topic",Int8,queue_size=20)
print("actuators")
sub=rospy.Subscriber("joy1", Joy, cb)
rospy.spin()
