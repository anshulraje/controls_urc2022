#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import os

hostname = "192.168.1.11" 

def check_connection():
    while(True):
        response = os.system("ping -c 1 " + hostname)
        if response == 0:
            print(hostname, 'is up!')
        else:
            print("Connection lost, stopped rover")
            pub.publish(Twist())
        rate.sleep()

if __name__ == "__main__":
    rospy.init_node("connection_loss", anonymous=True)
    pub = rospy.Publisher("/rover", Twist, queue_size=10)
    rate = rospy.Rate(0.2)
    while not rospy.is_shutdown():
        check_connection()